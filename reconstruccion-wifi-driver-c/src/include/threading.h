#ifndef THREADING_H
#define THREADING_H

#include "wdf_types.h"

#define THREAD_EVENT_ALLOC_SIZE     0x50
#define THREAD_EVENT_TIMEOUT_MS     2000
#define THREAD_NAME_MAX             36

#define ETW_TAG_THREAD_ALLOC_FAIL   50
#define ETW_TAG_THREAD_SKIP         56
#define ETW_TAG_THREAD_RUNNING      57
#define ETW_TAG_THREAD_TIMEOUT      58
#define ETW_TAG_THREAD_CREATE_FAIL  59

NTSTATUS CreateAdapterThread(PVOID Adapter, PVOID ThreadCtx, PVOID StartRoutine,
	const char* Name, UCHAR Priority, LONG StackSize, PVOID Param);
NTSTATUS StartAdapterThread(PVOID Adapter, PVOID ThreadCtx, UCHAR Priority, PVOID Param);
void     ThreadStartWrapper(PVOID StartContext);
NTSTATUS SignalThreadA(PVOID Adapter, PVOID ThreadCtx, UCHAR Priority, PVOID Param);
NTSTATUS SignalThreadB(PVOID Adapter, PVOID ThreadCtx, PVOID Arg1, PVOID Arg2);
NTSTATUS CreateWorkItem(PVOID, PVOID, PVOID, PVOID, const char*);
VOID     StringCopyBounded(char* Dest, const char* Src, ULONG MaxLen);

#endif