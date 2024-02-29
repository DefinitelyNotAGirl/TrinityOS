qemu-system-x86_64 -drive file=geos.img,if=ide -d in_asm,int,cpu_reset -cpu qemu64 -no-reboot -no-shutdown -m 2G -smp 1 -bios /usr/share/edk2-ovmf/x64/OVMF.fd 2> /GEOS_LOG/qemu.log
