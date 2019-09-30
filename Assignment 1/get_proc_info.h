#ifndef _GET_PROC_INFO_H
#define _GET_PROC_INFO_H

#include <sys/types.h>

struct proc_info {                      //info of a single process
    pid_t pid;                          //process ID
    char name[16];                      //file name of the program executed
};

struct procinfos {                      //info about processes we need
    long studentID;                     //for the assignment testing
    struct proc_info proc;              //process with pid or current process
    struct proc_info parent_proc;       //parent process
    struct proc_info oldest_child_proc; //oldest child process
};

long get_proc_info(pid_t pid, struct procinfos *info);  

#endif
