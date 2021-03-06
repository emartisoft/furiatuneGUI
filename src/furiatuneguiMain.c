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

#include "furiatunegui.c"
#include "furiatunecli.h"

int done = 0; // if done is 1 then Close Application
int m_done=0; // if done is 1 then Close 'Select Maprom File' Window
BOOL _fpu, _cache, _ide, _shadow, _map; // furiatune status

int timer = 1;
int strstart = 0;
char *caption = "";
char stringDst[CAPLEN];
const char *stringSrc = "     Hi and loves from\
 TURKEY! Coded by emarti, Murat OZDEMIR. Please, do not forget to visit furiatuneGUI\
 web site [https://github.com/emartisoft].\
 If you contact to me, send email to dtemarti@gmail.com\
 (C) 2017    ";

void PrefsVar(void)
{
	pROM = results[8];

	if (!_shadow)
	{
	  pROM = results[9];
	}

	if (!_map)
	{
	  pROM = results[7];
	}

	if (!_ide)
	{
	  pIdeSpeed = results[5];
	}
	else
	{
	  pIdeSpeed = results[6];
	}
}

void ControlStatus(void)
{
  furiatunestatus();

  // Cache
  if((statusresult & 1) == 1)
  {
    fwindowGadgets[5]->Flags &= ~SELECTED;
    _cache = FALSE;
  }
  else
  {
    fwindowGadgets[5]->Flags |= SELECTED;
    _cache = TRUE;
  }

  // FPU
  if((statusresult & 2) == 2)
  {
    fwindowGadgets[4]->Flags &= ~SELECTED;
    _fpu = FALSE;
  }
  else
  {
    fwindowGadgets[4]->Flags |= SELECTED;
    _fpu = TRUE;
  }

  // IDE SpeedUp
  if((statusresult & 4) == 4)
  {
    fwindowGadgets[6]->Flags &= ~SELECTED;
    _ide = FALSE;
  }
  else
  {
    fwindowGadgets[6]->Flags |= SELECTED;
    _ide = TRUE;
  }

  //shadowrom
  if((statusresult & 8) == 8)
  {
    fwindowGadgets[7]->Flags &= ~SELECTED;
    _shadow = FALSE;
  }
  else
  {
    fwindowGadgets[7]->Flags |= SELECTED;
    _shadow = TRUE;
  }

  //maprom
  if((statusresult & 16) == 16)
  {
    fwindowGadgets[8]->Flags &= ~SELECTED;
    _map = FALSE;
  }
  else
  {
    fwindowGadgets[8]->Flags |= SELECTED;
    _map = TRUE;
  }

  // Refresh window for togglebutton
  GT_RefreshWindow( fwindow, NULL);
  RefreshGList( fwindowGList, fwindow, NULL, ~0);

  PrefsVar();
}

void UpdateToggleButton(int GadgetIndex, BOOL statu)
{
  if (statu)
    fwindowGadgets[GadgetIndex]->Flags |= SELECTED;
  else
    fwindowGadgets[GadgetIndex]->Flags &= ~SELECTED;
  // Refresh window for togglebutton
  GT_RefreshWindow( fwindow, NULL);
  RefreshGList( fwindowGList, fwindow, NULL, ~0);
}

void SelectMapromFile(void)
{
  ULONG m_clas;
  UWORD m_code;
  struct Gadget *m_pgsel;
  struct IntuiMessage *m_imsg;

  m_done= 0;
  if (OpenWindowfMapromWindow()==0)
  {
    WindowToFront(fMapromWindow);
    ActivateWindow(fMapromWindow);
    MoveWindowInFrontOf(fMapromWindow, fwindow);
    while(m_done==0)
        {
                Wait(1L << fMapromWindow->UserPort->mp_SigBit);
                m_imsg=GT_GetIMsg(fMapromWindow->UserPort);
                while (m_imsg != NULL )
                    {
                    m_clas=m_imsg->Class;
                    m_code=m_imsg->Code;
                    m_pgsel=(struct Gadget *)m_imsg->IAddress; /* Only reference if it is a gadget message */
                    GT_ReplyIMsg(m_imsg);
                    ProcessWindowfMapromWindow(m_clas, m_code, m_pgsel);
                    m_imsg=GT_GetIMsg(fMapromWindow->UserPort);
                    }
                }

            CloseWindowfMapromWindow();
    }
    else
        printf("Cannot open window.\n");
}

