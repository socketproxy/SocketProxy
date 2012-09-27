target:
	cc -o target target.c -lcrypt

lib:
	cc -shared -ldl -lcrypt -fPIC fake_crypt.c -o libfake_crypt.so

clean:
	rm libfake_crypt.so target

all:	target lib

hack:	target lib
	sh -c LD_PRELOAD=$PWD/libfake_crypt.so ./target
