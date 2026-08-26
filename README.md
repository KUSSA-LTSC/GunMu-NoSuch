# GunMu-NoSuch

一个用纯汇编（NASM + GCC）在 Windows 下调用 `MessageBoxW` 显示中文的“我写了个滚木”程序。

## 编译

确保你已经安装了 **NASM** 和 **GCC**（MinGW 或 Cygwin 环境）。

在项目目录下执行：

```bash
nasm -f win64 humm.asm -o humm.obj
gcc -o humm.exe humm.obj -mwindows -lkernel32 -luser32 -nostdlib
```

到底啦~就这么点。
