#include "include/driver.h"

__int64 __fastcall RegisterDeviceOrReportAnomaly(
	PDRIVER_OBJECT DriverObject, PCUNICODE_STRING RegistryPath)
{
	InitDeviceContext((PDEVICE_SUB_COMPONENT)g_DeviceContext);
	LogEventInit();
	*(PVOID*)((PUCHAR)g_DeviceContext + 0x40) = NULL; // CurrentIrp
	RegisterDevicesOrWmi(DriverObject, RegistryPath);
	InitCallbackState(&g_InitState, NULL, NULL);

	if (g_InitState > 4) {
		ULONG64 etwData = (ULONG64)DriverObject;
		ULONG etwLen[2] = { RegistryPath->Length, 0 };
		EVENT_DATA_DESCRIPTOR descs[5] = { 0 };
		descs[0].Ptr = (ULONGLONG)&etwData; descs[0].Size = 8;
		descs[1].Ptr = (ULONGLONG)etwLen; descs[1].Type = 2;
		EtwWriteWrapper((ULONG)(ULONG_PTR)&g_InitState, dword_140594EB9, NULL, NULL, 5, descs);
	}

	EtwRegisterIfNotRegistered(&g_EtwProviderGuid, (PVOID)EtwEnableCallback,
		&g_EtwCallbackContext, &g_EtwRegHandle);

	if (ShouldLog(4)) LogSimple(GetLogContextPtr(), 10, g_LogContext);

	InitModuleA(); InitModuleB();
	KeInitializeSpinLock(&g_DeviceListLock);
	g_DriverObject = DriverObject;
	InitializeListHead(&g_DeviceList);
	InitializeListHead(&g_CallbackList);
	g_DeviceListHead = &g_DeviceList;
	g_CallbackListHead = &g_CallbackList;

	{
		UNICODE_STRING localDest = { 0 };
		localDest.Buffer = RegistryPathBuffer2;
		localDest.Length = 0;
		localDest.MaximumLength = 0x200;
		RtlCopyUnicodeString(&localDest, RegistryPath);
	}
	InitModuleC();

	{
		DRV_WDF_CONFIG cfg = { 0 };
		NTSTATUS wdfStatus;
		cfg.Size = 32; cfg.EvtDriverUnload = NULL; cfg.Flags = 2;
		wdfStatus = ((PFN_WDF_DRIVER_CREATE)g_WdfDriverCreateFn)(
			pWdfGlobals, DriverObject, RegistryPath, NULL, &cfg, NULL);
		if (wdfStatus < 0) {
			if (ShouldLog(2)) LogRich(GetLogContextPtr(), 11, g_LogContext, (ULONG)wdfStatus, 32, cfg.Size);
			goto ERROR_CLEANUP;
		}
		if (ShouldLog(4)) LogSimple(GetLogContextPtr(), 12, g_LogContext);
	}

	{
		UCHAR ndisParams[NDIS_INIT_PARAMS_SIZE] = { 0 };   // ← buffer raw
		UINT ndisVersion;
		UCHAR ndisMinor; USHORT ndisMajor;
		NTSTATUS ndisStatus;

		ndisVersion = NdisGetVersion();
		ndisMinor = (UCHAR)ndisVersion;
		if (ndisVersion < NDIS_VERSION_MIN_6_50) {
			if (ShouldLog(2)) LogSimple(GetLogContextPtr(), 17, g_LogContext);
			goto ERROR_CLEANUP;
		}
		ndisMajor = HIWORD(ndisVersion);
		if (ShouldLog(4)) LogRich(GetLogContextPtr(), 16, g_LogContext, ndisVersion, ndisMajor, (USHORT)ndisVersion);

		// NDIS_OBJECT_HEADER: Type=0x02, Size=0x98, Revision=0x8A
		ndisParams[0] = 0x02;
		ndisParams[1] = NDIS_INIT_PARAMS_SIZE;
		ndisParams[2] = 0x8A;
		// MajorNdisVersion
		ndisParams[4] = (UCHAR)ndisMajor;
		// MinorNdisVersion
		ndisParams[5] = ndisMinor;
		// MaxNumberOfInterfaces = 1
		*(USHORT*)&ndisParams[6] = 1;

		_mm_lfence();
		ndisStatus = NdisRegisterMiniport(DriverObject, RegistryPath, ndisParams);
		if (ndisStatus != 0) {
			if (ShouldLog(2)) LogEventNoName(GetLogContextPtr(), 18, g_LogContext, (ULONG)ndisStatus);
			goto ERROR_CLEANUP;
		}
	}

	InitializeListHead(&g_AdapterList);
	g_AdapterListHead = &g_AdapterList;
	if (ShouldLog(5)) LogEventNoName(GetLogContextPtr(), 20, g_LogContext, 0);
	NdisSetupCallbacks(DriverObject, NdisMiniportDriverHandle);
	goto EXIT;

ERROR_CLEANUP:
	if (ShouldLog(2)) LogEventNoName(GetLogContextPtr(), 19, g_LogContext, 0xC0000001);
	{
		REGHANDLE saved = g_EtwSystemRegHandle;
		g_EtwSystemRegHandle = 0;
		g_InitState = 0;
		EtwUnregister(saved);
	}
	CleanupCallbackState();

EXIT:
	InitGlobalDebugContext();
	return 1;
}