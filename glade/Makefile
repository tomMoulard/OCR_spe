# Makefile

CC=gcc
CPPFLAGS= -MMD -D_XOPEN_SOURCE=500 `pkg-config --cflags sdl gtk+-3.0`
CFLAGS= -Wall -Wextra -std=c99 -g
LDFLAGS=
LDLIBS= `pkg-config --libs sdl gtk+-3.0` -lSDL_image -lm -export-dynamic

SRC= main.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}


#For "make" instead of "make main"
all: main

-include ${DEP}

main: ${OBJ}

clean:
	rm -f ${OBJ} ${DEP} main

# END
