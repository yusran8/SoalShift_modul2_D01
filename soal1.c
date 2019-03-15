#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
 
  char *ptrToSubString, *ptrToSubString2;
      char fileName[100], newFileName[100], path_awal[150], path_akhir[150] ;
      strcpy(path_awal, "/home/yusran/Documents/sisop/modul2/gambar/");
      strcpy(path_akhir, "/home/yusran/Documents/sisop/modul2/gambar/");
      DIR *dir;
      struct dirent *ent;
      dir = opendir("/home/yusran/Documents/sisop/modul2/gambar");
 
              while((ent = readdir(dir)) != NULL) {
                     strcpy(fileName,ent->d_name);
                     ptrToSubString = strstr(fileName,".png");
                     if (ptrToSubString != NULL) {
                         printf("%s",ent->d_name);
                         ptrToSubString2 = strstr(fileName, "_grey.png");
                         if(ptrToSubString2 != NULL)
                             continue;
                         else{       


                           
                             strtok(fileName,".png");
                             strcpy(newFileName,fileName);
                             strcat(newFileName,"_grey.png");
                             strcat(fileName,".png");
                             strcat(path_awal,fileName);
                             strcat(path_akhir,newFileName);
                             rename(path_awal,path_akhir);
                          }
                    } else {
                        continue;
                    }
              }
              closedir(dir);

//    sleep(30);
  }
  exit(EXIT_SUCCESS);
}
