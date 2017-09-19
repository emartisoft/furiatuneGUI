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

#ifndef OFF_H
#define OFF_H

USHORT offData[38] = {
	0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
	0xffff,0x0000,0x0000,0x0000,0x19dc,0x2510,0x2598,0x2510,
	0x1910,0x0000,0x0000,0xffff,0xffff,0xffff,0xffff,0xffff,
	0xffff,0xffff,0xffff,0xffff,0x0000,0xffff,0xffff,0xe623,
	0xdaef,0xda67,0xdaef,0xe6ef,0xffff,0xffff
};

struct Image off = {
	0,0,		/* relative coordinates */
	16,19,		/* width and height */
	2,		/* bitplanes */
	NULL,		/* data pointer */
	0x003,0x000,		/* PlanePick & PlaneOnOff */
	NULL		/* next image */
};

#endif
