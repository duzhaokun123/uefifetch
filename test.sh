#!/usr/bin/env bash

mkdir -p ./esp/EFI/BOOT
cp -v "./cmake-build-$ARCH/src/uefifetch.efi" ./esp
echo "FS0:" > ./esp/EFI/BOOT/startup.nsh
echo uefifetch.efi >> ./esp/EFI/BOOT/startup.nsh

qemu_exe=qemu-system-$ARCH

if [ ! -x "$(command -v "$qemu_exe")" ]; then
  qemu_exe=$qemu_exe.exe
fi

if [ ! -x "$(command -v "$qemu_exe")" ]; then
  echo "qemu-system-$ARCH not found"
  exit 1
fi

if [ ! -f "$OVMF" ]; then
  echo "OVMF not found"
  exit 1
fi

$qemu_exe --version

$qemu_exe $QEMU_EXT_ARGS \
  -bios "$OVMF" \
  -cpu max \
  -drive file=fat:rw:./esp,format=raw \
  -serial stdio \
  -vga none \
  -device virtio-gpu \
  -device qemu-xhci \
  -device usb-kbd \
#  -device usb-tablet \
