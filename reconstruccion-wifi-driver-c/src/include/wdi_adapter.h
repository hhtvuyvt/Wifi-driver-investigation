#ifndef WDI_ADAPTER_H
#define WDI_ADAPTER_H

#include "wdf_types.h"

// Constantes
#define WDI_VERSION_1_1_9               0x00010109
#define WDI_VERSION_MIN                 WDI_VERSION_1_1_9
#define WDI_HEADER_MAGIC                0x007001C0
#define STATUS_NDIS_PCI_ERROR           ((NTSTATUS)0xC0010002)
#define PCI_DEVICE_ID_57                57
#define ADAPTER_ZERO_SIZE               0x7D0

// ETW Tags
#define ETW_TAG_ALLOC_BEGIN             24
#define ETW_TAG_WDI_VERSION             25
#define ETW_TAG_WDI_VERSION_LOW         26
#define ETW_TAG_WDF_DEVICE_FAIL         27
#define ETW_TAG_WDF_DEVICE_OK           28
#define ETW_TAG_INIT_HW1_FAIL           29
#define ETW_TAG_CONFIG_FAIL             30
#define ETW_TAG_PCI_CHECK_FAIL          31
#define ETW_TAG_INSUFFICIENT_RES        32
#define ETW_TAG_INIT_HW_FAIL            33
#define ETW_TAG_PCI_ALLOC_FAIL          34
#define ETW_TAG_POSTINIT_FAIL           35
#define ETW_TAG_PRECHECK_FAIL           36
#define ETW_TAG_ALLOC_SUCCESS           37
#define ETW_TAG_ALLOC_CLEANUP           38

// Función principal
NDIS_STATUS WdiAllocateAdapter(
	NDIS_HANDLE MiniportAdapterHandle,
	PVOID WdiParams, PVOID WdiAdapterContext,
	PVOID WdiCharacteristics, PVOID OutContext);

VOID MiniportNoop(PVOID Adapter);

// Stubs de init
PVOID    AllocInitialResource(VOID);
NTSTATUS AllocateAdapterContext(PVOID* Adapter, NDIS_HANDLE Handle);
VOID     InitPostDeviceCreation(VOID);
VOID     InitComponentA(VOID);
VOID     InitComponentB(VOID);
NTSTATUS InitHwStep1(VOID);
NTSTATUS ConfigAdapter(PVOID, PVOID, PVOID, PVOID);
BOOLEAN  PciCheckDevice(VOID);
BOOLEAN  CheckResourceAvailability(PVOID, USHORT);
VOID     InitPreHw(VOID);
VOID     InitComponentC(VOID);
NTSTATUS InitHwMain(VOID);
VOID     InitPhyMac(PVOID, UCHAR);
VOID     InitComponentD(VOID);
VOID     InitComponentE(VOID);
VOID     InitComponentF(VOID);
VOID     InitPrePciCheck(VOID);
NTSTATUS PciValidate(VOID);
VOID     InitComponentG(VOID);
VOID     InitComponentH(VOID);
VOID     InitComponentI(VOID);
VOID     InitComponentJ(VOID);
VOID     InitComponentK(VOID);
VOID     InitComponentL(VOID);
VOID     InitComponentM(VOID);
NTSTATUS PostInitFinal(VOID);
VOID     PrePostInit(VOID);
VOID     SaveStateSnapshot(PVOID, PVOID);
VOID     InitConditionalA(VOID);
VOID     InitConditionalB(VOID);
VOID     InitConditionalC(VOID);
VOID     InitConditionalD(VOID);

// Thread handlers
VOID RxHandleInterruptThread(VOID);
VOID InterruptThreadHandler(VOID);
VOID TaskThreadHandler(VOID);
VOID PropertyThreadHandler(VOID);
VOID PnpWorkItemHandler(VOID);

#endif