cc = gcc
obj = src/main.c
out = ./bin/arena.out

cflags = -Wall -Wextra -Wpedantic
lflags =

devel :
	$(cc) $(obj) $(cflags) -fsanitize=address $(lflags) -o $(out) -g

run : release
	$(out)

release :
	$(cc) $(obj) $(cflags) -o3 $(lflags) -o $(out) -s
