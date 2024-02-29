qemu-system-x86_64 -drive format=raw,file=geos.img -d in_asm,int,cpu_reset -no-reboot -no-shutdown -m 2G -smp 1 2> /GEOS_LOG/qemu.log
