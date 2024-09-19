# minitalk

The purpose of this project is to code a small data exchange program using UNIX signals. 

# Code logic

## 1. client side
	Send the size of the string first, then send the string;
	
	How to send a string to server?
	
	Separating a string to characters(in sedn() function), then send a character bit by bit (in send_byte() function).
	
	Every time after sending a bit to server, the client will wait if the server receive it successfully (by checking the value of g_ack),
	
	if the server receive it  successfully, then the client will send next bit to server; otherwise, the client will wait 10s, the prompt
	
	time out error message.
	
	# Key used functions
	
	To finish this project, fully understanding sigaction() and kill() functions are required.

## 2. server side

	Server will receive  message as bit by bit , then saving bits into a byte, then saving the byte into a str. After receiving all the 
 	characters, print the messsage out.
	

## sigaction()

	SYNOPSIS:
 		#include <signal.h>

       		int sigaction(int signum, const struct sigaction *_Nullable restrict act, 
	 		struct sigaction *_Nullable restrict oldact);
	
	DESCRIPTION:
  		The sigaction() system call is used to change the action taken 
    		by a process on receipt of a specific signal. 

    		-- signum specifies the signal and can be any valid signal except SIGKILL and SIGSTOP.

      		-- If act is non-NULL, the new action for signal signum is 
		installed from act.  If oldact is non-NULL, the previous action is saved in
       		   oldact.

       		-- The sigaction structure is defined as something like:

	           struct sigaction {
	               void     (*sa_handler)(int);
	               void     (*sa_sigaction)(int, siginfo_t *, void *);
	               sigset_t   sa_mask;
	               int        sa_flags;
	               void     (*sa_restorer)(void);
	           };
	    	The sa_restorer field is not intended for application use.
	        (POSIX does not specify a sa_restorer field.)  Some further
	       details of the purpose of this field can be found in
	       sigreturn(2).
	
	       sa_handler specifies the action to be associated with signum and
	       can be one of the following:
	
	       •  SIG_DFL for the default action.
	
	       •  SIG_IGN to ignore this signal.
	
	       •  A pointer to a signal handling function.  This function
	          receives the signal number as its only argument.
	
	       If SA_SIGINFO is specified in sa_flags, then sa_sigaction
	       (instead of sa_handler) specifies the signal-handling function
	       for signum.  This function receives three arguments, as described
	       below.
	
	       sa_mask specifies a mask of signals which should be blocked
	       (i.e., added to the signal mask of the thread in which the signal
	       handler is invoked) during execution of the signal handler.  In
	       addition, the signal which triggered the handler will be blocked,
	       unless the SA_NODEFER flag is used.
	
	       sa_flags specifies a set of flags which modify the behavior of
	       the signal.


## kill()

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

# Tester

https://github.com/ThibaudM13/minitalk-Tester

# Resources

https://42-cursus.gitbook.io/guide/rank-02/minitalk

https://man7.org/linux/man-pages/man2/sigaction.2.html

https://jameshfisher.com/2017/01/13/c-sigaction/

# My score


![Screenshot from 2024-09-19 13-49-58](https://github.com/user-attachments/assets/fef240cf-17b7-44e9-b06e-b0c478b5bb96)

# 42 projects rules

*All 42 projects must be written in C (later C++) in accordance to the 42 School Norm.

Sample restrictions:

-- All variables have to be declared and aligned at the top of each function

-- Each function can not have more then 25 lines

-- Projects should be created with allowed std functions otherwise it is cheating
