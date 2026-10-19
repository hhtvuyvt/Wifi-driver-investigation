// ================================================================
// wdf_types.h — Tipos custom del driver
// Única fuente de verdad para todos los tipos custom.
// NO redefine tipos del WDK.
// ================================================================

#ifndef WDF_TYPES_H
#define WDF_TYPES_H

#pragma warning(push)
#pragma warning(disable: 4201)
#include <ntddk.h>
#include <ntstrsafe.h>
#include <ndis.h>
#pragma warning(pop)

// ================================================================
// Constantes
// ================================================================

#define REGISTRY_PATH_BUF_SIZE          0x208
#define WDF_CLASS_ENTRY_SIZE            0x50

// ================================================================
// WDF_VERSION
// ================================================================

typedef struct _WDF_VERSION {
	ULONG Major;
	ULONG Minor;
	ULONG Build;
} WDF_VERSION;

// ================================================================
// WDF_BIND_INFO
// ================================================================

typedef struct _WDF_BIND_INFO {
	ULONG           Size;
	const char* ComponentName;
	WDF_VERSION     Version;
	ULONG           FuncCount;
	PVOID           FuncTable;
	PVOID           Out0;
} WDF_BIND_INFO, * PWDF_BIND_INFO;

// ================================================================
// DRV_WDF_CONFIG — nuestra versión del config WDF
// (el WDK tiene WDF_DRIVER_CONFIG con campos diferentes)
// ================================================================

typedef struct _DRV_WDF_CONFIG {
	ULONG   Size;
	PVOID   EvtDriverUnload;
	ULONG   Flags;
} DRV_WDF_CONFIG;

// ================================================================
// WDF_CLASS_BIND_ENTRY (0x50 bytes)
// ================================================================

typedef NTSTATUS(*PFN_CUSTOM_CLASS_BIND)(PVOID, PWDF_BIND_INFO, PVOID, PVOID);
typedef NTSTATUS(*PFN_CUSTOM_CLASS_UNBIND)(PVOID, PWDF_BIND_INFO, PVOID, PVOID);

typedef struct _WDF_CLASS_BIND_ENTRY {
	ULONG   Size;
	UCHAR   Reserved1[0x34];
	PVOID   CustomBindFn;
	PVOID   CustomUnbindFn;
	UCHAR   Reserved2[0x08];
} WDF_CLASS_BIND_ENTRY, * PWDF_CLASS_BIND_ENTRY;

// ================================================================
// DEVICE_LIST_HEAD
// ================================================================

typedef struct _DEVICE_LIST_HEAD {
	PVOID   Flink;
	PVOID   Blink;
	PVOID   Unknown1;
	PVOID   ContextPtr;
	UCHAR   Pad1[9];
	UCHAR   TipoBus;
	UCHAR   Pad2[2];
	ULONG   Flags;
	UCHAR   Pad3[36];
} DEVICE_LIST_HEAD;

// ================================================================
// DEVICE_SUB_COMPONENT (0x40 bytes)
// ================================================================

typedef struct _DEVICE_SUB_COMPONENT {
	PVOID   State;
	PVOID   Name;
	PVOID   Context;
	PVOID   Reserved1;
	PVOID   Flags;
	PVOID   IsActive;
	PVOID   Reserved2;
	PVOID   Reserved3;
} DEVICE_SUB_COMPONENT, * PDEVICE_SUB_COMPONENT;

// ================================================================
// NAMED_QUEUE (0x48 bytes)
// ================================================================

typedef struct _NAMED_QUEUE {
	LIST_ENTRY  ListHead;
	KSPIN_LOCK  Lock;
	PVOID       Unknown1;
	ULONG       State;
	CHAR        Name[36];
} NAMED_QUEUE, * PNAMED_QUEUE;

// ================================================================
// ADAPTER_THREAD_CONTEXT
// ================================================================

#define THREAD_STATE_READY      0x01
#define THREAD_STATE_STARTING   0x02
#define THREAD_STATE_STARTED    0x08
#define THREAD_STATE_STOPPING   0x10
#define THREAD_STATE_RUNNING    0x40

typedef struct _ADAPTER_THREAD_CONTEXT {
	PVOID   Adapter;
	UCHAR   State;
	UCHAR   Pad1[7];
	PVOID   Event;
	PVOID   Param;
	PVOID   StartRoutine;
	PVOID   ThreadHandle;
	USHORT  ActiveCount;
	USHORT  CompletedCount;
	UCHAR   Priority;
	CHAR    Name[36];
	UCHAR   Flag;
} ADAPTER_THREAD_CONTEXT, * PADAPTER_THREAD_CONTEXT;

// ================================================================
// ADAPTER_THREAD_EVENT (0x50 bytes)
// ================================================================

