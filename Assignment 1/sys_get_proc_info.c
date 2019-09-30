#include <linux/kernel.h>
#include <asm/current.h>
#include <asm/errno.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <asm/unistd.h>
#include <linux/string.h>

struct proc_info {                      //info about a single process
    pid_t pid;                          //pid of the process
    char name[16];                      //file name of the program executed
};

struct procinfos {                      //info about processes we need
    long studentID;                     //for the assignment testing
    struct proc_info proc;              //process with pid or current process
    struct proc_info parent_proc;       //parent process
    struct proc_info oldest_child_proc; //oldest child process
};

void create_procinfos(struct task_struct *process, struct procinfos __user *info){
    struct task_struct *parent_process, *oldest_child_process;
    struct list_head *children_list;
    struct procinfos result;
    
    memset(&result, 0, sizeof(struct procinfos));
    result.studentID = 1752076;
    //printk(KERN_INFO "create_procinfos is called");

    // current process
    (result.proc).pid = process->pid;
    get_task_comm((result.proc).name, process);
    //printk(KERN_INFO "sys_get_proc_info: Done current");

    // parent process
    parent_process = process->parent;
    if (parent_process){
        (result.parent_proc).pid = parent_process->pid;
        get_task_comm((result.parent_proc).name, parent_process);
        //printk(KERN_INFO "sys_get_proc_info: Done parent");
    }

    // oldest_child
    children_list = &process->children;
    
    // if there are no children
    if (list_empty(children_list)){
        //handle no child process
        oldest_child_process = NULL;
        //printk(KERN_INFO "sys_get_proc_info: No child");
    }
    else
        oldest_child_process = list_first_entry(children_list, struct task_struct, sibling);
    
    
    if (oldest_child_process){
        (result.oldest_child_proc).pid = oldest_child_process->pid;
        get_task_comm((result.oldest_child_proc).name, oldest_child_process);
    }
    else
        (result.oldest_child_proc).pid = -1;

    copy_to_user(info, &result, sizeof(struct procinfos));
}

SYSCALL_DEFINE2 (get_proc_info, pid_t, pid, struct procinfos __user *, info){
    struct task_struct *process;
    printk (KERN_INFO "%d, sys_get_proc_info is invoked", 1752076);
    if (pid == -1){
        //current process
        process = current;
        //printk(KERN_INFO "pid: %d", process->pid);
        create_procinfos(process, info);
    }
    else if (pid >= 0){
        process = find_task_by_vpid(pid);
        if (process == NULL)
            return -EINVAL;
        //printk(KERN_INFO "pid: %d", process->pid);
        create_procinfos(process, info);
    }
    else
        return -EpINVAL;
    
    return 0;
}
