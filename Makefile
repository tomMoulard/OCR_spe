# Makefile

CC=gcc
CPPFLAGS= -MMD -D_XOPEN_SOURCE=500 `pkg-config --cflags sdl gtk+-3.0`
CFLAGS= -Wall -Wextra -std=c99 -g
LDFLAGS=
LDLIBS= `pkg-config --libs sdl gtk+-3.0` -lSDL_image -lm -export-dynamic

SRC=    NeuralNetWork/nr2.c     \
        types/pixel.c           \
	    main.c			        \
	    matrix_op/rlsa.c	    \
	    image_op/sdl_fct.c	    \
	    image_op/binarize.c	    \
	    image_op/rotation.c	    \
	    images/database.c	    \
	    types/rectangle.c	    \
	    types/matrix.c		    \
	    types/matbintree.c	    \
	    matrix_op/xycut.c

OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}


#For "make" instead of "make main"
all: main

-include ${DEP}

main: ${OBJ}

clean:
	rm -f ${OBJ} ${DEP} main

# END
