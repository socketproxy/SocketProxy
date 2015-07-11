/***
 * socketproxy/src/library/uds_client.h
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

#ifndef __UDS_CLIENT_H
#define __UDS_CLIENT_H

/***
 * XXX: Work in progress: replacing fifos with unix domain sockets. This
 * file will replace fifo_client.h.
 * 
 */
#include "serialize.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 512


/* 
 * Forward declarations 
 */

/***
 * __sp_call_server -- This function takes in an __sp_request and sends
 * it to the socket proxy server process. It is usually called during
 * calls to socket and calls to read/write data.
 */
__sp_response __sp_call_server( __sp_request *req );

/* __sp_get_cmd_uds_addr()
 *
 * returns a malloc'd copy of the filepath used by the unix domain socket
 * used to to communicate with the socket proxy server process.
 */
char *__sp_get_cmd_uds_addr();

#endif
