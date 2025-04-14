[English](README.md) 简体中文

# UEFI fetch

就像任何平台的任何 fetch，但是 UEFI

## 为什么?

为什么不呢?

<img src="arts/sticker.webp" width="150">

## 特性

### 平台

- UEFI x86_64

### 模块

- Logo
- UEFI
- Shell
- Display
- Memory
- Locale
- Placeholder
- IP4
- FS
- FS2

## 用法

从 UEFI shell 调用, 使用 bootloader 链式引导, 直接从文件启动, ..., 或者你能想到任何方式

一些主板带有有 bug 的 UEFI 实现, 导致 CPU 锁死

尝试移除一些 uefifetch 模块

## 截图

![](arts/screenshot1.png)

## TODO

- 更多模块
  - Battery
  - CPU
  - Disk
  - Network
  - Version
  - BGRT
  - BIOS
  - ...
- 命令行选项
- 自定义 logo
- BGRT 作为 logo

## 也看看

- [UEFI](https://uefi.org/)
- [EDK II](https://github.com/tianocore/edk2)
- [Index of “Step to UEFI”](https://www.lab-z.com/iof/)
- [从零开始的UEFI裸机编程](https://kagurazakakotori.github.io/ubmp-cn/index.html)
- [フルスクラッチで作る!UEFIベアメタルプログラミング (日文)](http://yuma.ohgami.jp/UEFI-Bare-Metal-Programming/index.html)
- [yaroslav957/efifetch](https://github.com/yaroslav957/efifetch)