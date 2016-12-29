CC      = g++
#CFLAGS  = -I/home/scale/g++Projects/gLib/
#LDFLAGS = -lfltk

src = $(wildcard *.cc)
obj = $(src:.cc=.o)

#LDFLAGS = -lGL -lglut -lpng -lz -lm

all: $(obj)
	$(CC) -o brickpop $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(obj) brickpop
