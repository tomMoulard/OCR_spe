# Makefile

CC=gcc
CPPFLAGS= -MMD -D_XOPEN_SOURCE=500 `pkg-config --cflags sdl`
CFLAGS= -Wall -Wextra -std=c99 -O2
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm

SRC= types/pixel.c				\
 		 main_tests.c 				\
		 matrix_op/rlsa.c 		\
		 image_op/sdl_fct.c		\
		 image_op/binarize.c	\
		 types/rectangle.c 		\
		 types/matrix.c 			\
		 types/matbintree.c 	\
		 matrix_op/xycut.c

OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all:

-include ${DEP}

main_tests: ${OBJ}

clean:
	rm -f ${OBJ} ${DEP} main_tests

# END
