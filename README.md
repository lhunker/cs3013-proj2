Lukas Hunker
cs 3013 Project 2

To Compile/Run
Phase 1

% cd phase1
% make
% sudo insmod readwrite.ko

Phase 2

% cd phase2
% make
% sudo insmod processinfo.ko
% gcc -o testp2 proj2test.c
% ./testp2

Details
Phase 1 prints an alert to the syslog whenever a user opens or closes a file.

Phase 2 is a syscall that returns information about the current process. It is passed an empty processinfo structure that it returns filled with data. it can handle a NULL pointer and will return -1. It can not handle if it is assed the wrong type of pointer (such as a int *), this will result in a seg fault.
Phase 2 operates by getting the task structure and retrieving data from it. it also iterates the children and sibling lists to find the youngest child, younger sibling, and older sibling.