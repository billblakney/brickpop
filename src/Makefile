CC      = g++
#CFLAGS  = -I/home/scale/g++Projects/gLib/
#LDFLAGS = -lfltk

src = $(wildcard *.cc)
obj = $(src:.cc=.o)

#LDFLAGS = -lGL -lglut -lpng -lz -lm

brickpop: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(obj) brickpop
