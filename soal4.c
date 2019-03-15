#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <sys/sysmacros.h>
#include <string.h>

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
  int count=1;
  while(1) {
	   struct stat info_file;
	   char file[]="/home/yusran/Documents/makanan/makan_enak.txt";
	   stat(file, &info_file);
	   time_t now;
           time(&now);
	   int interval = difftime(now, info_file.st_atime); 
	   if(interval<=30){ 
	   	char path[150],str[20];
		strcpy(path, "/home/yusran/Documents/makanan/makan_sehat");
	     	sprintf(str,"%d.txt",count);
	     	strcat(path,str);
	     	FILE *newFile;
	    	newFile = fopen(path,"w");
	     	fclose(newFile);
	     	count++;
	     	sleep(5);
	     	}
  }
  exit(EXIT_SUCCESS);
}
