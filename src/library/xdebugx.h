/* socketproxy/src/library/xdebugx.h
 * (c) 2015 Mike Doyle
 *
 *    This file is part of SocketProxy.
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


#ifdef DEBUG
#include <stdio.h>

#define DEBUG_PRINTF(...) do { fprintf( stderr, __VA_ARGS__ ); } while (0)

#else 

#define DEBUG_PRINTF(...) do { ; } while (0)

#endif
