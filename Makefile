# Makefile

CC=gcc
CPPFLAGS= -MMD -D_XOPEN_SOURCE=500 `pkg-config --cflags sdl`
CFLAGS= -Wall -Wextra -std=c99 -O2
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm

SRC=	types/pixel.c   \
	main.c			    \
	matrix_op/rlsa.c	\
	image_op/sdl_fct.c	\
	image_op/binarize.c	\
	images/database.c	\
	types/rectangle.c	\
	types/matrix.c		\
	types/matbintree.c	\
	matrix_op/xycut.c   \
    image_op/rotation.c \
	NeuralNetWork/nr.c

OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all:

-include ${DEP}

main: ${OBJ}

clean:
	rm -f ${OBJ} ${DEP} main

# END
