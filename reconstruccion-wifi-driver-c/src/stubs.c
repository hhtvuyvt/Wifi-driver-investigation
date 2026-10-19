// ================================================================
// stubs.c — Stubs para funciones pendientes de análisis
// ================================================================

#include "include/driver.h"

// ── WdfBindClassTable ────────────────────────────────────

extern NTSTATUS WdfVersionBindClass(PWDF_BIND_INFO, PVOID, PVOID);

// ── Phase2_PostBindInit ──────────────────────────────────

NTSTATUS Phase2_PostBindInit(VOID)
{
	if ((ULONG_PTR)&Phase2_Table_Start <= (ULONG_PTR)&Phase2_Table_End)
		return STATUS_SUCCESS;
	return STATUS_INVALID_IMAGE_FORMAT;
}

// ── InitDeviceContext ─────────────────────────────────────

PVOID InitDeviceContext(PDEVICE_SUB_COMPONENT Table)
{
	PVOID ctx = g_DeviceContext;
	Table[0].State = 0; Table[0].Name = g_SubCompName_DeviceExt;
	Table[0].Context = (PVOID)((PUCHAR)ctx + 0x00); Table[0].Flags = 0; Table[0].IsActive = (PVOID)1;
	Table[1].State = 0; Table[1].Name = g_SubCompName_WcbQueue;
	Table[1].Context = (PVOID)((PUCHAR)ctx + 0x30); Table[1].Flags = 0; Table[1].IsActive = (PVOID)1;
	Table[2].State = 0; Table[2].Name = g_SubCompName_DevQueue;
	Table[2].Context = (PVOID)((PUCHAR)ctx + 0x20); Table[2].Flags = 0; Table[2].IsActive = (PVOID)1;
	Table[3].State = 0; Table[3].Name = g_SubCompName_Dpc;
	Table[3].Context = (PVOID)((PUCHAR)ctx + 0x48); Table[3].Flags = 0; Table[3].IsActive = (PVOID)1;
	Table[4].State = 0; Table[4].Name = g_SubCompName_Reserved;
	Table[4].Context = (PVOID)((PUCHAR)ctx + 0x50); Table[4].Flags = 0; Table[4].IsActive = (PVOID)1;
	Table[5].State = 0; Table[5].Name = g_SubCompName_Terminator;
	Table[5].Context = NULL; Table[5].Flags = 0; Table[5].IsActive = (PVOID)1;
	return g_SubCompName_Terminator;
}

// ── Funciones de inicialización ───────────────────────────

VOID LogEventInit(VOID) {}
VOID RegisterDevicesOrWmi(PDRIVER_OBJECT a, PCUNICODE_STRING b) { UNREFERENCED_PARAMETER(a); UNREFERENCED_PARAMETER(b); }
VOID InitCallbackState(PULONG a, PVOID b, PVOID c) { UNREFERENCED_PARAMETER(a); UNREFERENCED_PARAMETER(b); UNREFERENCED_PARAMETER(c); }
VOID CleanupCallbackState(VOID) {}
NTSTATUS EtwRegisterIfNotRegistered(LPCGUID a, PVOID b, PVOID c, PREGHANDLE d) {
	UNREFERENCED_PARAMETER(a); UNREFERENCED_PARAMETER(b); UNREFERENCED_PARAMETER(c);
	if (*d != 0) return STATUS_SUCCESS;
	return STATUS_SUCCESS;
}
VOID EtwEnableCallback(VOID) {}
VOID InitModuleA(VOID) {}
VOID InitModuleB(VOID) {}
VOID InitModuleC(VOID) {}
VOID InitGlobalDebugContext(VOID) {}
VOID memset_wrapper(PVOID Dest, int Value, SIZE_T Size, ULONG Unused) {
	UNREFERENCED_PARAMETER(Value); UNREFERENCED_PARAMETER(Unused);
	RtlZeroMemory(Dest, Size);
}

// ── NDIS ──────────────────────────────────────────────────

NTSTATUS NdisRegisterMiniport(PDRIVER_OBJECT a, PCUNICODE_STRING b, PVOID c) {
	UNREFERENCED_PARAMETER(a); UNREFERENCED_PARAMETER(b); UNREFERENCED_PARAMETER(c);
	return STATUS_SUCCESS;
}

// ── WDI Adapter stubs ─────────────────────────────────────

