/**
 * socketproxy/src/library/xunistdx.c
 * (c) 2010 Mike Doyle
 */

#include "xunistdx.h"
#include <stdlib.h>


ssize_t
xreadx ( int fd, void *buf, size_t count )
{

    ssize_t status = read(fd, buf, count);
    if ( status  < 0 ) 
         exit( -1 );
    return status;

} /* end of xreadx */



ssize_t
xwritex ( int fd, const void *buf, size_t count )
{
    ssize_t status = write ( fd, buf, count );
    if ( status < 0 )
        exit ( -1 );
    return status;
} /* end of xwritex */



int
xopenx ( const char *pathname, int flags, mode_t mode )
{
    int status = open ( pathname, flags, mode );
    if ( status < 0 ) {
        perror("xopenx");
    }
    return status;
} /* end of xopenx */



int
xcreatx ( const char *pathname, mode_t mode )
{
    int status = creat( pathname, mode );
    if ( status < 0 ) {
        perror("xcreatx");
    }
    return status;
} /* end of xcreatx */



int
xclosex ( int fd )
{
    int status = close( fd );
    if ( status < 0 )
        perror("xclosex");
    return status;
} /* end of xclosex */



int
xfcntlx ( int fd, int cmd, struct flock *lock )
{
    int status = fcntl( fd, cmd, lock );
    if ( status < 1 )
        perror("xfcntlx");
    return status;
} /* end of xfcntl */
