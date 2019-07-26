nasm -felf32 boot.asm -o debug/boot.o
i686-elf-gcc -c src/kernel.c src/common.c -o debug/kernel.o -std=gnu99 -ffreestanding -masm=intel -O2 -Wall -Wextra
i686-elf-gcc -T src/linker.ld -o debug/mountainos.bin -ffreestanding -O2 -nostdlib debug/boot.o debug/kernel.o -lgcc
set /p run="Run? (requires QEMU) (y/n) "
if %run% EQU y qemu-system-i386 -kernel debug/mountainos.bin
pause