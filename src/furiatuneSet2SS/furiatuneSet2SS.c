/*
This file is part of FuriatuneGUI.
FuriatuneGUI by emarti, Murat Özdemir (C) 2017

FuriatuneGUI is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

FuriatuneGUI is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with FuriatuneGUI.  If not, see <http://www.gnu.org/licenses/>.

Target OS: AmigaOS2.X/3.X

Web: https://github.com/emartisoft
email: dtemarti@gmail.com
*/

//
// Add command-lines to the beginning of the S:Startup-Sequence file
//

#include <dos/dos.h>

#define PATH_MAX    256
BPTR fs, fsb;
UBYTE path[PATH_MAX];

int main(void)
{
	fs = Open("SYS:S/Startup-Sequence", MODE_NEWFILE);
	fsb = Open("SYS:S/Startup-Sequence.backup", MODE_OLDFILE);
	if (fsb)
	{
		if (fs)
		{
			FPuts(fs, ";---------------------------------------\n");
			FPuts(fs, ";Added command-lines by furiatuneGUI 1.2\n");
			FPuts(fs, "If Exists SYS:C/furiatuneSet\n");
			FPuts(fs, "		Execute SYS:C/furiatuneSet\n");
			FPuts(fs, "EndIf\n");
			FPuts(fs, ";---------------------------------------\n\n");

			while(FGets(fsb, path, PATH_MAX))
			{
				FPuts(fs, path);
			}
		}
	}
	Close(fsb);
	Close(fs);
	return 0;
}
