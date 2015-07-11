/**
 * socketproxy/src/library/xunistdx.h
 * (c) 2010 Mike Doyle
 */
/*    This file is part of SocketProxy.
 *
 *    SocketProxy is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    SocketProxy is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with SocketProxy.  If not, see <http://www.gnu.org/licenses/>.
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
