# MBRHelloWorld
MBR HelloWorld example written in c

## How to make

Just type `make`

## How to test your own MBR

Install qemu, and type `qemu-system-x86_64 boot.MBR`.

## Work with GRUB

Get your grub stage2 or stage1.5 size, and set CFLAGS to compile it.

```shell
	root$ ls -l stage2 
	-rwxr--r--. 1 root root 126756  3月 15 21:31 stage2
	root$ make CFLAGS=-DBOOTLOADER_SIZE=126756
```

If you will not install stage1.5 into sector 1, you should also set `BOOTLOADER_START_SECTOR`

	make CFLAGS="-DBOOTLOADER_SIZE=126756 -DBOOTLOADER_START_SECTOR=12"
	
## Work with your custom bootloader

	Just set `BOOTLOADER_RUNNING_ADDRESS` and `BOOTLOADER_LOAD_ADDRESS` to boot.

## License

WTFPL
