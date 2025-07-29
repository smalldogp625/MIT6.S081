// kernel/sysinfo.h
#include"types.h"

struct sysinfo {
  uint64 freemem;   // 剩余内存字节数
  uint64 nproc;     // 正在运行的进程数
};
