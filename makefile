include ./make.inc
ALL=T1 

T1:
	cd neko && make all DIST=../build/


all:$(ALL)
	echo "all build done"