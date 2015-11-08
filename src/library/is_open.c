/***
 * socketproxy/src/library/is_open.c
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

#include <stdlib.h>
#include <unistd.h>

/* __sp_is_open()
 *
 * returns true if the file descriptor is open, false if not.
 *
 * !!HACK!! This is a hack !!HACK!! See the code for details. !!HACK!!
 */
int __sp_is_open(int fd)
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
    return (read(fd, NULL, 0)) ? 0 : -1;
}                               /* end of is_open */
