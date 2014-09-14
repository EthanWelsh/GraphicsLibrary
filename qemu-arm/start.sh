#!/bin/sh
qemu-system-arm -kernel zImage -cpu arm1176 -m 256 -M versatilepb -no-reboot \
-serial stdio -initrd piCore.gz -append \
"root=/dev/ram0 elevator=deadline rootwait quiet nozswap nortc noswap tce=sda1 home=sda1" \
-hda disk.qcow2 
