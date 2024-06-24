/* Part 1: truss */
syscall:::entry {
    printf("%Y, %d: %s(%04x,%04x,%d04x%04x,%04x,%04x)\n", walltimestamp, pid,  probefunc, arg0, arg1, arg2, arg3, arg4, arg5);
}

syscall:::return {
    printf("%s returned %d", probefunc, arg0);
}

