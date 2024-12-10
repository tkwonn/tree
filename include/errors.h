#ifndef ERRORS_H
#define ERRORS_H

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

/* Prints a message on stderr similar to printf() 
* except terminating newline character is automatically appended
*/
void errMsg(const char *format, ...);

/* This macro stops 'gcc -Wall' complaining that "control reaches
end of non-void function" if we use the following functions to
 terminate main() or some other non-void function. */
#ifdef __GNUC__
#define NORETURN __attribute__ ((__noreturn__))
#else
#define NORETURN
#endif

/* Print error message and terminate the program using exit()
* Uses errno to determine the error */
void errExit(const char *format, ...);

/* Similar to errExit(), but doesn't flush stdout and
* terminates with _exit() instead of exit() */
void err_exit(const char *format, ...);

/* Used to diagnose errors in command-line argument usage */
void usageErr(const char *format, ...);

#endif

