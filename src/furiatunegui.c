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
Modified: 10 Apr 2017
*/

#include <exec/types.h>
#include <exec/memory.h>
#include <exec/libraries.h>
#include <dos/dos.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <intuition/screens.h>
#include <intuition/intuition.h>
#include <intuition/gadgetclass.h>
#include <libraries/gadtools.h>
#include <utility/utility.h>
#include <workbench/workbench.h>
#include <clib/intuition_protos.h>
#include <clib/gadtools_protos.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "furiatunecli.h"
#include "furiatunegui.h"
#include "on.h"
#include "off.h"
#include "furiagirl.h"

struct Menu *fMenu = NULL;

struct NewMenu fMenuNewMenu[] =
{
    NM_TITLE, (STRPTR)"FuriatuneGUI"               ,  NULL , 0, NULL, (APTR)~0,
    NM_ITEM , (STRPTR)"Reboot Amiga"               ,  NULL , 0, 0L, (APTR)~0,
    NM_ITEM , NM_BARLABEL                          ,  NULL , 0, 0L, (APTR)~0,
    NM_ITEM , (STRPTR)"Close"                      ,  NULL , 0, 0L, (APTR)~0,
    NM_TITLE, (STRPTR)"Configuration"              ,  NULL , 0, NULL, (APTR)~0,
    NM_ITEM , (STRPTR)"Reset settings to defaults" ,  NULL , 0, 0L, (APTR)~0,
    NM_ITEM , NM_BARLABEL                          ,  NULL , 0, 0L, (APTR)~0,
    NM_ITEM , (STRPTR)"FPU -> on"                  ,  NULL , 0, 0L, (APTR)~0,
    NM_ITEM , (STRPTR)"FPU -> off"                 ,  NULL , 0, 0L, (APTR)~0,
    NM_ITEM , NM_BARLABEL                          ,  NULL , 0, 0L, (APTR)~0,
    NM_ITEM , (STRPTR)"CPU Cache -> on"            ,  NULL , 0, 0L, (APTR)~0,
    NM_ITEM , (STRPTR)"CPU Cache -> off"           ,  NULL , 0, 0L, (APTR)~0,
    NM_ITEM , NM_BARLABEL                          ,  NULL , 0, 0L, (APTR)~0,
    NM_ITEM , (STRPTR)"IDE Speedup -> on"          ,  NULL , 0, 0L, (APTR)~0,
    NM_ITEM , (STRPTR)"IDE Speedup -> off"         ,  NULL , 0, 0L, (APTR)~0,
    NM_ITEM , NM_BARLABEL                          ,  NULL , 0, 0L, (APTR)~0,
    NM_ITEM , (STRPTR)"ShadowROM -> on"            ,  NULL , 0, 0L, (APTR)~0,
    NM_ITEM , (STRPTR)"Select MapROM file"         ,  NULL , 0, 0L, (APTR)~0,
    NM_ITEM , (STRPTR)"Disables ShadowROM/MapROM"  ,  NULL , 0, 0L, (APTR)~0,
    NM_ITEM , NM_BARLABEL                          ,  NULL , 0, 0L, (APTR)~0,
    NM_ITEM , (STRPTR)"Add 1.5 MB of memory"       ,  NULL , 0, 0L, (APTR)~0,
    NM_TITLE, (STRPTR)"Help"                       ,  NULL , 0, NULL, (APTR)~0,
    NM_ITEM , (STRPTR)"About"                      ,  NULL , 0, 0L, (APTR)~0,
    NM_END  , NULL                                 ,  NULL , 0, 0L, (APTR)~0
};

ULONG fMenuTags[] =
{
    (GT_TagBase+67), TRUE,
    (TAG_DONE)
};

struct Window *fwindow = NULL;
APTR fwindowVisualInfo;
APTR fwindowDrawInfo;
struct Gadget *fwindowGList;
struct Gadget *fwindowGadgets[9];
UBYTE fwindowFirstRun = 0;

STRPTR strTitle = "FuriatuneGUI";
STRPTR strScreen = "FuriatuneGUI V1.1 - emarti, Murat OZDEMIR (C) 2017";

