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
