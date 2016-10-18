# Makefile

CC=gcc
CPPFLAGS= -MMD -D_XOPEN_SOURCE=500
CFLAGS= -Wall -Wextra -std=c99 -O2
LDFLAGS=
LDLIBS=

# you should at least create empty file insert_sort.c and quick_sort.c in
# order to compile

SRC= types/pixel.c image_op/binarize.c main_tests.c matrix_op/rlsa.c SDL/main.c SDL/pixel_operations.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all:

-include ${DEP}

main_tests: ${OBJ}

clean:
	rm -f ${OBJ} ${DEP} main_tests

# END
