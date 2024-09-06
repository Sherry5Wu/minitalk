# minitalk


# Used functions

	kill():
        Descrition:
        The kill() system call can be used to send any signal to any
        process group or process.

       If pid is positive, then signal sig is sent to the process with
       the ID specified by pid.

       If pid equals 0, then sig is sent to every process in the process
       group of the calling process.

       If pid equals -1, then sig is sent to every process for which the
       calling process has permission to send signals, except for
       process 1 (init), but see below.

       If pid is less than -1, then sig is sent to every process in the
       process group whose ID is -pid.

       If sig is 0, then no signal is sent, but existence and permission
       checks are still performed; this can be used to check for the
       existence of a process ID or process group ID that the caller is
       permitted to signal.
	return value:
		On success (at least one signal was sent), zero is returned. On
       error, -1 is returned, and errno is set to indicate the error.


# Resources

https://42-cursus.gitbook.io/guide/rank-02/minitalk

https://man7.org/linux/man-pages/man2/sigaction.2.html

https://jameshfisher.com/2017/01/13/c-sigaction/

https://man7.org/linux/man-pages/man2/sigaction.2.html
