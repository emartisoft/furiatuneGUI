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
Version: 1.1 01092017
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
Modified: 10 Apr 2017
Modified: 01 Sep 2017
*/

#ifndef FURIATUNEGUI_H
#define FURIATUNEGUI_H

#define FuriatuneGUIMenu 0
#define FuriatuneGUIMenuReboot 0
#define FuriatuneGUIMenuBar 1
#define FuriatuneGUIMenuClose 2
#define ConfigMenu 1
#define fMenuDefault 0
#define fMenuBar1 1
#define fMenuFpuon 2
#define fMenuFpuoff 3
#define fMenuBar2 4
#define fMenuCacheon 5
#define fMenuCacheoff 6
#define fMenuBar3 7
#define fMenuIdeon 8
#define fMenuIdeoff 9
#define fMenuBar4 10
#define fMenuShadowrom 11
#define fMenuMaprom 12
#define fMenuBoardrom 13
#define fMenuBar5 14
#define fMenuAddmem 15
#define HelpMenu 2
#define HelpMenuAbout 0
#define fwindowFirstID 0
#define bAbout 0
#define bReboot 1
#define bDefaults 2
#define bAddMegs 3
#define tFPU 4
#define tCache 5
#define tIDE 6
#define tShadow 7
#define tMap 8
#define fMapromWindowFirstID 0
#define lMaprom 0
#define tMaprom 1
#define bOkay 2
#define bCancel 3

extern struct TextAttr topaz800;
extern struct Menu *fMenu;
extern struct Gadget *fwindowGadgets[9];
extern struct Gadget *fwindowGList;
extern struct Window *fwindow;
extern APTR fwindowVisualInfo;
extern APTR fwindowDrawInfo;
extern UWORD fwindowGadgetTypes[];
extern struct NewGadget fwindowNewGadgets[];
extern struct Library *GadToolsBase;
extern struct IntuitionBase *IntuitionBase;
extern struct Image off;
extern struct Image on;
extern struct Image furiagirl;

extern int MakeMenufMenu( APTR MenuVisualInfo );
extern void RendWindowfwindow( struct Window *Win, void *vi );
extern int OpenWindowfwindow( void );
extern void CloseWindowfwindow( void );
extern void RendWindowfMapromWindow( struct Window *Win, void *vi );
extern int OpenWindowfMapromWindow( void );
extern void CloseWindowfMapromWindow( void );
extern int OpenLibs( void );
extern void CloseLibs( void );
extern int MakeImages( void );
extern void FreeImages( void );

#endif
