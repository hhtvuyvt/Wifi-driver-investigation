#include "include/driver.h"

NDIS_STATUS WdiAllocateAdapter(
	NDIS_HANDLE MiniportAdapterHandle,
	PVOID WdiParams, PVOID WdiAdapterContext,
	PVOID WdiCharacteristics, PVOID OutContext)
{
	UNREFERENCED_PARAMETER(MiniportAdapterHandle);
	UNREFERENCED_PARAMETER(WdiParams);
	UNREFERENCED_PARAMETER(WdiAdapterContext);
	UNREFERENCED_PARAMETER(WdiCharacteristics);
	UNREFERENCED_PARAMETER(OutContext);
	// TODO: reconstruir desde análisis de WdiAllocateAdapter
	return STATUS_SUCCESS;
}

VOID MiniportNoop(PVOID Adapter) {
	UNREFERENCED_PARAMETER(Adapter);
}