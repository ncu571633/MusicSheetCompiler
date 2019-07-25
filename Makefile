########################################################
CC = g++
LIBS = -lMidi -lNetPbm

CPPFLAGS = -Wall -g3 -std=c++11 #fpic
#LDFLAGS = -shared

# -c Compile or assemble the source files, but do not link.
# -o Place output in file file.  This applies to whatever sort of output
#           is being produced, whether it be an executable file, an object
#           file, an assembler file or preprocessed C code.
# -fpic Generate position-independent code (PIC) suitable for use in a
#           shared library
# -L Specify library path
# -WL,-rpath: specify library to exe loader
########################################################
objects = main.o

all: $(objects)
	$(CC) -o test $(objects) $(CPPFLAGS) -L./lib/ -Wl,-rpath=./lib/ $(LIBS)

clean:
	rm -r -f test
	rm -r -f *.o *.p?m *.mid* *.pdf *.ps *.xml *.txt


