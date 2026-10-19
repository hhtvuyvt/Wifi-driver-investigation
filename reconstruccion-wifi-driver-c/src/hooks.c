#include "include/driver.h"

void Custom_Realtek_DriverUnload(PDRIVER_OBJECT DriverObject)
{
	typedef void (*UNLOAD_FN)(PDRIVER_OBJECT);
	UNLOAD_FN original = (UNLOAD_FN)g_Original_DriverUnload;
	if (original != NULL && original != Custom_Realtek_DriverUnload)
		original(DriverObject);
	EvtDriverCleanup_Or_Destructor();
}

__int64 j_EvtDriverCleanup(void)
{
	return (__int64)EvtDriverCleanup_Or_Destructor();
}