#!/usr/bin/env bash

print_usage() {
  echo "Usage: $0 --arch <arch> --ovmf <ovmf_path> --build <build_path> [--help] [-- <qemu_args>]"
  echo "  -a --arch <arch>        Architecture to use (x86_64, aarch64, etc.)"
  echo "  -f --ovmf <ovmf_path>   Path to OVMF firmware"
  echo "  -b --build <build_path> Path to the build directory"
  echo "  -- <qemu_args>          Additional arguments to pass to QEMU"
  echo "  -h --help               Show this help message"
  echo "Example: $0 --arch x86_64 --ovmf /path/to/OVMF.fd --build /path/to/build"
}

if [ $# == 0 ]; then
    print_usage
    exit 1
fi

ARGS=$(getopt -o a:f:b:h --long arch:,ovmf:,build:,help -n "$0" -- "$@")
if [ $? != 0 ]; then
  echo "Invalid arguments"
  exit 1
fi

eval set -- "$ARGS"

while true; do
    case $1 in
    -a|--arch)
      arch="$2"
      shift 2
      ;;
    -f|--ovmf)
      ovmf="$2"
      shift 2
      ;;
    -b|--build)
      build="$2"
      shift 2
      ;;
    -h|--help)
      print_usage
      exit 0
      ;;
    --)
      shift
      break
      ;;
    esac
done

if [[ $ovmf == ?:* ]]; then
    echo -n "wslpath: $ovmf"
    ovmf=$(wslpath -u "$ovmf")
    echo " -> $ovmf"
fi

if [[ $build == ?:* ]]; then
    echo -n "wslpath: $build"
    build=$(wslpath -u "$build")
    echo " -> $build"
fi

mkdir -p ./esp/EFI/BOOT
cp -v "$build"/*.efi ./esp
echo "FS0:" > ./esp/EFI/BOOT/startup.nsh

qemu_exe=qemu-system-$arch

if [ ! -x "$(command -v "$qemu_exe")" ]; then
  qemu_exe=$qemu_exe.exe
fi

if [ ! -x "$(command -v "$qemu_exe")" ]; then
  echo "qemu-system-$arch not found"
  exit 1
fi

$qemu_exe --version

$qemu_exe "$@" \
  -bios "$ovmf" \
  -cpu max \
  -drive file=fat:rw:./esp,format=raw \
  -serial stdio \
  -vga none \
  -device virtio-gpu \
  -device qemu-xhci \
  -device usb-kbd \
#  -device usb-tablet \
