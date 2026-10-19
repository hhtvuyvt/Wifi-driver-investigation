#include "include/driver.h"

extern NTSTATUS WdfVersionBind(PDRIVER_OBJECT, PUNICODE_STRING, PWDF_BIND_INFO, PVOID);
extern NTSTATUS WdfBindClassTable(PWDF_BIND_INFO);
extern NTSTATUS Phase2_PostBindInit(VOID);

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	NTSTATUS status;

	if (DriverObject == NULL)
		return (NTSTATUS)RegisterDeviceOrReportAnomaly(NULL, RegistryPath);

	g_DriverObject_Backup = DriverObject;
	DestinationString.Buffer = RegistryPathBuffer;
	DestinationString.Length = 0;
	DestinationString.MaximumLength = REGISTRY_PATH_BUF_SIZE;
	RtlCopyUnicodeString(&DestinationString, RegistryPath);

	status = WdfVersionBind(DriverObject, &DestinationString, &g_WdfBindInfo, &pWdfGlobals);
	if (status < 0)
		return status;

	if ((status = WdfBindClassTable(&g_WdfBindInfo)) < 0 ||
		(status = Phase2_PostBindInit()) < 0 ||
		(status = (NTSTATUS)RegisterDeviceOrReportAnomaly(DriverObject, RegistryPath)) < 0)
	{
		EvtDriverCleanup_Or_Destructor();
		return status;
	}

	if (*(UCHAR*)((PUCHAR)pWdfGlobals + 0x30) != 0) {
		if (DriverObject->DriverUnload != NULL)
			g_Original_DriverUnload = (PVOID)DriverObject->DriverUnload;
		DriverObject->DriverUnload = Custom_Realtek_DriverUnload;
	}
	else if (*(ULONG*)((PUCHAR)pWdfGlobals + 0x08) & 0x2) {
		g_Internal_Wifi_Callback_Backup = g_Internal_Wifi_Callback;
		g_Internal_Wifi_Callback = (PVOID)EvtDriverCleanup_Or_Destructor;
	}

	return STATUS_SUCCESS;
}