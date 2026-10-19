// ================================================================
// logging.c — Sistema de logging del driver
// Documentacion: docs/LogSimple.md, docs/LogRich.md,
//                docs/LogEventNoName.md, docs/LogNamedEvent.md
// Direcciones originales:
//   LogSimple:      0x1400023C4
//   LogRich:        0x14000F1C4
//   LogEventNoName: 0x1400023EC
//   LogNamedEvent:  0x14000F464
//   g_LogDispatchFn: 0x140A7BB08
// ================================================================

#include "include/driver.h"

// ================================================================
// EventType del dispatcher (compartido por las 4 funciones)
// ================================================================

#define LOG_EVENT_TYPE      43      // 0x2B

// ================================================================
// LogSimple
// ================================================================
// Log sin datos extra. Wrapper mínimo del dispatcher.
// Direccion original: 0x1400023C4
// ================================================================

__int64 LogSimple(PVOID ContextPtr, ULONG Tag, PVOID LogData)
{
	typedef __int64 (*FN)(PVOID, ULONG, PVOID, ULONG, PVOID);
	return ((FN)g_LogDispatchFn)(
		ContextPtr,
		LOG_EVENT_TYPE,
		LogData,
		Tag,
		0);                 // sin descriptores, terminador
}

// ================================================================
// LogEventNoName
// ================================================================
// Log con 1 código de error (4 bytes) como descriptor.
// Se usa en rutas de error para registrar NTSTATUS codes.
// Direccion original: 0x1400023EC
// [NOTA] El decompiler de IDA falla con esta función por CFG.
//        Análisis desde ensamblador.
// ================================================================

__int64 LogEventNoName(PVOID ContextPtr, ULONG Tag, PVOID LogData,
	ULONG ErrorCode)
{
	// El error se copia al stack para obtener su dirección
	// [HECHO] El dispatcher necesita un puntero al dato, no el valor
	ULONG errorOnStack = ErrorCode;

	typedef __int64 (*FN)(PVOID, ULONG, PVOID, ULONG, PVOID, ULONG, PVOID);
	return ((FN)g_LogDispatchFn)(
		ContextPtr,
		LOG_EVENT_TYPE,
		LogData,
		Tag,
		&errorOnStack,      // Desc0: puntero al error
		4,                  // Size0: 4 bytes
		0);                 // Terminator
}

// ================================================================
// LogRich
// ================================================================
// Log con 3 datos extra (4 bytes c/u) como descriptores.
// Direccion original: 0x14000F1C4
// ================================================================

__int64 LogRich(PVOID ContextPtr, ULONG Tag, PVOID LogData,
	ULONG Param1, ULONG Param2, ULONG Param3)
{
	// Copiar datos al stack para obtener direcciones estables
	// [HECHO] Mismo patrón que LogEventNoName
	ULONG x = Param1;
	ULONG y = Param2;
	ULONG z = Param3;

	typedef __int64 (*FN)(PVOID, ULONG, PVOID, ULONG,
		PVOID, ULONG, PVOID, ULONG,
		PVOID, ULONG, PVOID);
	return ((FN)g_LogDispatchFn)(
		ContextPtr,
		LOG_EVENT_TYPE,
		LogData,
		Tag,
		&x,                 // Desc0
		4,                  // Size0
		&y,                 // Desc1
		4,                  // Size1
		&z,                 // Desc2
		4,                  // Size2
		0);                 // Terminator
}

// ================================================================
// LogNamedEvent
// ================================================================
// Log con un string como descriptor de datos.
// Calcula strlen + 1 (incluye null terminator).
// Si name es NULL, usa "NULL" (length = 5).
// Direccion original: 0x14000F464
// ================================================================

__int64 LogNamedEvent(PVOID ContextPtr, ULONG Tag, PVOID LogData,
	const char* Name)
{
	__int64 length;
	const char* safeName;

	if (Name != NULL) {
		// [HECHO] strlen compilado inline por MSVC
		// Loop do-while con i = -1 para manejar strings vacíos
		__int64 i = -1;
		do
			++i;
		while (Name[i] != 0);
		length = i + 1;             // incluir null terminator
		safeName = Name;
	}
	else {
		// [HECHO] Fallback para puntero NULL
		length = 5;                 // "NULL" + null = 5
		safeName = "NULL";
	}

	typedef __int64 (*FN)(PVOID, ULONG, PVOID, ULONG,
		PVOID, ULONG, PVOID);
	return ((FN)g_LogDispatchFn)(
		ContextPtr,
		LOG_EVENT_TYPE,
		LogData,
		Tag,
		(PVOID)safeName,    // Desc0: puntero al string
		(ULONG)length,      // Size0: strlen + 1
		0);                 // Terminator
}

// ================================================================
// EtwWriteWrapper
// ================================================================
// Construye un EVENT_DESCRIPTOR desde formato custom de bytes y
// llama a EtwWriteTransfer. Auto-fill 2 UserData descriptors.
// Direccion original: 0x140001000
// ================================================================

NTSTATUS EtwWriteWrapper(
	__int64                 a1,
	unsigned __int8* a2,
	const GUID* ActivityId,
	const GUID* RelatedActivityId,
	ULONG                   UserDataCount,
	PEVENT_DATA_DESCRIPTOR  UserData)
{
	EVENT_DESCRIPTOR EventDescriptor;

	// Construir EVENT_DESCRIPTOR desde formato custom [HECHO]
	*(DWORD*)&EventDescriptor.Id = *a2 << 24;
	*(DWORD*)&EventDescriptor.Level = *(unsigned __int16*)(a2 + 1);
	EventDescriptor.Keyword = *(ULONGLONG*)(a2 + 3);

	// Auto-fill descriptor 0 desde la estructura de contexto [HECHO]
	UserData->Ptr = *(ULONGLONG*)(a1 + 8);
	UserData->Size = **(unsigned __int16**)(a1 + 8);
	UserData->Reserved = 2;

	// Auto-fill descriptor 1 desde los datos raw [HECHO]
	UserData[1].Ptr = (ULONGLONG)(a2 + 11);
	UserData[1].Size = *(unsigned __int16*)(a2 + 11);
	UserData[1].Reserved = 1;

	return EtwWriteTransfer(
		*(REGHANDLE*)(a1 + 32),
		&EventDescriptor,
		ActivityId,
		RelatedActivityId,
		UserDataCount,
		UserData);
}

// ================================================================
// ShouldLog — helper de verificación de logging
// ================================================================
// Verifica: lista no vacía && TipoBus >= nivel && Flags bit 1
// [HECHO] Patrón repetido en TODAS las funciones del driver
// ================================================================

BOOLEAN ShouldLog(ULONG MinTipoBus)
{
	// [STUB] Verificar contra DeviceObject real cuando esté completo
	// if (DeviceObject != &g_DeviceListHead_Sentinel
	//     && g_DeviceListHead_Sentinel->TipoBus >= MinTipoBus
	//     && (g_DeviceListHead_Sentinel->Flags & 2) != 0)
	//     return TRUE;
	UNREFERENCED_PARAMETER(MinTipoBus);
	return TRUE;
}

// ================================================================
// GetLogContextPtr — helper para obtener el contexto de log
// ================================================================
// [HECHO] Devuelve DeviceObject->ContextPtr (offset +0x18)
// ================================================================

PVOID GetLogContextPtr(VOID)
{
	// [STUB] Cuando DeviceObject tenga struct completo:
	// return ((PDEVICE_LIST_HEAD)DeviceObject)->ContextPtr;
	return DeviceObject;
}