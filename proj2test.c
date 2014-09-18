//Lukas Hunker
#include <sys/syscall.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "processinfo.h"

// These values MUST match the unistd_32.h modifications:
#define __NR_cs3013_syscall1 349
#define __NR_cs3013_syscall2 350
#define __NR_cs3013_syscall3 351

long testCall1 ( void) {
        return (long) syscall(__NR_cs3013_syscall1);
}
long testCall2 ( void) {
		struct processinfo info;
        long ret =  (long) syscall(__NR_cs3013_syscall2, &info);
        printf("\t\tUID is %d\n", info.uid);
        printf("\t\tPID is %d\n", info.pid);
        printf("\t\tParent PID is %d\n", info.parent_pid);
        printf("\t\tYougest Child PID is %d\n", info.youngest_child);
        printf("\t\tYounger Sibling PID is %d\n", info.younger_sibling);
        printf("\t\tOlder Sibling PID is %d\n", info.older_sibling);
        printf("\t\tState is %ld\n", info.state);
        printf("\t\tStart time is %lld\n", info.start_time);
        printf("\t\tSys time is %lld\n", info.sys_time);
        printf("\t\tUser time is %lld\n", info.user_time);
        printf("\t\tChild User time is %lld\n", info.cutime);
        printf("\t\tChild system time is %lld\n", info.cstime);
        return ret;
}
long testCall3 ( void) {
        return (long) syscall(__NR_cs3013_syscall3);
}
int main () {
		int pid = fork();
		char * args[] = {"ping", "google.com", "-c", "15"};
		if (pid == 0){
			execvp(args[0], args);
		}
        printf("The return values of the system calls are:\n");
        printf("\tcs3013_syscall1: %ld\n", testCall1());
        printf("\tcs3013_syscall2: %ld\n", testCall2());
        printf("\tcs3013_syscall3: %ld\n", testCall3());
        return 0;
}
