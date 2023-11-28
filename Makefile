BINDIR = $(HOME)/bin
INCDIR = $(HOME)/include
LIBDIR = $(HOME)/lib

CC = cc
CFLAGS = -Wextra -Wall -I$(INCDIR) -L$(LIBDIR) -O2 -DUTF_8 -DLF
LDLIBS = -lshun
INSTALL = cp -i
RM = rm -f

PROGRAM = mkmyfile
OBJS = mkmyfile.o

.PHONY: all install clean
all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDLIBS)

.SUFFIXES: .o .c
.c.o:
	$(CC) $(CFLAGS) -c $<

install:
	$(INSTALL) $(PROGRAM) $(BINDIR)

clean:
	$(RM) $(PROGRAM) $(OBJS)

