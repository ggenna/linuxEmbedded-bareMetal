1- Download the compilation tool:
http://www.mentor.com/embedded-software/sourcery-tools/sourcery-codebench/editions/lite-edition/

2- Porting the C libraries for ARM:
ftp://sources.redhat.com/pub/newlib/index

3- Install the two packages.
to compile the C library for ARM run:
./configure --target arm-none-eabi --disable-newlib-supplied-syscalls
make

4- Extract the u-boot bootloader sources and compile:
- ./xCompilare.sh
- copy the MLO and u-boot.img executables to the boot partition of the beagleboard sd memory card

5- Extract the bsp_1v1.tar.gz archive

6- Edit the make.cfg and make_main.cfg and configure the following points:
- U-BOOT = path where the bootloader sources were extracted at point 4
- LIBNEW = path where the libm.a library is installed (installed with the package at point 2)
- INCLIBA = path of the include directory of the archive installed at point 2
- INCLIBGCC = path of the include directory of the archive installed at point 1

6- edit the main.c source file in the src/main folder

7- To compile, run the make command from the main directory, where the i package containing the drivers has been extracted.

8- copy the uEnv.txt file and the src/main/kernel.bin file to the boot partition of the beagleboard sd memory card (the beagleboard must have been previously configured with the u-boot bootloader)