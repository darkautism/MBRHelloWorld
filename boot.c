__asm__(".code16gcc\n");
__asm__ ("jmpl  $0, $main\n");
#define __NOINLINE  __attribute__((noinline))
#define __REGPARM   __attribute__ ((regparm(3)))
#define __NORETURN  __attribute__((noreturn))
 
/* BIOS interrupts must be done with inline assembly */
void    __NOINLINE __REGPARM print(const char *s){
    while(*s){
        __asm__ __volatile__ ("int  $0x10" : : "a"(0x0E00 | *s), "b"(7));
        s++;
    }
}

void    __NOINLINE __REGPARM goo(void){
    __asm__ __volatile__ ("movb $0xC0, %ah");
    __asm__ __volatile__ ("int $0x15");
}


/* and for everything else you can use C! Be it traversing the filesystem, or verifying the kernel image etc.*/
 
void __NORETURN main(){
    goo();
    print("Hello World!\n");
    while(1);
}
