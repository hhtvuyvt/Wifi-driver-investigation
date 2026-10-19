---
tags: [project, index]
---

# Realtek WiFi Driver — Reconstrucción en C

Proyecto de reconstrucción de un driver WiFi Realtek
(desofuscado desde .sys) a código C funcional.

## Estructura del código

| Archivo | Función | Estado | Doc |
|---------|---------|--------|-----|
| `driver_entry.c` | [[DriverEntry]] | ✅ Completo | [[DriverEntry]] |
| `wdf_bind_class_table.c` | [[WdfBindClassTable]] | ✅ Completo | [[WdfBindClassTable]] |
| `phase2_post_bind_init.c` | [[Phase2_PostBindInit]] | ✅ Completo | [[Phase2_PostBindInit]] |
| `register_device.c` | [[RegisterDeviceOrReportAnomaly]] | ⬜ Pendiente | — |
| `cleanup.c` | [[EvtDriverCleanup]] | ⬜ Pendiente | — |
| `hooks.c` | [[Custom_DriverUnload]] | ⬜ Pendiente | — |
| `globals.c` | Variables globales | ✅ | [[_Glossary]] |

## Tipos compartidos

Definidos en `src/include/wdf_types.h`:

- `WDF_BIND_INFO` (0x30) — [[WdfBindClassTable]]
- `WDF_CLASS_BIND_ENTRY` (0x50) — [[WdfBindClassTable]]
- `PHASE2_ENTRY` (0x28) — [[Phase2_PostBindInit]]
- `WDF_DRIVER_GLOBALS` — [[DriverEntry]]

## Flujo de ejecución

[[DriverEntry]] → [[WdfBindClassTable]] → [[Phase2_PostBindInit]] → ...