UWORD fwindowGadgetTypes[] =
{
    BUTTON_KIND,
    BUTTON_KIND,
    BUTTON_KIND,
    BUTTON_KIND,
    GENERIC_KIND,
    GENERIC_KIND,
    GENERIC_KIND,
    GENERIC_KIND,
    GENERIC_KIND
};

struct NewGadget fwindowNewGadgets[] =
{
    234, 115, 70, 13, (UBYTE *)"About", &topaz800, bAbout, 16, NULL,  NULL,
    224, 131, 80, 13, (UBYTE *)"Reboot", &topaz800, bReboot, 16, NULL,  NULL,
    214, 147, 90, 13, (UBYTE *)"Default", &topaz800, bDefaults, 16, NULL,  NULL,
    204, 163, 100, 13, (UBYTE *)"Add 1.5 MB", &topaz800, bAddMegs, 16, NULL,  NULL,
    39, 6, 16, 19, NULL, NULL, tFPU, 2, NULL,  NULL,
    39, 34, 16, 19, NULL, NULL, tCache, 2, NULL,  NULL,
    288, 6, 16, 19, NULL, NULL, tIDE, 2, NULL,  NULL,
    288, 34, 16, 19, NULL, NULL, tShadow, 2, NULL,  NULL,
    288, 62, 16, 19, NULL, NULL, tMap, 2, NULL,  NULL,
};

struct Window *fMapromWindow = NULL;
APTR fMapromWindowVisualInfo;
APTR fMapromWindowDrawInfo;
struct Gadget *fMapromWindowGList;
struct Gadget *fMapromWindowGadgets[4];
UBYTE fMapromWindowFirstRun = 0;

ULONG fMapromWindowGadgetTags[] =
{
    (GTTX_Text), (ULONG)"Enter MapROM File Path",
    (TAG_END),
    (GTST_String), (ULONG)"SYS:ROM/Kick.rom",
    (TAG_END),
};

UWORD fMapromWindowGadgetTypes[] =
{
    TEXT_KIND,
    STRING_KIND,
    BUTTON_KIND,
    BUTTON_KIND,
};

struct NewGadget fMapromWindowNewGadgets[] =
{
    4, 4, 235, 19, NULL, &topaz800, lMaprom, 1, NULL,  (APTR)&fMapromWindowGadgetTags[0],
    4, 21, 233, 18, NULL, &topaz800, tMaprom, 1, NULL,  (APTR)&fMapromWindowGadgetTags[3],
    169, 49, 68, 13, (UBYTE *)"OK", &topaz800, bOkay, 16, NULL,  NULL,
    4, 49, 68, 13, (UBYTE *)"Cancel", &topaz800, bCancel, 16, NULL,  NULL,
};

struct Library *GadToolsBase = NULL;
struct IntuitionBase *IntuitionBase = NULL;
struct TextAttr topaz800 = { (STRPTR)"topaz.font", 8, 0, 0 };

int MakeMenufMenu( APTR MenuVisualInfo )
{
    if (NULL == (fMenu = CreateMenusA( fMenuNewMenu, NULL)))
        return( 1L );
    LayoutMenusA( fMenu, MenuVisualInfo, (struct TagItem *)(&fMenuTags[0]));
    return( 0L );
}

void RendWindowfwindow(struct Window *Win, void *vi)
{
    UWORD offx,offy;
    offx = Win->BorderLeft;
    offy = Win->BorderTop;
    if (Win != NULL)
    {
        DrawImage( Win->RPort, &furiagirl, 0+offx, 0+offy);
    }
}

