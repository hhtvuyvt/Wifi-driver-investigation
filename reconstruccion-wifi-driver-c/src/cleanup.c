#include "include/driver.h"

extern NTSTATUS WdfVersionUnbind(PUNICODE_STRING, PWDF_BIND_INFO, PVOID);
extern NTSTATUS WdfVersionUnbindClass(PWDF_BIND_INFO, PVOID, PVOID);

void PreUnbind_Cleanup(PWDF_BIND_INFO BindInfo)
{
	PWDF_CLASS_BIND_ENTRY entry = (PWDF_CLASS_BIND_ENTRY)&ClassBindTable_Entries;
	if (g_CurrentClassEntry == (PVOID)&ClassBindTable_Header ||
		(ULONG_PTR)&ClassBindTable_Entries > (ULONG_PTR)g_CurrentClassEntry)
		return;

	do {
		PFN_CUSTOM_CLASS_UNBIND fn = (PFN_CUSTOM_CLASS_UNBIND)entry->CustomUnbindFn;
		if (fn != NULL)
			fn((PVOID)WdfVersionUnbindClass, BindInfo, pWdfGlobals, entry);
		else
			WdfVersionUnbindClass(BindInfo, pWdfGlobals, entry);
		entry = (PWDF_CLASS_BIND_ENTRY)((PUCHAR)entry + WDF_CLASS_ENTRY_SIZE);
	} while (entry <= (PWDF_CLASS_BIND_ENTRY)g_CurrentClassEntry);
}

NTSTATUS EvtDriverCleanup_Or_Destructor(VOID)
{
	PreUnbind_Cleanup(&g_WdfBindInfo);
	return WdfVersionUnbind(&DestinationString, &g_WdfBindInfo, pWdfGlobals);
}