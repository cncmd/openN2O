TRAGET=nvmdso.so
ALL=nvmdso_wrap.o nvmdso.o
.PHONEY clean

clean:
	rm -f *.so *.o
	
nvmdso_wrap.o:
	swig -lua nvmdso.i
	gcc  -fPIC -I/usr/include -c nvmdso_wrap.c -o nvmdso_wrap.o 
	
nvmdso.o:
	gcc  -fPIC -I/usr/include -c nvmdso.c -o nvmdso.o 
	
dist: $(ALL)
	gcc  -fPIC -shared -I/usr/include -L/usr/lib/lua $(ALL) -o $(TRAGET) ../lib/libneko.so 
	
all: clean dist 
	cp -f  $(TRAGET) ../build/
	echo "make done"