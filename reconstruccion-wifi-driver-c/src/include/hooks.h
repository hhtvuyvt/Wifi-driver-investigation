#ifndef HOOKS_H
#define HOOKS_H

#include "wdf_types.h"

void    Custom_Realtek_DriverUnload(PDRIVER_OBJECT DriverObject);
__int64 j_EvtDriverCleanup(void);

#endif