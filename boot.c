/* barebone from http://dc0d32.blogspot.tw/2010/06/real-mode-in-c-with-gcc-writing.html */
#define SECTOR_SIZE 512
#ifndef BOOTLOADER_TYPE
#define BOOTLOADER_TYPE
/* This is default GRUB boot parameter */
#define BOOTLOADER_RUNNING_ADDRESS 0x8200
#define BOOTLOADER_LOAD_ADDRESS 0x8000
#endif

#ifndef BOOTLOADER_START_SECTOR
#define BOOTLOADER_START_SECTOR 1
#endif

#ifndef BOOTLOADER_SIZE
#define BOOTLOADER_SIZE 131368
#endif
#define BOOTLOADER_SIZE_SECTOR (BOOTLOADER_SIZE/SECTOR_SIZE + ((BOOTLOADER_SIZE%SECTOR_SIZE)?1:0))


asm(".code16gcc\n");
asm ("jmp main\n") ;

#define __NOINLINE  __attribute__((noinline))
#define __REGPARM   __attribute__ ((regparm(3)))
#define __NORETURN  __attribute__((noreturn))

struct lba_reader_packet
{
	unsigned short struct_size;				/* struct's size ( 0x10 or  0x18 )*/
	unsigned short sectors;							/* read size of sectors */
	unsigned int bootloader_load_address;		/* buffer address */
	unsigned long long start_sector;
} ; /* struct from http://www.mouseos.com/win7/int_0x13.html */

struct lba_reader_packet lbapkt = {
		.struct_size = sizeof(struct lba_reader_packet),
		.sectors = BOOTLOADER_SIZE_SECTOR,						/* bootloader size of sector */
		.bootloader_load_address = BOOTLOADER_LOAD_ADDRESS,		/* bootloader memory loaded address */
		.start_sector = BOOTLOADER_START_SECTOR				/* bootloader start sector */
		};
		
void __NOINLINE __REGPARM print(const char *s) {
	while(*s)
		asm volatile ("int  $0x10" : : "a"(0x0E00 | *s++), "b"(7));
}

int __NOINLINE __REGPARM lba_load_sector(unsigned char boot_drive) {
	asm volatile goto ("int $0x13\njc %l[failed]"
		: 
		: "a"(0x4200), "d"(boot_drive), "S"(&lbapkt)
		:"cc"
		: failed);
return 0;
failed:
return 1;
}

/* and for everything else you can use C! Be it traversing the filesystem, or verifying the kernel image etc.*/
void __NORETURN main(){
 	unsigned char   bios_drive = 0;
	asm volatile("movb  %%dl, %0" : "=r"(bios_drive));      /* the BIOS drive number of the device we booted from is passed in dl register */
	print("Hello World!\r\n");
	if( lba_load_sector(bios_drive)) {
		print("Load bootloader Failed");
		while(1);
	}
	print("Boot bootloader...\r\n");
	asm volatile ("" : : "d"(bios_drive));
	goto *((void *) BOOTLOADER_RUNNING_ADDRESS);
}

