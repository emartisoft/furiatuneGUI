#
# FuriatuneGUI by emarti
# Version  : 1.0 02042017
# Target OS: Amiga OS2.X/3.X
# Compiler : GCC
#

objects = furiatuneguiMain.o
appname = furiatuneGUI

CFLAG = -O2 -m68000
LIBS 	= -noixemul
RZFLAGS = -fstrength-reduce -msmall-code -Wimplicit \
          -Wstrict-prototypes -s -Os -Wall -fomit-frame-pointer

furiatuneguiMain:	$(objects)
	gcc -o $(appname) $(objects) $(CFLAG) $(LIBS) $(RZFLAGS)

furiatuneguiMain.o:	furiatuneguiMain.c furiatunegui.c on.h off.h \
	furiagirl.h furiatunecli.h furiatunegui.h
	gcc -c -w furiatuneguiMain.c $(CFLAG) $(RZFLAGS)

clean:
	rm $(objects) $(appname)
