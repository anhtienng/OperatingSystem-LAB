#include "get_proc_info.h"
#include <sys/syscall.h>

long get_proc_info(pid_t pid, struct procinfos *info){
    return syscall(548, pid, info);
}
