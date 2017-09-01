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

#include "furiatuneset.h"

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

void RunFuriatune(char parameter[PATH_MAX])
{
  strcpy(furiatunePATH, "SYS:C/furiatune >NIL: ");
  strcat(furiatunePATH, parameter);
  //printf("%s\n", parameter);
  Execute(furiatunePATH, NULL, NULL);
}

int main(void)
{
    fp = Open("SYS:Prefs/Env-Archive/furiatunegui.prefs",MODE_OLDFILE);
    strcpy(result,"");
    if (fp)
    {
        //printf("File in operation \n");
        while(FGets(fp, path, PATH_MAX))
        {
            strcat(result, path);
        }
        Close(fp);
    }
   // else
   // {
   //     printf("Prefs file not found for furiatuneGUI\n");
   // }

    if (strstr(result, results[5]) != NULL)
    {
       RunFuriatune("ide on");
    }
    else
    {
       RunFuriatune("ide off");
    }
    
    return 0;
}
