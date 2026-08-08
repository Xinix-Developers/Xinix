#pragma once

#include <stdint.h>

typedef struct [[gnu::packed]] sdt_header {
    char signature[4];
    uint32_t length;
    uint8_t revision;
    uint8_t checksum;
    char oemid[6];
    char oem_table_id[8];
    uint32_t oem_revision;
    uint32_t creator_id;
    uint32_t creator_revision;
} sdt_header_t;

typedef struct rsdt {
    sdt_header_t header;
    uint32_t entries[]; // flexible
} rsdt_t;

typedef struct [[gnu::packed]] xsdt {
    sdt_header_t header;
    uint64_t entries[]; // flexible
} xsdt_t;

typedef struct madt {
    sdt_header_t header;
    uint32_t local_apic_address;
    uint32_t flags;
} madt_header_t;

extern void load_system_descriptor_tables(void);