int OpenWindowfwindow(void)
{
    struct Screen *Scr;
    UWORD offx, offy;
    UWORD loop;
    struct NewGadget newgad;
    struct Gadget *Gad;
    struct Gadget *Gad2;
    APTR Cla;
    if (fwindowFirstRun == 0)
    {
        fwindowFirstRun = 1;
    }
    if (fwindow == NULL)
    {
        Scr = LockPubScreen(NULL);
        if (NULL != Scr)
        {
            offx = Scr->WBorLeft;
            offy = Scr->WBorTop + Scr->Font->ta_YSize+1;
            if (NULL != ( fwindowVisualInfo = GetVisualInfoA( Scr, NULL)))
            {
                if (NULL != ( fwindowDrawInfo = GetScreenDrawInfo( Scr)))
                {
                    fwindowGList = NULL;
                    Gad = CreateContext( &fwindowGList);
                    for (loop=0; loop<9; loop++)
                        if (fwindowGadgetTypes[loop] != 198)
                        {
                            CopyMem((char * )&fwindowNewGadgets[loop], ( char * )&newgad, (long)sizeof( struct NewGadget ));
                            newgad.ng_VisualInfo = fwindowVisualInfo;
                            newgad.ng_LeftEdge += offx;
                            newgad.ng_TopEdge += offy;
                            fwindowGadgets[ loop ] = NULL;
                            fwindowGadgets[ newgad.ng_GadgetID - fwindowFirstID ] = Gad = CreateGadgetA( fwindowGadgetTypes[loop], Gad, &newgad, (struct TagItem *) newgad.ng_UserData );
                            if (Gad != NULL)
                                switch (loop+fwindowFirstID)
                                {
                                    case tFPU :
                                        Gad->GadgetType |= GTYP_BOOLGADGET;
                                        Gad->GadgetRender = &on;
                                        Gad->SelectRender = &off;
                                        Gad->Activation = GACT_TOGGLESELECT|GACT_IMMEDIATE|GACT_RELVERIFY;
                                        Gad->Flags = 6;
                                        break;
                                    case tCache :
                                        Gad->GadgetType |= GTYP_BOOLGADGET;
                                        Gad->GadgetRender = &on;
                                        Gad->SelectRender = &off;
                                        Gad->Activation = GACT_TOGGLESELECT|GACT_IMMEDIATE|GACT_RELVERIFY;
                                        Gad->Flags = 6;
                                        break;
                                    case tIDE :
                                        Gad->GadgetType |= GTYP_BOOLGADGET;
                                        Gad->GadgetRender = &on;
                                        Gad->SelectRender = &off;
                                        Gad->Activation = GACT_TOGGLESELECT|GACT_IMMEDIATE|GACT_RELVERIFY;
                                        Gad->Flags = 6;
                                        break;
                                    case tShadow :
                                        Gad->GadgetType |= GTYP_BOOLGADGET;
                                        Gad->GadgetRender = &on;
                                        Gad->SelectRender = &off;
                                        Gad->Activation = GACT_TOGGLESELECT|GACT_IMMEDIATE|GACT_RELVERIFY;
                                        Gad->Flags = 6;
                                        break;
                                    case tMap :
                                        Gad->GadgetType |= GTYP_BOOLGADGET;
                                        Gad->GadgetRender = &on;
                                        Gad->SelectRender = &off;
                                        Gad->Activation = GACT_TOGGLESELECT|GACT_IMMEDIATE|GACT_RELVERIFY;
                                        Gad->Flags = 6;
                                        break;
                                }
                        }

                 for (loop=0; loop<9; loop++)
                         if (fwindowGadgetTypes[loop] == 198)
                        {
                            fwindowGadgets[ loop ] = NULL;
                            Cla = NULL;
                            if (Gad)
                                fwindowGadgets[ loop ] = Gad2 = (struct Gadget *) NewObjectA( (struct IClass *)Cla, fwindowNewGadgets[ loop ].ng_GadgetText, (struct TagItem *)fwindowNewGadgets[ loop ].ng_UserData );
                        }

                    if (Gad != NULL)
                    {
                        if (NULL != (fwindow = OpenWindowTags( NULL,
                                    (WA_Left), (Scr->Width - 315)/2,
                                    (WA_Top), (Scr->Height - 197)/2,
                                    (WA_Width), 315+offx,
                                    (WA_Height), 197+offy,
                                    (WA_Title), strTitle,
                                    (WA_ScreenTitle), strScreen,
                                    (WA_MinWidth), 313+offx,
                                    (WA_MinHeight), 197+offy,
                                    (WA_MaxWidth), 1200,
                                    (WA_MaxHeight), 1200,
                                    (WA_DragBar), TRUE,
                                    (WA_DepthGadget), TRUE,
                                    (WA_CloseGadget), TRUE,
                                    (WA_Activate), TRUE,
                                    (WA_Dummy+0x30), TRUE,
                                    (WA_SmartRefresh), TRUE,
                                    (WA_AutoAdjust), TRUE,
                                    (WA_Gadgets), fwindowGList,
                                    (WA_IDCMP),20972356,
                                    (TAG_END))))
                        {
                            RendWindowfwindow(fwindow, fwindowVisualInfo);
                            GT_RefreshWindow(fwindow, NULL);
                            RefreshGList(fwindowGList, fwindow, NULL, ~0);
                            UnlockPubScreen(NULL, Scr);
                            if (fMenu == NULL)
                                MakeMenufMenu(fwindowVisualInfo);
                            if (fMenu != NULL)
                            {
                                SetMenuStrip(fwindow, fMenu);
                                return (0L);
                            }
                            return( 0L );
                        }
                    }
                    FreeGadgets(fwindowGList);
                    FreeScreenDrawInfo(Scr, (struct DrawInfo *) fwindowDrawInfo);
                }
                FreeVisualInfo(fwindowVisualInfo);
            }
            UnlockPubScreen(NULL, Scr);
        }
    }
    else
    {
        WindowToFront(fwindow);
        ActivateWindow(fwindow);
        return( 0L );
    }
    return( 1L );
}

