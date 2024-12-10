#include "errors.h"

static void terminate(bool useExit3)
{
    char *s;
    s = getenv("EF_DUMPCORE");

    if (s != NULL && *s != '\0')
        abort(); /* Generate core dump file for debugger */
    else if (useExit3)
        exit(EXIT_FAILURE);
    else
        _exit(EXIT_FAILURE);
}

static void outputError(bool useErr, int err, bool flushStdout,
        const char *format, va_list ap)
{
#define BUF_SIZE 500
    char buf[BUF_SIZE], userMsg[BUF_SIZE], errText[BUF_SIZE];

    vsnprintf(userMsg, BUF_SIZE, format, ap);

    if (useErr)
        snprintf(errText, BUF_SIZE, " [%s]", strerror(err));
    else
        snprintf(errText, BUF_SIZE, ":");

    snprintf(buf, BUF_SIZE, "ERROR%s %s\n", errText, userMsg);

    if (flushStdout)
        fflush(stdout);
    fputs(buf, stderr);
    fflush(stderr);
}

void errMsg(const char *format, ...)
{
    va_list argList;
    int savedErrno;

    savedErrno = errno;
    va_start(argList, format);
    outputError(true, errno, true, format, argList);
    va_end(argList);

    errno = savedErrno;
}

void errExit(const char *format, ...)
{
    va_list argList;

    va_start(argList, format);
    outputError(true, errno, true, format, argList);
    va_end(argList);

    terminate(true);
}

void err_exit(const char *format, ...)
{
    va_list argList;

    va_start(argList, format);
    outputError(true, errno, false, format, argList);
    va_end(argList);

    terminate(false);
}

void usageErr(const char *format, ...)
{
    va_list argList;

    fflush(stdout); 

    fprintf(stderr, "Usage: ");
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);

    fflush(stderr);
    exit(EXIT_FAILURE);
}
