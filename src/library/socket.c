/**
 * socketproxy/src/library/socket.c
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

#include "socket.h"
#include "fifo_client.h"
#include <errno.h>
#include <string.h>
#ifdef DEBUG
#  include <stdio.h>
#endif



int 
socket(int family, int type, int protocol)
{

    __sp_request req;
    __sp_response resp;
    int retval;

    req = __sp_serialize_init( "socket" );
    __sp_serialize_str(&req, "name", "socket");
    __sp_serialize_int(&req, "family", family);
    __sp_serialize_int(&req, "type", type);
    __sp_serialize_int(&req, "protocol", protocol);
    __sp_serialize_finalize( &req );

    if (DEBUG) {
        printf ( "About to call server\n" );
        printf ( "Call: (%s)\n", __sp_serialize_tostring(&req));
    }

    if ( (resp = __sp_call_server(&req)) == (__sp_response)NULL ) {
        return -1;
    }

    if (DEBUG) {
        printf ( "Finished call to server\nResp:(%s)\n",
                __sp_serialize_tostring(&resp) );
    }

    free(req);

    retval = __sp_deserialize_int(&resp, "retval");

    if (!retval){
        errno = __sp_deserialize_int(&resp, "errno");
    }

    free(resp);
   
    return retval;

} /* end of socket() */

int
connect ( int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen)
{

    __sp_request req;
    __sp_response resp;
    int retval;
    char *errnostr;

    char sin6_addr[INET6_ADDRSTRLEN + 1];

    /* We'll only need one of these */

    req = __sp_serialize_init( "connect" );
    __sp_serialize_str(&req, "name", "connect");
    __sp_serialize_int(&req, "addrlen", addrlen);
    __sp_serialize_int(&req, "sockfd", sockfd);

    switch ( serv_addr->sa_family ) {
    case AF_INET: {
        struct sockaddr_in *sin;
        char sin_addr[INET_ADDRSTRLEN + 1];

        __sp_serialize_str(&req, "sin_family", "AF_INET");

        sin = (struct sockaddr_in *)serv_addr;

        __sp_serialize_int(&req, "sin_port", ntohs(sin->sin_port));

        bzero( sin_addr, sizeof(sin_addr) );

        if ( inet_ntop ( 
                serv_addr->sa_family, 
                &(sin->sin_addr),
                sin_addr, 
                sizeof(sin_addr) 
            ) == NULL
        ) {
            return -1;
        }

        if(DEBUG){
            printf ( "my sin_addr: %s\n", sin_addr );
        }
        __sp_serialize_str(&req, "sin_addr", sin_addr);
        
        break;
    }


    case AF_INET6: {
        struct sockaddr_in6 *sin6;

        __sp_serialize_str(&req, "serv-addr-family", "AF_INET6");
        sin6 = (struct sockaddr_in6 *)serv_addr;
        return -1;
        break;
    }



    case AF_LOCAL: {
        struct sockaddr_un *sun;
        __sp_serialize_str(&req, "serv-addr-family", "AF_LOCAL");
        sun = (struct sockaddr_un *)serv_addr;
        return -1;
        break;
    }



    /*case AF_LINK: {*/
        /*struct sockaddr_dl sdl;*/
        /*__sp_serialize_str(&req, "serv-addr-family", "AF_LINK");*/
        /*sdl = (struct sockaddr_dl)(*serv_addr);*/
        /*return -1;*/
        /*break;*/
    /*}*/


    default:
        free ( req );
        return -1;
    }

    __sp_serialize_finalize( &req );

    if (DEBUG) {
        printf ( "About to call server\n" );
        printf ( "Call: (%s)\n", __sp_serialize_tostring(&req));
    }

    if ( (resp = __sp_call_server(&req)) == (__sp_response)NULL ) {
        return -1;
    }

    if (DEBUG) {
        printf ( "Finished call to server\nResp:(%s)\n",
                __sp_serialize_tostring(&resp) );
    }

    free(req);

    retval = __sp_deserialize_int(&resp, "retval");

    if (retval != 0){
        errnostr = __sp_deserialize_str(&resp, "errno");

        free(resp);

        if (DEBUG) {
            printf ( " About to strcmp: %s \n", errnostr);
        }

        if ( strcmp ( errnostr, "ECONNREFUSED" ) ) {
            if ( DEBUG ) {
                printf ( "SEtting errno accordingly\n" );
            }
            errno = ECONNREFUSED;
        }
    }

   
    return retval;

} /* end of connect() */

/***
 * setsocketopt
 *
 * TODO: Stop screwing around.
 */
int setsockopt(int s, int level, int optname,
                 const void *optval, socklen_t optlen){
    return 0;
}