void CloseWindowfwindow( void )
{
    if (fwindow != NULL)
    {
        ClearMenuStrip(fwindow);
        FreeScreenDrawInfo( fwindow->WScreen, (struct DrawInfo *) fwindowDrawInfo );
        fwindowDrawInfo = NULL;
        CloseWindow( fwindow);
        fwindow = NULL;
        FreeVisualInfo( fwindowVisualInfo);
        FreeGadgets( fwindowGList);
    }
}

void RendWindowfMapromWindow( struct Window *Win, void *vi )
{
    UWORD offx,offy;
    offx = Win->BorderLeft;
    offy = Win->BorderTop;
    /* if (Win != NULL)
    {
    } */
}

int OpenWindowfMapromWindow( void )
{
    struct Screen *Scr;
    UWORD offx, offy;
    UWORD loop;
    struct NewGadget newgad;
    struct Gadget *Gad;
    struct Gadget *Gad2;
    APTR Cla;
    if (fMapromWindowFirstRun == 0)
    {
        fMapromWindowFirstRun = 1;
    }
    if (fMapromWindow == NULL)
    {
        Scr = LockPubScreen(NULL);
        if (NULL != Scr)
        {
            offx = Scr->WBorLeft;
            offy = Scr->WBorTop + Scr->Font->ta_YSize+1;
            if (NULL != ( fMapromWindowVisualInfo = GetVisualInfoA( Scr, NULL)))
            {
                if (NULL != ( fMapromWindowDrawInfo = GetScreenDrawInfo( Scr)))
                {
                    fMapromWindowGList = NULL;
                    Gad = CreateContext( &fMapromWindowGList);
                    for ( loop=0 ; loop<4 ; loop++ )
                        if (fMapromWindowGadgetTypes[loop] != 198)
                        {
                            CopyMem((char * )&fMapromWindowNewGadgets[loop], ( char * )&newgad, (long)sizeof( struct NewGadget ));
                            newgad.ng_VisualInfo = fMapromWindowVisualInfo;
                            newgad.ng_LeftEdge += offx;
                            newgad.ng_TopEdge += offy;
                            fMapromWindowGadgets[ loop ] = NULL;
                            fMapromWindowGadgets[ newgad.ng_GadgetID - fMapromWindowFirstID ] = Gad = CreateGadgetA( fMapromWindowGadgetTypes[loop], Gad, &newgad, (struct TagItem *) newgad.ng_UserData );
                        }
                    for ( loop=0 ; loop<4 ; loop++ )
                        if (fMapromWindowGadgetTypes[loop] == 198)
                        {
                            fMapromWindowGadgets[ loop ] = NULL;
                            Cla = NULL;
                            if (Gad)
                                fMapromWindowGadgets[ loop ] = Gad2 = (struct Gadget *) NewObjectA( (struct IClass *)Cla, fMapromWindowNewGadgets[ loop ].ng_GadgetText, (struct TagItem *)fMapromWindowNewGadgets[ loop ].ng_UserData );
                        }
                    if (Gad != NULL)
                    {
                        if (NULL != (fMapromWindow = OpenWindowTags( NULL,
                                    (WA_Left), fwindow->LeftEdge + 32,
                                    (WA_Top), fwindow->TopEdge + 32,
                                    (WA_Width), 246+offx,
                                    (WA_Height), 69+offy,
                                    (WA_Title), "MapROM File Path",
                                    (WA_MinWidth), 150,
                                    (WA_MinHeight), 25,
                                    (WA_MaxWidth), 1200,
                                    (WA_MaxHeight), 1200,
                                    (WA_DragBar), TRUE,
                                    (WA_DepthGadget), TRUE,
                                    (WA_CloseGadget), TRUE,
                                    (WA_Activate), TRUE,
                                    (WA_Dummy+0x30), TRUE,
                                    (WA_SmartRefresh), TRUE,
                                    (WA_AutoAdjust), TRUE,
                                    (WA_Gadgets), fMapromWindowGList,
                                    (WA_IDCMP),580,
                                    (TAG_END))))
                        {
                            RendWindowfMapromWindow(fMapromWindow, fMapromWindowVisualInfo );
                            GT_RefreshWindow( fMapromWindow, NULL);
                            RefreshGList( fMapromWindowGList, fMapromWindow, NULL, ~0);
                            UnlockPubScreen( NULL, Scr);
                            return( 0L );
                        }
                    }
                    FreeGadgets( fMapromWindowGList);
                    FreeScreenDrawInfo( Scr, (struct DrawInfo *) fMapromWindowDrawInfo );
                }
                FreeVisualInfo( fMapromWindowVisualInfo );
            }
            UnlockPubScreen( NULL, Scr);
        }
    }
    else
    {
        WindowToFront(fMapromWindow);
        ActivateWindow(fMapromWindow);
        return( 0L );
    }
    return( 1L );
}