PVOID AllocInitialResource(VOID) { return NULL; }
NTSTATUS AllocateAdapterContext(PVOID* Adapter, NDIS_HANDLE Handle) {
	UNREFERENCED_PARAMETER(Handle); *Adapter = NULL; return STATUS_UNSUCCESSFUL;
}
VOID InitPostDeviceCreation(VOID) {}
VOID InitComponentA(VOID) {}
VOID InitComponentB(VOID) {}
NTSTATUS InitHwStep1(VOID) { return STATUS_SUCCESS; }
NTSTATUS ConfigAdapter(PVOID a, PVOID b, PVOID c, PVOID d) {
	UNREFERENCED_PARAMETER(a); UNREFERENCED_PARAMETER(b); UNREFERENCED_PARAMETER(c); UNREFERENCED_PARAMETER(d);
	return STATUS_SUCCESS;
}
BOOLEAN PciCheckDevice(VOID) { return FALSE; }
BOOLEAN CheckResourceAvailability(PVOID a, USHORT b) {
	UNREFERENCED_PARAMETER(a); UNREFERENCED_PARAMETER(b); return FALSE;
}
VOID InitPreHw(VOID) {}
VOID InitComponentC(VOID) {}
NTSTATUS InitHwMain(VOID) { return STATUS_SUCCESS; }
VOID InitPhyMac(PVOID a, UCHAR b) { UNREFERENCED_PARAMETER(a); UNREFERENCED_PARAMETER(b); }
VOID InitComponentD(VOID) {}
VOID InitComponentE(VOID) {}
VOID InitComponentF(VOID) {}
VOID InitPrePciCheck(VOID) {}
NTSTATUS PciValidate(VOID) { return STATUS_SUCCESS; }
VOID InitComponentG(VOID) {}
VOID InitComponentH(VOID) {}
VOID InitComponentI(VOID) {}
VOID InitComponentJ(VOID) {}
VOID InitComponentK(VOID) {}
VOID InitComponentL(VOID) {}
VOID InitComponentM(VOID) {}
NTSTATUS PostInitFinal(VOID) { return STATUS_SUCCESS; }
VOID PrePostInit(VOID) {}
VOID SaveStateSnapshot(PVOID a, PVOID b) { UNREFERENCED_PARAMETER(a); UNREFERENCED_PARAMETER(b); }
VOID InitConditionalA(VOID) {}
VOID InitConditionalB(VOID) {}
VOID InitConditionalC(VOID) {}
VOID InitConditionalD(VOID) {}

// ── Thread handlers ───────────────────────────────────────

VOID RxHandleInterruptThread(VOID) {}
VOID InterruptThreadHandler(VOID) {}
VOID TaskThreadHandler(VOID) {}
VOID PropertyThreadHandler(VOID) {}
VOID PnpWorkItemHandler(VOID) {}

// ── Threading stubs ───────────────────────────────────────

NTSTATUS CreateAdapterThread(PVOID a, PVOID b, PVOID c, const char* d, UCHAR e, LONG f, PVOID g) {
	UNREFERENCED_PARAMETER(a); UNREFERENCED_PARAMETER(b); UNREFERENCED_PARAMETER(c);
	UNREFERENCED_PARAMETER(d); UNREFERENCED_PARAMETER(e); UNREFERENCED_PARAMETER(f); UNREFERENCED_PARAMETER(g);
	return STATUS_SUCCESS;
}
NTSTATUS StartAdapterThread(PVOID a, PVOID b, UCHAR c, PVOID d) {
	UNREFERENCED_PARAMETER(a); UNREFERENCED_PARAMETER(b); UNREFERENCED_PARAMETER(c); UNREFERENCED_PARAMETER(d);
	return STATUS_SUCCESS;
}
void ThreadStartWrapper(PVOID a) { UNREFERENCED_PARAMETER(a); }
NTSTATUS SignalThreadA(PVOID a, PVOID b, UCHAR c, PVOID d) {
	UNREFERENCED_PARAMETER(a); UNREFERENCED_PARAMETER(b); UNREFERENCED_PARAMETER(c); UNREFERENCED_PARAMETER(d);
	return STATUS_SUCCESS;
}
NTSTATUS SignalThreadB(PVOID a, PVOID b, PVOID c, PVOID d) {
	UNREFERENCED_PARAMETER(a); UNREFERENCED_PARAMETER(b); UNREFERENCED_PARAMETER(c); UNREFERENCED_PARAMETER(d);
	return STATUS_SUCCESS;
}
NTSTATUS CreateWorkItem(PVOID a, PVOID b, PVOID c, PVOID d, const char* e) {
	UNREFERENCED_PARAMETER(a); UNREFERENCED_PARAMETER(b); UNREFERENCED_PARAMETER(c);
	UNREFERENCED_PARAMETER(d); UNREFERENCED_PARAMETER(e);
	return STATUS_SUCCESS;
}
VOID StringCopyBounded(char* Dest, const char* Src, ULONG MaxLen) {
	ULONG i = 0;
	while (i < MaxLen - 1 && Src[i]) { Dest[i] = Src[i]; i++; }
	Dest[i] = 0;
}
