TARGET="nvmdso"
CC=gcc
CFLGS=-fPIC 
all:
	swig -lua example.i
	gcc  -fPIC -I/usr/include -c example_wrap.c -o example_wrap.o
	gcc  -fPIC -I/usr/include -c example.c -o example.o
	gcc  -fPIC -shared -I/usr/include -L/usr/lib/lua example_wrap.o example.o -o example.so ./libneko.so
	echo "done"
