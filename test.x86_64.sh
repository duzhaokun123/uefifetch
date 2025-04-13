QEMU="$*"

mkdir -p ./esp/EFI/BOOT
cp -v ./cmake-build*/src/uefifetch.efi ./esp
echo "FS0:" > ./esp/EFI/BOOT/startup.nsh
echo uefifetch.efi >> ./esp/EFI/BOOT/startup.nsh

if [ -n "$QEMU" ]; then
  echo use "$QEMU" as the QEMU binary
elif [ -x "$(command -v qemu-system-x86_64)" ]; then
  QEMU=qemu-system-x86_64
elif [ -x "$(command -v qemu-system-x86_64.exe)" ]; then
  QEMU=qemu-system-x86_64.exe
fi

if [ -z "$QEMU" ]; then
  echo "QEMU not found"
  exit 1
fi

if [ ! -f "$OVMF" ]; then
  echo "OVMF not set"
  exit 1
fi

$QEMU --version

$QEMU -bios "$OVMF" -drive file=fat:rw:./esp,format=raw
