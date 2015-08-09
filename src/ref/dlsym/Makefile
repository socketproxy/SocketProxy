# (c) 2015 Mike Doyle
#
#    This file is part of SocketProxy.
#
#    SocketProxy is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 2 of the License, or
#    (at your option) any later version.
#
#    SocketProxy is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with SocketProxy.  If not, see <http://www.gnu.org/licenses/>.
target:
	cc -o target target.c -lcrypt

lib:
	cc -shared -ldl -lcrypt -fPIC fake_crypt.c -o libfake_crypt.so

clean:
	rm libfake_crypt.so target

all:	target lib

hack:	target lib
	sh -c LD_PRELOAD=$PWD/libfake_crypt.so ./target
