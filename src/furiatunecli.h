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

#ifndef FURIATUNECLI_H
#define FURIATUNECLI_H

//ULONG seconds; /* Seconds */
ULONG micros;  /* Micros */
int statusresult, i;

#define PATH_MAX    64
#define CAPLEN    32
BPTR fp;
UBYTE path[PATH_MAX];
UBYTE result[PATH_MAX];
char furiatunePATH[PATH_MAX];

// About
struct EasyStruct aboutreq =
{
   sizeof(struct EasyStruct),
   0,
   "About",
   "Furiatune GUI 1.1 (C) 2017\nCoded by emarti, Murat OZDEMIR\n\nWeb: https://github.com/emartisoft\nLoves from Turkey!\nStay with the Amiga!",
   "Ok"
};

#ifndef min
#define min(a,b) ( (a) < (b) ? (a) : (b) )
#endif

void mid(const char *src, size_t start, size_t length, char *dst, size_t dstlen)
{       size_t len = min( dstlen - 1, length);

        strncpy(dst, src + start, len);
        // zero terminate because strncpy() didn't ?
        if(len < length)
                dst[dstlen-1] = 0;
}

// furiatune outputs
char *results[10] =
{
    "no furia expansion board installed",
    "Cache is on",
    "Cache is off",
    "FPU is on",
    "FPU is off",
    "IDESpeedup is on",
    "IDESpeedup is off",
    "MapROM is active",
    "ROM mapping is inactive",
    "ShadowROM is active"
};

BOOL fileExist(STRPTR filePath)
{
  fp= Open(filePath, MODE_OLDFILE);
  if(fp)
  {
    Close(fp);
    return(1);
  }
  else
  {
    return(0);
  }
}

/*
C Cache
F FPU
I IDESpeedup
M Maprom
S Shadowrom

43210
MSIFC

ex.: 12 -> 01100
Fpu and Cache are off
IDESpeedup is on and ShadowROM is active
ROM mapping is inactive
*/
void furiatunestatus(void)
{
    statusresult=0;
    Execute("SYS:C/furiatune status >RAM:furiatune.log", NULL, NULL);
    fp = Open("RAM:furiatune.log", MODE_OLDFILE);
    strcpy(result,"");
    if(fp)
    {
        while(FGets(fp, path, PATH_MAX))
        {
            strcat(result, path);
        }
        Close(fp);
    }

    for(i=1;i<10;i++)
    {
        if (strstr(result, results[i]) != NULL)
        {
                switch (i) {
                    case 0: statusresult = 0; break; // no furia
                    case 1: statusresult +=1; break; // Cache on
                    case 3: statusresult +=2; break; // fpu on
                    case 5: statusresult +=4; break; // ide on
                    case 7: statusresult +=16; break; // maprom active
                    case 9: statusresult +=8; break; // shadowrom active
                }
        }
    }
}

void RunFuriatune(char parameter[PATH_MAX])
{
  strcpy(furiatunePATH, "SYS:C/furiatune >NIL: ");
  strcat(furiatunePATH, parameter);
  //printf("%s\n", parameter);
  Execute(furiatunePATH, NULL, NULL);
}

void xAbout(void)
{
  EasyRequest(NULL, &aboutreq, NULL, NULL);
}

void xDefault(void)
{
  printf("Resetted settings to defaults (reboots if needed)\n");
  RunFuriatune("default");
}

void xReboot(void)
{
  printf("Rebooting your Amiga...\n");
  RunFuriatune("reboot");
}

void xAddMem(void)
{
  printf("Added 1.5 MB of memory\n");
  RunFuriatune("addmem");
}

void xFpuOn(void)
{
  printf("Enabled onboard FPU (reboots if needed)\n");
  RunFuriatune("fpu on");
}

void xFpuOff(void)
{
  printf("Disabled onboard FPU (reboots if needed)\n");
  RunFuriatune("fpu off");
}

void xCacheOn(void)
{
  printf("Enabled CPU Cache\n");
  RunFuriatune("cache on");
}

void xCacheOff(void)
{
  printf("Disabled CPU Cache\n");
  RunFuriatune("cache off");
}

void xIdeOn(void)
{
  printf("Enabled IDE Speed up function\n");
  RunFuriatune("ide on");
  Execute("SYS:C/furiatune status >SYS:Prefs/Env-Archive/furiatunegui.prefs",NULL,NULL);
}

void xIdeOff(void)
{
  printf("Disabled IDE Speed up function\n");
  RunFuriatune("ide off");
  Execute("SYS:C/furiatune status >SYS:Prefs/Env-Archive/furiatunegui.prefs",NULL,NULL);
}

void xShadow(void)
{
  printf("Enabled ShadowROM 32 bit access\n");
  RunFuriatune("shadowrom");
}

void xBoard(void)
{
  printf("Disabled ShadowROM/MapROM function\n");
  RunFuriatune("boardrom");
}

void xMap(STRPTR mapromfile)
{
  STRPTR cmd = "maprom ";
  printf("Enabled MapROM function\n");
  strcat(cmd, mapromfile);
  xBoard();
  RunFuriatune(cmd);
  xReboot();
}

#endif
