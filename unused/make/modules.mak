modules-all:
	$(MAKE) build -C modules/IDE out=OUT/kernel/IDE.module build=build/kernel_IDE/
	$(MAKE) build -C modules/INIT out=OUT/kernel/INIT.module build=build/kernel_INIT/
	$(MAKE) build -C modules/ACPI out=OUT/kernel/ACPI.module build=build/kernel_ACPI/
	$(MAKE) build -C modules/AHCI out=OUT/kernel/AHCI.module build=build/kernel_AHCI/
	$(MAKE) build -C modules/FUNCDIS out=OUT/kernel/FUNCDIS.module build=build/kernel_FUNCDIS/
	$(MAKE) build -C modules/PAGING out=OUT/kernel/PAGING.module build=build/kernel_PAGING/
	$(MAKE) build -C modules/SATA out=OUT/kernel/SATA.module build=build/kernel_SATA/
	$(MAKE) build -C modules/MALLOC out=OUT/kernel/MALLOC.module build=build/kernel_MALLOC/
	$(MAKE) build -C modules/COUT out=OUT/kernel/COUT.module build=build/kernel_COUT/
	$(MAKE) build -C modules/PCIe out=OUT/kernel/PCIe.module build=build/kernel_PCIe/
	$(MAKE) build -C modules/gfs0.fs out=OUT/kernel/gfs0.fs.module build=build/kernel_gfs0.fs/
	$(MAKE) build -C modules/Kernel out=OUT/kernel/Kernel.module build=build/kernel_Kernel/
	$(MAKE) build -C modules/ELF out=OUT/kernel/ELF.module build=build/kernel_ELF/

modules-IDE:
	$(MAKE) build -C modules/IDE out=OUT/kernel/IDE.module build=build/kernel_IDE/

modules-INIT:
	$(MAKE) build -C modules/INIT out=OUT/kernel/INIT.module build=build/kernel_INIT/

modules-ACPI:
	$(MAKE) build -C modules/ACPI out=OUT/kernel/ACPI.module build=build/kernel_ACPI/

modules-AHCI:
	$(MAKE) build -C modules/AHCI out=OUT/kernel/AHCI.module build=build/kernel_AHCI/

modules-FUNCDIS:
	$(MAKE) build -C modules/FUNCDIS out=OUT/kernel/FUNCDIS.module build=build/kernel_FUNCDIS/

modules-PAGING:
	$(MAKE) build -C modules/PAGING out=OUT/kernel/PAGING.module build=build/kernel_PAGING/

modules-SATA:
	$(MAKE) build -C modules/SATA out=OUT/kernel/SATA.module build=build/kernel_SATA/

modules-MALLOC:
	$(MAKE) build -C modules/MALLOC out=OUT/kernel/MALLOC.module build=build/kernel_MALLOC/

modules-COUT:
	$(MAKE) build -C modules/COUT out=OUT/kernel/COUT.module build=build/kernel_COUT/

modules-PCIe:
	$(MAKE) build -C modules/PCIe out=OUT/kernel/PCIe.module build=build/kernel_PCIe/

modules-gfs0.fs:
	$(MAKE) build -C modules/gfs0.fs out=OUT/kernel/gfs0.fs.module build=build/kernel_gfs0.fs/

modules-Kernel:
	$(MAKE) build -C modules/Kernel out=OUT/kernel/Kernel.module build=build/kernel_Kernel/

modules-ELF:
	$(MAKE) build -C modules/ELF out=OUT/kernel/ELF.module build=build/kernel_ELF/
