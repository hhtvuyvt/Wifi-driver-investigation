// ================================================================
// Phase2_PostBindInit — Gate 2 de DriverEntry
// Documentacion: docs/Phase2_PostBindInit.md
// Direccion original: 0x14007BF30
// ================================================================

#include "include/driver.h"

NTSTATUS Phase2_PostBindInit(VOID)
{
    PUCHAR start = Phase2_Table;
    PUCHAR end = Phase2_Table + sizeof(Phase2_Table);

    // Sanity check anti-tamper [HECHO]
    if (start > end)
        return STATUS_INVALID_IMAGE_FORMAT;

    PPHASE2_ENTRY entry = (PPHASE2_ENTRY)start;

    while ((PUCHAR)entry < end) {
        // Validar magic del entry [HECHO]
        if (entry->Size != PHASE2_ENTRY_SIZE)
            return STATUS_INFO_LENGTH_MISMATCH;

        // Invocar InitFn si existe [HECHO]
        // Sin error check: tolerancia a fallos
        if (entry->InitFn != NULL) {
            PHASE2_INIT_FN fn = (PHASE2_INIT_FN)entry->InitFn;
            entry->InitResult = fn();
        }

        // Siguiente entry [HECHO]
        entry = (PPHASE2_ENTRY)((PUCHAR)entry + PHASE2_ENTRY_SIZE);
    }

    return STATUS_SUCCESS;
}