void CloseWindowfMapromWindow( void )
{
    if (fMapromWindow != NULL)
    {
        FreeScreenDrawInfo( fMapromWindow->WScreen, (struct DrawInfo *) fMapromWindowDrawInfo );
        fMapromWindowDrawInfo = NULL;
        CloseWindow( fMapromWindow);
        fMapromWindow = NULL;
        FreeVisualInfo( fMapromWindowVisualInfo);
        FreeGadgets( fMapromWindowGList);
    }
}

int OpenLibs(void)
{
    if (NULL != (GadToolsBase = OpenLibrary((UBYTE *)"gadtools.library" , 37)))
            if ( NULL != (IntuitionBase = (struct IntuitionBase * )OpenLibrary((UBYTE *)"intuition.library" , 37)))
                return( 0L );
    CloseLibs();
    return( 1L );
}

void CloseLibs(void)
{
    if (NULL != GadToolsBase )
        CloseLibrary( GadToolsBase );
    if (NULL != IntuitionBase )
        CloseLibrary( ( struct Library * )IntuitionBase );
}

int MakeImages(void)
{
    UWORD failed = 0;
    if (NULL != (off.ImageData=(UWORD *)AllocMem( 38*2, MEMF_CHIP)))
        CopyMem( offData, off.ImageData, 38*2);
    else
        failed = 1;
    if (NULL != (on.ImageData=(UWORD *)AllocMem( 38*2, MEMF_CHIP)))
        CopyMem( onData, on.ImageData, 38*2);
    else
        failed = 1;
    if (NULL != (furiagirl.ImageData=(UWORD *)AllocMem( 7800*2, MEMF_CHIP)))
        CopyMem( furiagirlData, furiagirl.ImageData, 7800*2);
    else
        failed = 1;
    if (failed==0)
        return( 0L );
    else
    {
        FreeImages();
        return( 1L );
    }
}

void FreeImages( void )
{
    if (off.ImageData != NULL)
        FreeMem(off.ImageData, 38*2);
    off.ImageData = NULL;
    if (on.ImageData != NULL)
        FreeMem(on.ImageData, 38*2);
    on.ImageData = NULL;
    if (furiagirl.ImageData != NULL)
        FreeMem(furiagirl.ImageData, 7800*2);
    furiagirl.ImageData = NULL;
}
