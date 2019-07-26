nasm -felf32 boot.asm -o boot.o
i686-elf-gcc -c kernel.c common.c -o kernel.o -std=gnu99 -ffreestanding -masm=intel -O2 -Wall -Wextra
i686-elf-gcc -T linker.ld -o mountainos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
set /p run="Run? (requires QEMU) (y/n) "
if %run% EQU y qemu-system-i386 -kernel mountainos.bin
pause