typedef struct _ADAPTER_THREAD_EVENT {
	NDIS_EVENT  ReadyEvent;
	NDIS_EVENT  StopEvent;
	KSPIN_LOCK  Lock;
	KIRQL       SavedIrql;
	PVOID       KThread;
} ADAPTER_THREAD_EVENT, * PADAPTER_THREAD_EVENT;

// ================================================================
// ADAPTER_STATE_MACHINE
// ================================================================

#define ADAPTER_STATE_ALLOCATED     1
#define ADAPTER_STATE_POST_DEVICE   3
#define ADAPTER_STATE_CONFIGURED    11
#define ADAPTER_STATE_HW_INIT       4
#define ADAPTER_STATE_POST_INIT     13
#define ADAPTER_STATE_PRE_PNP       7

typedef struct _ADAPTER_STATE_MACHINE {
	UCHAR   Count;
	UCHAR   Pad[3];
	ULONG   States[32];
} ADAPTER_STATE_MACHINE;

// ================================================================
// WDI_ADAPTER_CONTEXT
// ================================================================

typedef struct _WDI_ADAPTER_CONTEXT {
	ULONG   Header;
	PVOID   Adapter;
	ULONG   CapabilitiesSize;
	ULONG   Version;
} WDI_ADAPTER_CONTEXT, * PWDI_ADAPTER_CONTEXT;

// ================================================================
// EVENT_DATA_DESC
// ================================================================

typedef struct _EVENT_DATA_DESC {
	ULONGLONG   Ptr;
	ULONG       Size;
	ULONG       Type;
} EVENT_DATA_DESC;

// ================================================================
// NDIS_MINIPORT_DRIVER_WDI_CHARACTERISTICS (custom)
// ================================================================

typedef struct _NDIS_MINIPORT_DRIVER_WDI_CHARACTERISTICS {
	NDIS_OBJECT_HEADER  Header;
	ULONG               WdiVersion;
	PVOID               AllocateAdapterHandler;
	PVOID               FreeAdapterHandler;
	PVOID               OpenAdapterHandler;
	PVOID               CloseAdapterHandler;
	PVOID               TalTxRxInitializeHandler;
	PVOID               TalTxRxDeinitializeHandler;
	PVOID               HangDiagnoseHandler;
	PVOID               StartOperationHandler;
	PVOID               StopOperationHandler;
	PVOID               PostPauseHandler;
	PVOID               LeIdleNotificationHandler;
} NDIS_MINIPORT_DRIVER_WDI_CHARACTERISTICS;

// ================================================================
// WIFI_ADAPTER (placeholder ~8.5MB)
// ================================================================

typedef struct _WIFI_ADAPTER {
	NDIS_HANDLE     MiniportAdapterHandle;
	UCHAR           Pad1[0x18];
	PDEVICE_OBJECT  PhysicalDeviceObject;
	PDEVICE_OBJECT  FunctionalDeviceObject;
	PDEVICE_OBJECT  NextDeviceObject;
	UCHAR           DeviceStackDepth;
	UCHAR           Pad2[0x07];
	PVOID           WdfDeviceContext;
	UCHAR           Pad3[0x6C8];
	PVOID           SubStruct13;
	UCHAR           Pad4[0x778];
	USHORT          DeviceId;
	UCHAR           Pad5[0x06];
	PVOID           WdiParams;
	UCHAR           Pad6[0x18B8];
	ADAPTER_STATE_MACHINE StateMachine;
	UCHAR           Unknown[8000000];
} WIFI_ADAPTER, * PWIFI_ADAPTER;

// ================================================================
// Function pointer types
// ================================================================

typedef NTSTATUS(*PFN_WDF_DRIVER_CREATE)(PVOID, PDRIVER_OBJECT, PCUNICODE_STRING, PVOID, PVOID, PVOID);
typedef NTSTATUS(*PFN_WDF_DEVICE_CREATE)(PVOID, PVOID, PVOID, PDEVICE_OBJECT, PDEVICE_OBJECT, PDEVICE_OBJECT, PVOID);
typedef NTSTATUS(*PFN_WDF_VERSION_BIND_CLASS)(PWDF_BIND_INFO, PVOID, PVOID);
typedef VOID(*PFN_THREAD_START_ROUTINE)(PVOID);

// ================================================================
// PFN_LOG_DISPATCH — dispatcher central de logging
// ================================================================

typedef NTSTATUS(*PFN_LOG_DISPATCH)(
	PVOID       ContextPtr,
	ULONG       EventType,
	PVOID       LogData,
	ULONG       Tag,
	PVOID       Desc0,
	ULONG       Size0,
	PVOID       Desc1,
	ULONG       Size1,
	PVOID       Desc2,
	ULONG       Size2,
	PVOID       Terminator);

#endif // WDF_TYPES_H