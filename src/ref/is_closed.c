/**
 * socketproxy/src/ref/is_closed.c
 * (c) 2010 Mike Doyle
 */

#include <stdlib.h>
#include <unistd.h>

/* is_open()
 *
 * returns true if the file descriptor is open, false if not.
 *
 * !!HACK!! This is a hack !!HACK!! See the code for details. !!HACK!!
 */
int
is_open(int fd)
{
    /* HACK: This implementation of this function relies on a slight
     * inconguity between what the linux read(2) man page says and what
     * read actually does. 
     *
     * Here's the man page:
     *
     * If count is zero, read() returns zero  and  has  no  other  results.
     *
     * But in practice, if fd is closed, read will not return zero, it 
     * will return -1 and set errno to EBADF.
     */
    return (read ( fd, NULL, 0 ))?0:-1;
} /* end of is closed */

