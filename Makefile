CC=gcc
CFLAGS=-static -Isrc -march=x86-64 -Ofast -ffast-math -flto=8 -ftree-vectorize -floop-interchange -ftree-loop-distribution -floop-strip-mine -floop-block -Wall
KERNEL=6.6
JOBS=$(shell nproc)

debug_program: CFLAGS += -g -D_DEBUG
debug_program: build_program

build: create_img create_initramfs build_program build_kernel cp_initramfs build_iso patch_grub

download_kernel:
	rm -rf "linux-kernel"
	curl "https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/snapshot/linux-$(KERNEL).tar.gz" -o "linux.tar.gz"
	tar -zxf "linux.tar.gz"
	rm "linux.tar.gz"
	mv "linux-$(KERNEL)" "linux-kernel"

build_kernel:
	cp config/linux.config linux-kernel/.config
	cd linux-kernel && \
	make "-j$(JOBS)" && \
	INSTALL_PATH=../build/mnt/boot make install
	rm -rf build/mnt/boot/*.old

create_initramfs:
	rm -rf build/initramfs/dev
	mkdir -p build/initramfs/dev build/initramfs/proc/sys/kernel
	mknod -m 622 build/initramfs/dev/console c 5 1
	mknod -m 622 build/initramfs/dev/tty0 c 4 0
	mknod -m 622 build/initramfs/dev/fb0 c 29 0
	echo 7 > build/initramfs/proc/sys/kernel/printk

cp_initramfs:
	cp linux-kernel/usr/initramfs_data.cpio "build/mnt/boot/initramfs-$(KERNEL).0.img"

create_img:
	mkdir -p build/mnt/boot/efi build/mnt/boot/grub
	cp config/grub.cfg build/mnt/boot/grub
	sed -i "s/VERSION/$(KERNEL)/g" build/mnt/boot/grub/grub.cfg

build_program:
	$(CC) $(CFLAGS) src/flame/**.c src/scene/**.c src/main.c -lm -o build/initramfs/init
	chmod +x build/initramfs/init

build_iso:
	grub-mkrescue -o LUMON.iso build/mnt

patch_grub:
	sed -i 's/Welcome to GRUB!/\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0/g' LUMON.iso

format:
	find src -iname "*.h" -o -iname "*.c" | xargs clang-format -style="{BasedOnStyle: Google, UseTab: Always, IndentWidth: 4, TabWidth: 4}" -i

clean:
	cd linux-kernel && make clean
	rm -rf build
