

CC         := gcc
LINKER     := $(CC)
CFLAGS     := -O0 # -msse3 -O2
LDFLAGS    := -lm

UTIL       := function.o \



TEST_OBJS  := main.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all:
	make clean;
	make main.x

main.x: $(TEST_OBJS) $(UTIL) function.h
	$(LINKER) $(TEST_OBJS) $(UTIL) $(LDFLAGS) \
        $(BLAS_LIB) -o $@ -lopenblas

export OMP_NUM_THREADS=1
export GOTO_NUM_THREADS=1

run:
	make all
	./main.x

clean:
	rm -f *.o *~ core *.x

cleanall:
	rm -f *.o *~ core *.x output*.m *.eps  *.jpg