void SavePrefsDefault(void)
{
  _ide=TRUE;
  UpdateToggleButton(6, _ide);
  _shadow=TRUE;
  UpdateToggleButton(7, _shadow);
  _map=TRUE;
  UpdateToggleButton(8, _map);
  fp = Open("SYS:Prefs/Env-Archive/furiatunegui.prefs", MODE_NEWFILE);
  if (fp)
  {
	FPuts(fp, "IDESpeedUp is off\nROM Mapping is inactive");
	Close(fp);
  }

  Changed=FALSE;
  Default=TRUE;
}

void ProcessMenuIDCMPfMenu( UWORD MenuNumber)
{
  UWORD MenuNum;
  UWORD ItemNumber;
  UWORD SubNumber;
  int Done=0;                        /* Set Done to 1 to forget rest of next selects. */
  struct MenuItem *item;
  while ((MenuNumber != MENUNULL) && (Done == 0))
	{
		item = ItemAddress( fMenu, MenuNumber);
		MenuNum = MENUNUM(MenuNumber);
		ItemNumber = ITEMNUM(MenuNumber);
		SubNumber = SUBNUM(MenuNumber);
		switch ( MenuNum )
		{
			case NOMENU :
				/* No Menu Selected. */
				break;
			case FuriatuneGUIMenu :
				switch ( ItemNumber )
				{
					case NOITEM :
						/* No Item selcted. */
						break;
					case FuriatuneGUIMenuReboot :
						/* Item Text : Reboot Amiga */
						xReboot();
						break;
					case FuriatuneGUIMenuClose :
						/* Item Text : Close */
						done = 1;
						break;
				}
				break;
			case ConfigMenu :
				switch ( ItemNumber )
				{
					case NOITEM :
						/* No Item selcted. */
						break;
					case fMenuDefault :
						/* Item Text : Reset settings to defaults */
						SavePrefsDefault();
						break;
					case fMenuFpuon :
						/* Item Text : FPU -> on */
						xFpuOn();
						_fpu = FALSE;
						UpdateToggleButton(4, _fpu);
						break;
					case fMenuFpuoff :
						/* Item Text : FPU -> off */
						xFpuOff();
						_fpu = TRUE;
						UpdateToggleButton(4, _fpu);
						break;
					case fMenuCacheon :
						/* Item Text : CPU Cache -> on */
						xCacheOn();
						_cache = FALSE;
						UpdateToggleButton(5, _cache);
						break;
					case fMenuCacheoff :
						/* Item Text : CPU Cache -> off */
						xCacheOff();
						_cache = TRUE;
						UpdateToggleButton(5, _cache);
						break;
					case fMenuIdeon :
						/* Item Text : IDE Speedup -> on */
						_ide = FALSE;
						UpdateToggleButton(6, _ide);
						PrefsVar();
						if ((!_ide) & (!_map))
						{
							EasyRequest(NULL, &WarningGayle, NULL, NULL);
						}
						xIdeOn();
						break;
					case fMenuIdeoff :
						/* Item Text : IDE Speedup -> off */
						_ide = TRUE;
						UpdateToggleButton(6, _ide);
						PrefsVar();
						xIdeOff();
						break;
					case fMenuShadowrom :
						/* Item Text : ShadowROM -> on */
						_shadow = FALSE;
						_map = TRUE;
						UpdateToggleButton(7, _shadow);
						UpdateToggleButton(8, _map);
						PrefsVar();
						xShadow();
						break;
					case fMenuMaprom :
						/* Item Text : Select MapROM file */
						SelectMapromFile();
						break;
					case fMenuBoardrom :
						/* Item Text : Disables Shadow/MapROM */
						_shadow = TRUE;
						_map = TRUE;
						UpdateToggleButton(7, _shadow); // Shadowrom togglebutton is off
						UpdateToggleButton(8, _map); // maprom togglebutton is off
						PrefsVar();
						xBoard();
						break;
					case fMenuAddmem :
						/* Item Text : Add 1.5 MB of memory */
						xAddMem();
						break;
				}
				break;
			case HelpMenu :
				switch ( ItemNumber )
				{
					case NOITEM :
						/* No Item selcted. */
						break;
					case HelpMenuAbout :
						/* Item Text : About */
						xAbout();
						break;
				}
				break;
		}
		MenuNumber = item->NextSelect;
    }
}

