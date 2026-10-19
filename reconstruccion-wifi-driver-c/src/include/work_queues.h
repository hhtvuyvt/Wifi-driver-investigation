#ifndef WORK_QUEUES_H
#define WORK_QUEUES_H

#include "wdf_types.h"

#define ETW_TAG_PHASE_BEGIN     90
#define ETW_TAG_PHASE_END       91
#define FLAG_TRACING_ENABLED    0x40000000

__int64 __fastcall NdisSetupCallbacks(PVOID DriverObject, PVOID NdisHandle);
NTSTATUS InitNamedQueue(PNAMED_QUEUE Queue, const char* Name);
VOID     InitMemoryQueue(VOID);
VOID     InitWifiQueues(VOID);
VOID     InitTimerQueues(VOID);
VOID     PostQueueInit(VOID);
VOID     PostTraceInitA(VOID);
VOID     PostTraceInitB(VOID);
VOID     PostTraceInitC(VOID);
VOID     PostTraceInitD(VOID);
VOID     PostTraceInitE(VOID);

#endif