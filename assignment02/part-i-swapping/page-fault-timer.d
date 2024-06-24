/*
 * page-fault-timer.d
 */

fbt::vm_fault_trap:entry
{
	self->ts = timestamp;
	printf("PID %d: %s(Page Fault at Virtual Address at  %04x, Mapping at  %04x\n", pid,  probefunc, arg1, arg0);

}
fbt::vm_fault_trap:return
/self->ts/
{
    	printf("returned %d, timer: %d ns\n\n", arg1, timestamp - self->ts);
	self->ts = 0;
}