void ProcessWindowfwindow(LONG Class, UWORD Code, APTR IAddress)
{
  struct Gadget *gad;
  switch (Class)
    {
    case IDCMP_GADGETUP :
          /* Gadget message, gadget = gad. */
          gad = (struct Gadget *)IAddress;
          switch (gad->GadgetID)
          {
                case bAbout :
                    /* Button pressed  , Text of gadget : About */
                    xAbout();
                    break;

                case bReboot :
                    /* Button pressed  , Text of gadget : Reboot */
                    xReboot();
                    break;

                case bDefaults :
                    /* Button pressed  , Text of gadget : Defaults */
		                SavePrefsDefault();
                    break;

                case bAddMegs :
                    /* Button pressed  , Text of gadget : Add 1.5 Megs */
                    xAddMem();
                    break;

                case tFPU :
                    /* FPU togglebutton */
                    _fpu = !_fpu;
                    if (!_fpu)
                    {
                      xFpuOn();
                    }
                    else
                    {
                      xFpuOff();
                    }
                    break;

                case tCache :
                    /* Cache togglebutton */
                    _cache = !_cache;
                    if (!_cache)
                    {
                      xCacheOn();
                    }
                    else
                    {
                      xCacheOff();
                    }
                    break;

                case tIDE :
                    /* IDESpeedup togglebutton */
                    _ide = !_ide;
                    PrefsVar();
                    if (!_ide)
                    {
                      xIdeOn();
                      if ((!_ide) & (!_map))
			{
            			EasyRequest(NULL, &WarningGayle, NULL, NULL);
            		}
                    }
                    else
                    {
                      xIdeOff();
                    }
                    break;

                case tShadow :
                    /* ShadowROM togglebutton */
                    _shadow = !_shadow;

                    if (!_shadow)
                    {
                      _shadow=FALSE;
                      _map = TRUE;
                      UpdateToggleButton(8, _map);
                      PrefsVar();
                      xShadow();
                    }
                    else
                    {
                      _shadow=TRUE;
                      PrefsVar();
                      xBoard();
                    }
                    break;

                case tMap :
                    /* MapROM togglebutton */

                    if (_map)
                    {
                      SelectMapromFile();
                    }
                    else
                    {
                      _map = !_map;
                      PrefsVar();
                      xBoard();
                    }
                      break;

    }
        break;

    case IDCMP_CLOSEWINDOW :
        /* CloseWindow Now */
        done = 1;
        break;

    case IDCMP_REFRESHWINDOW :
        GT_BeginRefresh( fwindow);
        /* Refresh window. */
        RendWindowfwindow( fwindow, fwindowVisualInfo );
        GT_EndRefresh( fwindow, TRUE);
        GT_RefreshWindow( fwindow, NULL);
        RefreshGList( fwindowGList, fwindow, NULL, ~0);
        break;

    case IDCMP_INTUITICKS :
        /* Timing message. */
        if (((micros / 100000) % (2 * timer)) == 0)
        {
            strcpy(caption, "FuriatuneGUI - ");
            if (!(Changed || Default))
            {
              mid( stringSrc, strstart % (strlen(stringSrc)), CAPLEN, stringDst, sizeof(stringDst));
              strcat(caption, stringDst);
            }
            else
            {
              timer=8;
              strcat(caption, flashMessage[strstart % 3]);
            }
          	strstart++;
          	SetWindowTitles(fwindow, caption, strScreen);
        }
        break;

    case IDCMP_MENUPICK :
            /* Menu Selected */
        ProcessMenuIDCMPfMenu(Code);
        break;

    case IDCMP_MENUHELP :
        break;
    }
}

