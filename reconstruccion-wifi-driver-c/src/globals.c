#include "include/driver.h"

// ── DriverEntry ──
UNICODE_STRING   DestinationString = { 0 };
WCHAR            RegistryPathBuffer[REGISTRY_PATH_BUF_SIZE] = { 0 };
PVOID            pWdfGlobals = NULL;
PVOID            g_DriverObject_Backup = NULL;
PVOID            g_Original_DriverUnload = NULL;
PVOID            g_Internal_Wifi_Callback = NULL;
PVOID            g_Internal_Wifi_Callback_Backup = NULL;
WDF_BIND_INFO    g_WdfBindInfo = { 0 };

// ── Class Bind Table ──
UCHAR   ClassBindTable_Header[16] = { 0 };
UCHAR   ClassBindTable_Entries[WDF_CLASS_ENTRY_SIZE] = { 0 };
PVOID   g_CurrentClassEntry = NULL;

// ── Phase2 Table ──
UCHAR   Phase2_Table_Start[16] = { 0 };
UCHAR   Phase2_Table_End[16] = { 0 };

// ── RegisterDeviceOrReportAnomaly ──
PVOID   g_DriverObject = NULL;
PVOID   g_DeviceContext = NULL;
ULONG   g_InitState = 0;
ULONG   g_OperationMode = 0;
KSPIN_LOCK  g_DeviceListLock = 0;
LIST_ENTRY  g_DeviceList = { 0 };
LIST_ENTRY  g_CallbackList = { 0 };
LIST_ENTRY  g_AdapterList = { 0 };
LIST_ENTRY* g_DeviceListHead = NULL;
LIST_ENTRY* g_CallbackListHead = NULL;
LIST_ENTRY* g_AdapterListHead = NULL;
WCHAR   RegistryPathBuffer2[260] = { 0 };

// ── ETW ──
REGHANDLE   g_EtwSystemRegHandle = 0;
REGHANDLE   g_EtwRegHandle = 0;
GUID        g_EtwProviderGuid = { 0 };
PVOID       g_EtwCallbackContext = NULL;
PVOID       g_LogContext = NULL;
PVOID       g_LogContextPhase = NULL;
PVOID       dword_140594EB9 = NULL;
PVOID       dword_140594F03 = NULL;
PVOID       dword_140594F38 = NULL;
PVOID       dword_140594AF8 = NULL;

// ── DeviceObject sentinel ──
PVOID   DeviceObject = NULL;

// ── NDIS ──
PVOID   NdisMiniportDriverHandle = NULL;
PVOID   NdisObjectHandle = NULL;
PVOID   g_DriverObject2 = NULL;

// ── WDF FuncTable ──
PVOID   g_WdfDriverCreateFn = NULL;
PVOID   g_WdfDeviceCreateFn = NULL;
PVOID   g_DeviceRegisterFn = NULL;

// ── Logging dispatcher ──
PVOID   g_LogDispatchFn = NULL;

// ── Debug ──
PVOID   g_GlobalDebugContext = NULL;

// ── Work Queues ──
NAMED_QUEUE g_NicQueue = { 0 };
NAMED_QUEUE g_MemoryQueue = { 0 };
NAMED_QUEUE g_WifiIdleQueue = { 0 };
NAMED_QUEUE g_WifiSystemQueue = { 0 };
NAMED_QUEUE g_TimerIdleQueue = { 0 };
NAMED_QUEUE g_TimerSystemQueue = { 0 };
NAMED_QUEUE g_GlobalThreadQueue = { 0 };
NAMED_QUEUE g_TraceQueue = { 0 };
KSPIN_LOCK  g_MemoryQueueLock = 0;
KSPIN_LOCK  g_WifiStateLock = 0;
KSPIN_LOCK  g_TimerStateLock = 0;
UCHAR   g_WifiActiveFlag = 0;
UCHAR   g_TimerActiveFlag = 0;
KIRQL   g_WifiSavedIrql = 0;
KIRQL   g_TimerSavedIrql = 0;
ULONG   g_TimerActiveCount = 0;

// ── WDI Adapter ──
ULONG   g_AdapterCount = 0;
PVOID   g_AdapterHandle = NULL;
ULONG   g_PciErrorFlags = 0;

// ── Sub-component names ──
UCHAR   g_SubCompName_DeviceExt[16] = { 0 };
UCHAR   g_SubCompName_WcbQueue[16] = { 0 };
UCHAR   g_SubCompName_DevQueue[16] = { 0 };
UCHAR   g_SubCompName_Dpc[16] = { 0 };
UCHAR   g_SubCompName_Reserved[16] = { 0 };
UCHAR   g_SubCompName_Terminator[16] = { 0 };