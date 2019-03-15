#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <grp.h>
#include <pwd.h>
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

    const char* file = "/home/yusran/Documents/sisop/modul2/hatiku/elen.ku";
    struct stat fileinfo;

    if((stat(file,&fileinfo)) == 0 ) {
       
        struct passwd *pw = getpwuid(fileinfo.st_uid);  
        struct group *grp = getgrgid(fileinfo.st_gid); 

        chmod(file, 777);
        if(!strcmp(grp->gr_name,"www-data") && !strcmp(pw->pw_name,"www-data")){ 
            remove(file); 
        }
    }
     sleep(3);
  }
  
  exit(EXIT_SUCCESS);
}
