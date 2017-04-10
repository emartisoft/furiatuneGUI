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

Version: 1.0 02042017
Target OS: AmigaOS2.X/3.X

FuriatuneGUI is a graphical user interface for the furiatune*
to run on Amiga 600 with Furia Expansion Board only.
The interface is very simple and user-friendly, it offers easy
access to documented furiatune* parameters without the need
for command-line usage.

(*) furiatune is a simple tool, that handles all the functions of the
FuriaEC020 accelerator card. More info at http://www.kuchinka.cz/furia/

Web: https://github.com/emartisoft
email: dtemarti@gmail.com

Created : 02 Apr 2017
Modified: 09 Apr 2017
*/

#ifndef ON_H
#define ON_H

USHORT onData[38] = {
	0x0000,0x0000,0x0c90,0x12d0,0x12b0,0x1290,0x0c90,0x0000,
	0x0000,0x0000,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
	0xffff,0xffff,0xffff,0xffff,0xffff,0xf36f,0xed2f,0xed4f,
	0xed6f,0xf36f,0xffff,0xffff,0x0000,0xffff,0xffff,0xffff,
	0xffff,0xffff,0xffff,0xffff,0xffff,0xffff
};

struct Image on = {
	0,0,		/* relative coordinates */
	16,19,		/* width and height */
	2,		/* bitplanes */
	NULL,		/* data pointer */
	0x003,0x000,		/* PlanePick & PlaneOnOff */
	NULL		/* next image */
};

#endif