void ProcessWindowfMapromWindow( LONG Class, UWORD Code, APTR IAddress )
{
STRPTR mapromfile;
struct Gadget *gad;
switch ( Class )
    {
    case IDCMP_GADGETUP :
        /* Gadget message, gadget = gad. */
        gad = (struct Gadget *)IAddress;
        switch ( gad->GadgetID )
        {
            case tMaprom :
                /* String entered  , Text of gadget :  */
                break;
            case bOkay :
                /* Button pressed  , Text of gadget : OK */
                mapromfile = ((struct StringInfo *)fMapromWindowGadgets[1]->SpecialInfo)->Buffer;
                if (fileExist(mapromfile))
                {
                  //printf("MapROM file found: %s\n", mapromfile);
                  xMap(mapromfile);
                  _map=FALSE;
                  _shadow =TRUE;
                  _ide=TRUE;
                  UpdateToggleButton(8, _map);
                  UpdateToggleButton(7, _shadow);
                  UpdateToggleButton(6, _ide);
                  PrefsVar();
                  xIdeOff();
                  //Why used xIdeOff() function?
                  //If MapROM is ON and Amiga 600 Board has GAYLE-02 chip,
                  //IDESpeedUp must be OFF. Otherwise, the system may be freeze.
                  //In addition, call SavePrefs() via xIdeOff
                  m_done = 1;
                }
                //  else
                //  {
                //    //printf("MapROM file not found: '%s'\n", mapromfile);
                //  }
                break;
            case bCancel :
                /* Button pressed  , Text of gadget : Cancel */
                UpdateToggleButton(8, _map);
                m_done = 1;
                break;
        }
        break;
    case IDCMP_CLOSEWINDOW :
        /* CloseWindow Now */
        UpdateToggleButton(8, _map);
        m_done = 1;
        break;
    case IDCMP_REFRESHWINDOW :
        GT_BeginRefresh( fMapromWindow);
        /* Refresh window. */
        RendWindowfMapromWindow( fMapromWindow, fMapromWindowVisualInfo );
        GT_EndRefresh( fMapromWindow, TRUE);
        GT_RefreshWindow( fMapromWindow, NULL);
        RefreshGList( fMapromWindowGList, fMapromWindow, NULL, ~0);
        break;
    }
}

int main(void)
{
  ULONG clas;
  UWORD code;
  struct Gadget *pgsel;
  struct IntuiMessage *imsg;

  if (OpenLibs()==0)
  {
       if (MakeImages()==0)
       {
		       //printf("***** %s *****\n", strScreen);
           if (!fileExist("SYS:C/furiatune"))
           {
              printf("***** %s *****\n", strScreen);
              printf("FuriatuneGUI needs furiatune executable file.\n");
              printf("Please, download it from http://www.kuchinka.cz/furia/\n");
              printf("And then copy it to C drawer.\n");
              printf("DO NOT FORGET THAT THIS APP RUNS ON THE A600 WITH FURIA ONLY\n");
              printf("**************************************************************\n");
            }
            else
            {
              // No furia expansion board installed
              statusresult=-1;
              furiatunestatus();
              if (statusresult==0)
              {
                printf("No Furia Expansion Board Installed\n");
                printf("DO NOT FORGET THAT THIS APP RUNS ON THE A600 WITH FURIA ONLY\n");
                printf("Sorry but you have to buy it to run this application :(\n");
              }
              else
              {
                if (OpenWindowfwindow()==0)
                {
                      ControlStatus();
                      Changed=FALSE;
                      Default=FALSE;
                      while(done==0)
                      {
                          Wait(1L << fwindow->UserPort->mp_SigBit);
                          imsg=GT_GetIMsg(fwindow->UserPort);
                          while (imsg != NULL )
                          {
                              clas=imsg->Class;
                              code=imsg->Code;
                              //seconds=imsg->Seconds; /* Seconds */
                              micros = imsg->Micros;   /* Micros */
                              pgsel=(struct Gadget *)imsg->IAddress;
                              GT_ReplyIMsg(imsg);
                              ProcessWindowfwindow(clas, code, pgsel);
                              imsg=GT_GetIMsg(fwindow->UserPort);
                          }
                      }
                      CloseWindowfwindow();
                }
                else
                    printf("Cannot open window.\n");
                FreeImages();
              }
            }
      }
      else
          printf("Cannot make images.\n");
      CloseLibs();
 }
 else
    printf("Cannot open libraries.\n");
}
