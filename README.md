# MBRHelloWorld

MBR HelloWorld example written in c

## How to make

Just type `make`

## How to test this MBR

Install qemu, and type `qemu-system-x86_64 boot.MBR`.

## Work with GRUB

It work with grub stage2 or stage1.5 perfectly. You can test this MBR work with GRUB stage2 images by fellowing command:

```sh
cat boot.MBR stage2 > tmpdisk && qemu-system-x86_64 tmpdisk
```

If you will not install stage1.5 into sector 1, you should set `BOOTLOADER_START_SECTOR` to compile it.

	make CFLAGS="-DBOOTLOADER_START_SECTOR=12"
	
## Loading your custom bootloader at specific address

Just set `BOOTLOADER_LOAD_ADDRESS` to boot.

	make CFLAGS="-BOOTLOADER_LOAD_ADDRESS=0x7000"

This MBR will pass 
	
## Work with MBR partition table

Sure! It work perfectly. This is hexdump of our MBR, the partition table fill with nop, so we do not need worry about partition table.

```dump
00000000  e9 54 00 66 55 66 89 c2  66 89 e5 66 53 67 8a 0a  |.T.fUf..f..fSg..|
00000010  84 c9 74 0d 66 42 bb 01  00 b4 0e 88 c8 cd 10 eb  |..t.fB..........|
00000020  ec 66 5b 66 5d 66 c3 66  55 66 89 c2 66 89 e5 66  |.f[f]f.fUf..f..f|
00000030  b8 00 42 00 00 66 56 66  be 14 7d 00 00 cd 13 72  |..B..fVf..}....r|
00000040  02 eb 0e 66 b8 24 7d 00  00 66 e8 b4 ff ff ff eb  |...f.$}..f......|
00000050  fe 66 5e 66 5d 66 c3 66  55 66 89 e5 66 53 88 d3  |.f^f]f.fUf..fS..|
00000060  66 b8 30 7d 00 00 66 e8  97 ff ff ff 66 0f b6 c3  |f.0}..f.....f...|
00000070  66 e8 b1 ff ff ff 66 b8  3f 7d 00 00 66 e8 81 ff  |f.....f.?}..f...|
00000080  ff ff 66 b8 14 7d 00 00  89 c6 30 f6 88 da 66 b8  |..f..}....0...f.|
00000090  00 80 00 00 66 ff e0 00  14 00 00 00 00 00 00 00  |....f...........|
000000a0  01 7a 52 00 01 7c 08 01  1b 0c 04 04 88 01 00 00  |.zR..|..........|
000000b0  20 00 00 00 1c 00 00 00  4b ff ff ff 24 00 00 00  | .......K...$...|
000000c0  00 42 0e 08 85 02 46 0d  05 42 83 03 56 c3 42 c5  |.B....F..B..V.B.|
000000d0  0c 04 04 00 20 00 00 00  40 00 00 00 4b ff ff ff  |.... ...@...K...|
000000e0  30 00 00 00 00 42 0e 08  85 02 46 0d 05 48 86 03  |0....B....F..H..|
000000f0  5c c6 42 c5 0c 04 04 00  18 00 00 00 64 00 00 00  |\.B.........d...|
00000100  57 ff ff ff 40 00 00 00  00 42 0e 08 85 02 43 0d  |W...@....B....C.|
00000110  05 42 83 03 10 00 01 00  00 80 00 00 01 00 00 00  |.B..............|
00000120  00 00 00 00 42 6f 6f 74  20 66 61 69 6c 65 64 00  |....Boot failed.|
00000130  48 65 6c 6c 6f 20 57 6f  72 6c 64 21 0d 0a 00 42  |Hello World!...B|
00000140  6f 6f 74 20 62 6f 6f 74  6c 6f 61 64 65 72 2e 2e  |oot bootloader..|
00000150  2e 0d 0a 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000160  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000170  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000180  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000190  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000001a0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000001b0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000001c0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000001d0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000001e0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000001f0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 55 aa  |..............U.|
```
	
## Known issue

It will not worked if you are running on non supported LBA BIOS.

## License

WTFPL
