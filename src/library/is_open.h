/**
 * socketproxy/src/library/is_open.h
 * (c) 2010 Mike Doyle
 */

#ifndef __SP_IS_OPEN_H
#define __SP_IS_OPEN_H

#include <stdlib.h>
#include <unistd.h>

/* __sp_is_open()
 *
 * returns true if the file descriptor is open, false if not.
 *
 * !!HACK!! This is a hack !!HACK!! See the code for details. !!HACK!!
 */
int
__sp_is_open(int fd);


#endif
