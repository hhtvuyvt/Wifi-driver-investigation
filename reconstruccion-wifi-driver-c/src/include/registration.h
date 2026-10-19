#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "wdf_types.h"

// Constantes
#define NDIS_VERSION_MIN_6_50       0x60032
#define NDIS_HEADER_MAGIC           0x98028A
#define NDIS_INIT_PARAMS_SIZE       152
#define WDF_CONFIG_SIZE             32
#define WDF_CONFIG_FLAGS            2

// ETW Tags
#define ETW_TAG_PREINIT             10
#define ETW_TAG_WDF_FAIL            11
#define ETW_TAG_WDF_OK              12
#define ETW_TAG_NDIS_VERSION        16
#define ETW_TAG_NDIS_OLD            17
#define ETW_TAG_NDIS_REG_FAIL       18
#define ETW_TAG_ERROR_GENERAL       19
#define ETW_TAG_NDIS_REG_OK         20

// Funciones principales
__int64 __fastcall RegisterDeviceOrReportAnomaly(
	PDRIVER_OBJECT DriverObject, PCUNICODE_STRING RegistryPath);

// Funciones internas
VOID     LogEventInit(VOID);
VOID     RegisterDevicesOrWmi(PDRIVER_OBJECT, PCUNICODE_STRING);
VOID     InitCallbackState(PULONG, PVOID, PVOID);
VOID     CleanupCallbackState(VOID);
NTSTATUS EtwRegisterIfNotRegistered(LPCGUID, PVOID, PVOID, PREGHANDLE);
VOID     EtwEnableCallback(VOID);
VOID     InitModuleA(VOID);
VOID     InitModuleB(VOID);
VOID     InitModuleC(VOID);
NTSTATUS NdisRegisterMiniport(PDRIVER_OBJECT, PCUNICODE_STRING, PVOID);
VOID     InitGlobalDebugContext(VOID);
VOID     memset_wrapper(PVOID, int, SIZE_T, ULONG);

// Logging
__int64  LogSimple(PVOID Ctx, ULONG Tag, PVOID Data);
__int64  LogRich(PVOID Ctx, ULONG Tag, PVOID Data, ULONG P1, ULONG P2, ULONG P3);
__int64  LogEventNoName(PVOID Ctx, ULONG Tag, PVOID Data, ULONG Err);
__int64  LogNamedEvent(PVOID Ctx, ULONG Tag, PVOID Data, const char* Name);
NTSTATUS EtwWriteWrapper(
	__int64 a1,
	unsigned __int8* a2,
	const GUID* ActivityId,
	const GUID* RelatedActivityId,
	ULONG UserDataCount,
	PEVENT_DATA_DESCRIPTOR UserData);

// Funciones de InitDeviceContext
PVOID    InitDeviceContext(PDEVICE_SUB_COMPONENT Table);

#endif