#include "include/driver.h"

// ── Funciones externas ────────────────────────────────────
extern NTSTATUS WdfVersionBindClass(PWDF_BIND_INFO, PVOID, PVOID);

NTSTATUS WdfBindClassTable(PWDF_BIND_INFO BindInfo)
{
	UNREFERENCED_PARAMETER(BindInfo);
	if ((ULONG_PTR)&ClassBindTable_Header > (ULONG_PTR)&ClassBindTable_Entries)
		return STATUS_INVALID_IMAGE_FORMAT;
	return STATUS_SUCCESS;
}