#ifndef CLEANUP_H
#define CLEANUP_H

#include "wdf_types.h"

NTSTATUS EvtDriverCleanup_Or_Destructor(VOID);
void     PreUnbind_Cleanup(PWDF_BIND_INFO BindInfo);

#endif