#include "include/driver.h"

NTSTATUS InitNamedQueue(PNAMED_QUEUE Queue, const char* Name)
{
	Queue->ListHead.Flink = &Queue->ListHead;
	Queue->ListHead.Blink = &Queue->ListHead;
	KeInitializeSpinLock(&Queue->Lock);
	Queue->State = 0;
	if (Name != NULL) StringCopyBounded(Queue->Name, Name, 36);
	return STATUS_SUCCESS;
}

VOID InitMemoryQueue(VOID)
{
	InitNamedQueue(&g_MemoryQueue, "os_mem_q");
	KeInitializeSpinLock(&g_MemoryQueueLock);
}

VOID InitWifiQueues(VOID)
{
	KIRQL irql;
	KeInitializeSpinLock(&g_WifiStateLock);
	irql = KeAcquireSpinLockRaiseToDpc(&g_WifiStateLock);
	g_WifiActiveFlag = 0;
	g_WifiSavedIrql = irql;
	KeReleaseSpinLock(&g_WifiStateLock, irql);
	InitNamedQueue(&g_WifiIdleQueue, "wiidleq");
	InitNamedQueue(&g_WifiSystemQueue, "wisysq");
}

VOID InitTimerQueues(VOID)
{
	KIRQL irql;
	KeInitializeSpinLock(&g_TimerStateLock);
	irql = KeAcquireSpinLockRaiseToDpc(&g_TimerStateLock);
	g_TimerActiveCount = 0;
	g_TimerSavedIrql = irql;
	g_TimerActiveFlag = 0;
	KeReleaseSpinLock(&g_TimerStateLock, irql);
	InitNamedQueue(&g_TimerIdleQueue, "tmridleq");
	InitNamedQueue(&g_TimerSystemQueue, "tmrsysq");
}

VOID PostQueueInit(VOID)
{
	InitNamedQueue(&g_TraceQueue, "tcb_traceq");
	PostTraceInitA(); PostTraceInitB(); PostTraceInitC();
	PostTraceInitD(); PostTraceInitE();
}

VOID PostTraceInitA(VOID) {}
VOID PostTraceInitB(VOID) {}
VOID PostTraceInitC(VOID) {}
VOID PostTraceInitD(VOID) {}
VOID PostTraceInitE(VOID) {}

__int64 __fastcall NdisSetupCallbacks(PVOID DriverObject, PVOID NdisHandle)
{
	__int64 result = 0;
	if (ShouldLog(4)) LogNamedEvent(GetLogContextPtr(), 90, g_LogContextPhase, "OS_driver_init");
	NdisObjectHandle = NdisHandle;
	g_DriverObject2 = DriverObject;
	InitNamedQueue(&g_NicQueue, "nicq");
	InitMemoryQueue();
	InitWifiQueues();
	InitTimerQueues();
	InitNamedQueue(&g_GlobalThreadQueue, "gthread_q");
	PostQueueInit();
	if (ShouldLog(4)) LogNamedEvent(GetLogContextPtr(), 91, g_LogContextPhase, "OS_driver_init");
	return result;
}