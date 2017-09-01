/*
This file is part of FuriatuneGUI.
FuriatuneSET by emarti, Murat Özdemir (C) 2017

FuriatuneSET is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

FuriatuneSET is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with FuriatuneSET.  If not, see <http://www.gnu.org/licenses/>.

Version: 1.0 01092017
Target OS: AmigaOS2.X/3.X

Web: https://github.com/emartisoft
email: dtemarti@gmail.com
*/

#include <dos/dos.h>

#define PATH_MAX    64
BPTR fp;
UBYTE path[PATH_MAX];
UBYTE result[PATH_MAX];
char furiatunePATH[PATH_MAX];

