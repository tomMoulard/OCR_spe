# Makefile

CC=gcc
CPPFLAGS= -MMD -D_XOPEN_SOURCE=500 `pkg-config --cflags sdl`
CFLAGS= -Wall -Wextra -std=c99 -O2
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

SRC= types/pixel.c main_tests.c matrix_op/rlsa.c SDL/pixel_operations.c matrix_op/rectangle.c types/matrix.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all:

-include ${DEP}

main_tests: ${OBJ}

clean:
	rm -f ${OBJ} ${DEP} main_tests

# END
