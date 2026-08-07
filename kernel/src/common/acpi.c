#include <acpi.h>
#include <auxv.h>
#include <stdio.h>

void print_sdt_header(sdt_header_t *sdt_p) {
    printf("Table %.4s\r\n", sdt_p->signature);
    printf("OEMID: %.6s\r\n", sdt_p->oemid);
    printf("OEM Table ID: %.8s\r\n", sdt_p->oem_table_id);
    printf("OEM Revision: %08X\r\n", sdt_p->oem_revision);         // TODO: %d
    printf("Creator ID: %08X\r\n", sdt_p->creator_id);             // TODO: %d
    printf("Creator Revision: %08X\r\n", sdt_p->creator_revision); // TODO: %d
}

void load_xsdt(void) {
    xsdt_t *xsdt_p = getauxval(AT_KXINIX_XSDT_ADDR).a_ptr;
    print_sdt_header(&xsdt_p->header);

    // TODO: read structures
}

void load_rsdt(void) {
    rsdt_t *rsdt_p = getauxval(AT_KXINIX_RSDT_ADDR).a_ptr;
    print_sdt_header(&rsdt_p->header);

    // TODO: read structures
}

void load_system_descriptor_tables(void) {
    if (getauxval(AT_KXINIX_XSDT_ADDR).a_val) {
        load_xsdt();
    } else {
        load_rsdt();
    }
}
