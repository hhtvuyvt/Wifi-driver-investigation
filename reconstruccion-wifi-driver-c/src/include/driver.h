// ================================================================
// driver.h — Header maestro del driver reconstruido
// ================================================================

#ifndef DRIVER_H
#define DRIVER_H

#include "wdf_types.h"

// Macros auxiliares
#define MAKEWORD(a,b)   ((USHORT)(((UCHAR)(a)) | ((USHORT)((UCHAR)(b))) << 8))
#define MAKELONG(a,b)   ((ULONG)(((USHORT)(a)) | ((ULONG)((USHORT)(b))) << 16))
#define LOWORD(l)       ((USHORT)((ULONG)(l) & 0xFFFF))
#define HIWORD(l)       ((USHORT)(((ULONG)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)       ((UCHAR)((ULONG)(w) & 0xFF))

// ================================================================
// Includes de módulos
// ================================================================

#include "registration.h"
#include "hooks.h"
#include "cleanup.h"
#include "work_queues.h"
#include "wdi_adapter.h"
#include "threading.h"

// ================================================================
// Globales compartidas (definidas en globals.c)
// ================================================================

// DriverEntry
extern UNICODE_STRING   DestinationString;
extern WCHAR            RegistryPathBuffer[REGISTRY_PATH_BUF_SIZE];
extern PVOID            pWdfGlobals;
extern PVOID            g_DriverObject_Backup;
extern PVOID            g_Original_DriverUnload;
extern PVOID            g_Internal_Wifi_Callback;
extern PVOID            g_Internal_Wifi_Callback_Backup;
extern WDF_BIND_INFO    g_WdfBindInfo;

// Class Bind Table
extern UCHAR            ClassBindTable_Header[16];
extern UCHAR            ClassBindTable_Entries[WDF_CLASS_ENTRY_SIZE];
extern PVOID            g_CurrentClassEntry;

// Phase2 Table
extern UCHAR            Phase2_Table_Start[16];
extern UCHAR            Phase2_Table_End[16];

// RegisterDeviceOrReportAnomaly
extern PVOID            g_DriverObject;
extern PVOID            g_DeviceContext;
extern ULONG            g_InitState;
extern ULONG            g_OperationMode;
extern KSPIN_LOCK       g_DeviceListLock;
extern LIST_ENTRY       g_DeviceList;
extern LIST_ENTRY       g_CallbackList;
extern LIST_ENTRY       g_AdapterList;
extern LIST_ENTRY* g_DeviceListHead;
extern LIST_ENTRY* g_CallbackListHead;
extern LIST_ENTRY* g_AdapterListHead;
extern WCHAR            RegistryPathBuffer2[260];

// ETW
extern REGHANDLE        g_EtwSystemRegHandle;
extern REGHANDLE        g_EtwRegHandle;
extern GUID             g_EtwProviderGuid;
extern PVOID            g_EtwCallbackContext;
extern PVOID            g_LogContext;
extern PVOID            g_LogContextPhase;
extern PVOID            dword_140594EB9;
extern PVOID            dword_140594F03;
extern PVOID            dword_140594F38;
extern PVOID            dword_140594AF8;

// DeviceObject sentinel (logging)
extern PVOID            DeviceObject;

// NDIS
extern PVOID            NdisMiniportDriverHandle;
extern PVOID            NdisObjectHandle;
extern PVOID            g_DriverObject2;

// WDF FuncTable
extern PVOID            g_WdfDriverCreateFn;
extern PVOID            g_WdfDeviceCreateFn;
extern PVOID            g_DeviceRegisterFn;

// ── Logging dispatcher ──
extern PVOID            g_LogDispatchFn;

// Debug
extern PVOID            g_GlobalDebugContext;

// Work Queues
extern NAMED_QUEUE      g_NicQueue;
extern NAMED_QUEUE      g_MemoryQueue;
extern NAMED_QUEUE      g_WifiIdleQueue;
extern NAMED_QUEUE      g_WifiSystemQueue;
extern NAMED_QUEUE      g_TimerIdleQueue;
extern NAMED_QUEUE      g_TimerSystemQueue;
extern NAMED_QUEUE      g_GlobalThreadQueue;
extern NAMED_QUEUE      g_TraceQueue;
extern KSPIN_LOCK       g_MemoryQueueLock;
extern KSPIN_LOCK       g_WifiStateLock;
extern KSPIN_LOCK       g_TimerStateLock;
extern UCHAR            g_WifiActiveFlag;
extern UCHAR            g_TimerActiveFlag;
extern KIRQL            g_WifiSavedIrql;
extern KIRQL            g_TimerSavedIrql;
extern ULONG            g_TimerActiveCount;

// WDI Adapter
extern ULONG            g_AdapterCount;
extern PVOID            g_AdapterHandle;
extern ULONG            g_PciErrorFlags;

// Sub-component names (data)
extern UCHAR            g_SubCompName_DeviceExt[16];
extern UCHAR            g_SubCompName_WcbQueue[16];
extern UCHAR            g_SubCompName_DevQueue[16];
extern UCHAR            g_SubCompName_Dpc[16];
extern UCHAR            g_SubCompName_Reserved[16];
extern UCHAR            g_SubCompName_Terminator[16];

// ================================================================
// Helpers compartidos (definidos en stubs.c)
// ================================================================

BOOLEAN ShouldLog(ULONG MinTipoBus);
PVOID   GetLogContextPtr(VOID);

#endif // DRIVER_H