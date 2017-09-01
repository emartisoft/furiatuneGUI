#
# FuriatuneSet by emarti
# Version  : 1.0 01092017
# Target OS: Amiga OS2.X/3.X
# Compiler : GCC
#

objects = furiatuneset.o
appname = furiatuneSET

CFLAG = -O2 -m68000
LIBS 	= -noixemul
RZFLAGS = -fstrength-reduce -msmall-code -Wimplicit \
          -Wstrict-prototypes -s -Os -Wall -fomit-frame-pointer

furiatuneSet:	$(objects)
	gcc -o $(appname) $(objects) $(CFLAG) $(LIBS) $(RZFLAGS)

furiatuneset.o:	furiatuneset.c furiatuneset.h
	gcc -c -w furiatuneset.c $(CFLAG) $(RZFLAGS)

clean:
	rm $(objects) $(appname)
