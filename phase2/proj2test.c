//Lukas Hunker
//proj2test.c
//a program to test phase 2
//calls the syscall and prints results
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
        if (ret == -1){
                //if error return
        	return ret;
        }
        //Print all fields of info
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
//put a load on the cpu
void stress (void) {
	//Set a child process to generate usage
	long long i, j;
	for(i = 0; i < 1000000000; i++){
		j++;
	}
	printf("done\n");
}

int main () {
	int pid = fork();
	if (pid == 0){
		stress();
		return 0;
	}
	pid = fork();
	if (pid == 0){
		stress();
		return 0;
	}

        sleep(1);
        printf("The return values of the system calls are:\n");
        printf("\tcs3013_syscall1: %ld\n", testCall1());
        printf("\tcs3013_syscall2: %ld\n", testCall2());
        printf("\tcs3013_syscall3: %ld\n", testCall3());
        //wait for children to terminate
        wait(0);
        wait(0);
        return 0;
}
