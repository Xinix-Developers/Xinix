#pragma once

#include <stdint.h>
#include <stddef.h>

#define ELFMAGIC "\x7FELF"

enum ElfClass : uint8_t {
    ELFCLASSNONE = 0,
    ELFCLASS32 = 1,
    ELFCLASS64 = 2,
};

enum ElfData : uint8_t {
    ELFDATANONE = 0,
    ELFDATA2LSB = 1,
    ELFDATA2MSB = 2,
};

enum ElfVersion : uint8_t {
    EV_NONE = 0,
    EV_CURRENT = 1,
};

enum ElfOsAbi : uint8_t {
    None = 0,
};

typedef struct {
    char ei_magic[4];
    enum ElfClass ei_class;
    enum ElfData ei_data;
    enum ElfVersion ei_version;
    enum ElfOsAbi ei_osabi;
    uint8_t ei_abiversion;
    uint8_t ei_pad[16-9];
} Elf_Ident;


typedef uint64_t Elf64_Addr;
typedef uint64_t Elf64_Size;
typedef int64_t Elf64_Off;

typedef uint8_t Elf64_Byte;
typedef uint16_t Elf64_Half;
typedef uint32_t Elf64_Word;
typedef uint64_t Elf64_Xword;
typedef int8_t Elf64_Sbyte;
typedef int16_t Elf64_Shalf;
typedef int32_t Elf64_Sword;
typedef int64_t Elf64_Sxword;

typedef struct {
        Elf_Ident   e_ident;
        uint16_t    e_type;
        uint16_t    e_machine;
        uint32_t    e_version;
        Elf64_Addr  e_entry;
        Elf64_Off   e_phoff;
        Elf64_Off   e_shoff;
        uint32_t    e_flags;
        uint16_t    e_ehsize;
        uint16_t    e_phentsize;
        uint16_t    e_phnum;
        uint16_t    e_shentsize;
        uint16_t    e_shnum;
        uint16_t    e_shstrndx;
} Elf64_Ehdr;

typedef struct {
	Elf64_Word	sh_name;
	Elf64_Word	sh_type;
	Elf64_Xword	sh_flags;
	Elf64_Addr	sh_addr;
	Elf64_Off	sh_offset;
	Elf64_Xword	sh_size;
	Elf64_Word	sh_link;
	Elf64_Word	sh_info;
	Elf64_Xword	sh_addralign;
	Elf64_Xword	sh_entsize;
} Elf64_Shdr;

typedef struct {
	Elf64_Word	st_name;
	uint8_t 	st_info;
	uint8_t 	st_other;
	Elf64_Half	st_shndx;
	Elf64_Addr	st_value;
	Elf64_Xword	st_size;
} Elf64_Sym;