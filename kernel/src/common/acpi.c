#include <acpi.h>
#include <auxv.h>
#include <stdio.h>

void print_sdt_header(sdt_header_t *sdt_p) {
    printf("Table %.4s\r\n", sdt_p->signature);
    printf("OEMID: %.6s -- Table ID: %.8s -- Revision: %08X\r\n", sdt_p->oemid,
           sdt_p->oem_table_id, sdt_p->oem_revision); // TODO: %d
    printf("               Creator ID: %08X -- Revision: %08X\r\n\r\n",
           sdt_p->creator_id,
           sdt_p->creator_revision); // TODO: %d
}

void load_xsdt(void) {
    xsdt_t *xsdt_p = getauxval(AT_KXINIX_XSDT_ADDR).a_ptr;
    print_sdt_header(&xsdt_p->header);

    int num_sdts = (xsdt_p->header.length - sizeof(sdt_header_t)) / 8;
    size_t hhdm_offset = getauxval(AT_KXINIX_HHDM_OFFSET).a_val;
    for (int i = 0; i < num_sdts; i++) {
        print_sdt_header((sdt_header_t *)(hhdm_offset + xsdt_p->entries[i]));
    }
}

void load_rsdt(void) {
    rsdt_t *rsdt_p = getauxval(AT_KXINIX_RSDT_ADDR).a_ptr;
    print_sdt_header(&rsdt_p->header);

    int num_sdts = (rsdt_p->header.length - sizeof(sdt_header_t)) / 4;
    size_t hhdm_offset = getauxval(AT_KXINIX_HHDM_OFFSET).a_val;
    for (int i = 0; i < num_sdts; i++) {
        print_sdt_header((sdt_header_t *)(hhdm_offset + rsdt_p->entries[i]));
    }
}

void load_system_descriptor_tables(void) {
    if (getauxval(AT_KXINIX_XSDT_ADDR).a_val) {
        load_xsdt();
    } else {
        load_rsdt();
    }
}
