#
# FuriatuneSet2SS by emarti
# Version  : 1.0 11092017
# Target OS: Amiga OS2.X/3.X
# Compiler : GCC
#

objects = furiatuneSet2SS.o
appname = furiatuneSet2SS

CFLAG = -O2 -m68000
LIBS 	= -noixemul
RZFLAGS = -fstrength-reduce -msmall-code -Wimplicit \
          -Wstrict-prototypes -s -Os -Wall -fomit-frame-pointer

furiatuneSet2SS:	$(objects)
	gcc -o $(appname) $(objects) $(CFLAG) $(LIBS) $(RZFLAGS)

furiatuneSet2SS.o:	FuriatuneSet2SS.c
	gcc -c -w FuriatuneSet2SS.c $(CFLAG) $(RZFLAGS)

clean:
	rm $(objects) $(appname)
