/* socketproxy/src/library/fifo_client.c
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

#include "fifo_client.h"
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
     * XXX: Work in progress: chaning this code over from using fifos to 
     * using unix domain sockets. This will likely involve replacing this
     * file entirely.
     */

    /***
     * Variable declarations 
     */
     
    /*
     * The message to send.
     */

    char *mesg;

    /* file name and descriptor of the "command fifo" communications 
     * channel to the server 
     */
    char *cmdfifoname;
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



    /***
     *Initialization. 
     * - Get the name of the communications path to the soxprox server,
     * - Set flags and modes for the calls to open,
     */

    mesg = *((char **)req);

    if ( (cmdfifoname = __sp_get_cmd_fifo_name() ) == NULL ) {
        return (__sp_response)NULL;
    }

    if(DEBUG){
        printf( "Cmd fifo name: %s\n", cmdfifoname );
    }

    callflags = O_WRONLY;
    callmode = S_IRUSR; /*Note this should be ignored*/

    respflags = O_RDONLY;
    respmode = S_IRUSR; /*Note this should be ignored*/
    


    /* end of initialization for __sp_call_server() */
    
    /***
     * Send a request 
     */
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
    bzero ( buf, bufsize );

    if(DEBUG) {
        printf (" Just before xopenx\n");
    }
    if ( (cmdfd = xopenx ( cmdfifoname, respflags, respmode )) == -1 ){
        return (__sp_response)NULL;
    }

    if(DEBUG) {
        printf (" Just after xopenx\n");
    }


    while ( (n = xreadx ( cmdfd, buf, bufsize )) > 0 ) {
        asprintf ( &resp, "%s%s\n", resp, buf ); 
    }
    
    xclosex ( cmdfd );
    free ( cmdfifoname ) ;

    return resp;

} /* end of __sp_call_server */



/* __sp_get_cmd_fifo_name()
 *
 * returns a malloc'd copy of the filename of the fifo used to
 * communicate with he socketproxy server.
 */
char *
__sp_get_cmd_fifo_name()
{
    pid_t pid, ppid;
    char *s;
    
    pid = getpid();
    ppid = getppid();

    if ( asprintf(&s, "/tmp/soxprox-%d-%d/command_fifo", pid, ppid) == -1 ){
        return NULL;
    }

    return s;
} /* end of __sp_get_cmd_fifo_name() */
