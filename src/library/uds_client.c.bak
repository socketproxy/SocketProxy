/* socketproxy/src/library/uds_client.c
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

#include "uds_client.h"
#define BUFSIZE 512
#include <stdio.h>

#define DEBUG 0

/***
 * __sp_call_server -- This function takes in an __sp_request and sends
 * it to the socket proxy server process. It is usually called during
 * calls to socket and calls to read/write data.
 */
__sp_response
__sp_call_server( __sp_request *req )
{

    /***
     * XXX: Work in progress: changing this code over from using fifos to 
     * using unix domain sockets. This will likely involve replacing the
     * fifo_client.c file with this file.
     */



    /***
     * Variable declarations 
     */
     
    /*
     * The message to send.
     */
    char *mesg;

    /* file path and descriptor of the "command socket" communications 
     * channel to the server. 
     */
    char *cmdaddrpath;
    int cmdfd;

    /* flag and mode bitfields for the call and response i/o */
    int callflags, respflags;
    mode_t callmode, respmode;

    /* temp variable for reading the response */
    int n;
    int bufsize = BUFSIZE;
    char buf[BUFSIZE];

    /* return variable for the response */
    __sp_response resp;


    /* Pointer to the real socket(2) */
    static int (*__sp_real_socket)(int, int, int) = NULL;



    /***
     *Initialization. 
     * - Get the name of the communications path to the soxprox server,
     * - Set flags and modes for the calls to open,
     */

    mesg = *((char **)req);

    if ( (cmdaddrpath = __sp_get_cmd_uds_path() ) == NULL ) {
        return (__sp_response)NULL;
    }

    if(DEBUG){
        printf( "Cmd uds path: %s\n", cmdaddrpath );
    }

    callflags = O_WRONLY;
    callmode = S_IRUSR; /*Note this should be ignored*/

    respflags = O_RDONLY;
    respmode = S_IRUSR; /*Note this should be ignored*/
    


    /* Setting the static function pointer, if not already set. */
    if ( __sp_real_socket == NULL ) {
            __sp_real_socket = dlsym(RTLD_NEXT, "socket");
    }       



    /* XXX: Open socket to server here.  */



    /* end of initialization for __sp_call_server() */
    
    /***
     * Send a request 
     */

    /* XXX: Replace this code with code that writes to the socket. */
    if ( (cmdfd = xopenx ( cmdfifoname, callflags, callmode )) == -1 ){
        return (__sp_response)NULL;
    }

    if ( (xwritex ( cmdfd, mesg, strlen( mesg ) +1 )) == -1 ){
        return (__sp_response)NULL;
    }

    xclosex ( cmdfd );


    /*** 
     * Receive a response 
     */

    /* XXX: Replace this with code that reads from the socket.
    bzero ( buf, bufsize );

    if ( (cmdfd = xopenx ( cmdfifoname, respflags, respmode )) == -1 ){
        return (__sp_response)NULL;
    }


    while ( (n = xreadx ( cmdfd, buf, bufsize )) > 0 ) {
        asprintf ( &resp, "%s%s\n", resp, buf ); 
    }
    
    xclosex ( cmdfd );
    free ( cmdfifoname ) ;

    return resp;

} /* end of __sp_call_server() */



/* __sp_get_cmd_uds_addr()
 *
 * returns a malloc'd copy of the filename of the fifo used to
 * communicate with he socketproxy server.
 */
char *
__sp_get_cmd_uds_addr()
{
    pid_t pid, ppid;
    char *s;
    
    pid = getpid();
    ppid = getppid();

    if ( asprintf(&s, "/tmp/soxprox-%d-%d/command_fifo", pid, ppid) == -1 ){
        return NULL;
    }

    return s;
} /* end of __sp_get_cmd_uds_addr() */
