/* socketproxy/src/library/fifo_client.c
 * (c) 2010 Mike Doyle
 */

#include "fifo_client.h"
#define BUFSIZE 512
#include <stdio.h>

#define DEBUG 0

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
