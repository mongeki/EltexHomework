## Cross compilation

### Steps:
1. Create default configuration file
2. Build kernel with cross-compilator
3. Compile device tree source files
4. Copy bzImage and .dtb-file to a new folder
5. Run qemu

```console
ARCH=arm make defconfig
ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- make -j6 bzImage
ARCH=arm make dtbs
QEMU_AUDIO=none qemu-system-arm -M vexpress-a9 -kernel zImage -dtb vexpress-v2p-ca9.dtb -append "console=ttyAMA0" -nographic
```
![kernel_panic](/img/kernel_panic.png)
