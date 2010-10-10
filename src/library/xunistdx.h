/**
 * socketproxy/src/library/xunistdx.h
 * (c) 2010 Mike Doyle
 */

#ifndef __SP_XUNISTD_H
#define __SP_XUNISTD_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>


/***
 * Forward declarations
 */

ssize_t xreadx ( int fd, void *buf, size_t count ); 
ssize_t xwritex ( int fd, const void *buf, size_t count ); 
int xopenx ( const char *pathname, int flags, mode_t mode ); 
int xcreatx ( const char *pathname, mode_t mode ); 
int xclosex ( int fd ); 
int xfcntlx ( int fd, int cmd, struct flock *lock );

#endif
