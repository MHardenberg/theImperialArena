src = ./src/arena.c
obj = ./bin/arena.o
out = ./bin/lib_arena.a
cflags = -Wall -Wextra -Wpedantic

devel :
	gcc -fPIC -O0  $(cflags) -o $(obj) -c $(src) -g
	ar -rc $(out) $(obj) 

release :
	gcc -fPIC -O3  $(cflags) -o $(obj) -c $(src) -s
	ar -rc $(out) $(obj) 
