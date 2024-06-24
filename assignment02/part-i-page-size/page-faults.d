/*
 * page-faults.d
 */

fbt::vm_fault_trap:entry
{
	printf("PID %d: %s(Page Fault at Virtual Address at  %04x\n", pid,  probefunc, arg1);

}
fbt::vm_fault_trap:return
{
    printf("PID: %d: %s returned %d\n", pid, probefunc, arg1);

}
