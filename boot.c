/* barebone from http://dc0d32.blogspot.tw/2010/06/real-mode-in-c-with-gcc-writing.html */
__asm__(".code16gcc\n");
__asm__ ("jmpl  $0, $main\n");
#define __NOINLINE  __attribute__((noinline))
#define __REGPARM   __attribute__ ((regparm(3)))
#define __NORETURN  __attribute__((noreturn))

struct buffer_packet
{
	short buffer_packet_size;         /* struct's size ( 0x10 or  0x18 )*/
	short sectors;                    /* read size of sectors */
	char * buffer;                     /* buffer address */
	long long start_sectors;
	long long *l_buffer;              /* 64 bit buffer address */
} ; /* struct from http://www.mouseos.com/win7/int_0x13.html */

struct buffer_packet buffer = {
	.buffer_packet_size=0x10,
	.sectors=5,
	.buffer=(char *)0x8000,
	.start_sectors=1
	};
 
/* BIOS interrupts must be done with inline assembly */
void __NOINLINE __REGPARM print(const char *s) {
	while(*s)
		__asm__ __volatile__ ("int  $0x10" : : "a"(0x0E00 | *s++), "b"(7));
}

void __NOINLINE __REGPARM load_sector(unsigned char boot_drive) {
	__asm__ __volatile__ ("int $0x13" : : "a"(0x4200), "d"(boot_drive), "S"(&buffer):"cc");
}

/* and for everything else you can use C! Be it traversing the filesystem, or verifying the kernel image etc.*/
void __NORETURN main(){
 	unsigned char   bios_drive = 0;
	__asm__ __volatile__("movb  %%dl, %0" : "=r"(bios_drive));      /* the BIOS drive number of the device we booted from is passed in dl register */
	print("Hello World!\r\n");
	load_sector(bios_drive);
	//__asm__ ("jmpl  $0, $0x8200");
	while(1);
}

