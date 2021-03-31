CC=g++
INCL=-I${HOME}/cpp-include
# find all ./*.cc
src=$(wildcard ./*.cc)
# replace all %.cc to %.o in $(src)  
obj=$(patsubst %.cc, %.o, $(src))  
target=simulator  

# echo:
# 	echo $(obj)

$(target): $(obj)  
	$(CC) $(INCL) $(obj) -o $(target)

%.o: %.cc
	$(CC) $(INCL) -c -o $@ $^

all: clean $(target)

.PHONY: clean
clean:
	rm -f $(obj) $(target)

# ODIR=obj
# LDIR =../lib

# LIBS=-lm

# _DEPS = hellomake.h
# DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# _OBJ = hellomake.o hellofunc.o 
# OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))