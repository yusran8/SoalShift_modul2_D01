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

  if ((chdir("/home/yusran/Documents/sisop/modul2/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    // main program here
     time_t t = time(NULL);
     struct tm tm = *localtime(&t);
     char name[50];
     char direktori[50] = "/home/yusran/log/";
     char *fileName  = "log";
     char *ext = ".log";
     mkdir(direktori, 0777);
     // printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon +1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
     sprintf(name, "%d:%d:%d-%d:%d/", tm.tm_mday, tm.tm_mon +1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
     //printf("%s\n", nama);
     strcat(direktori, name);
     mkdir(direktori, 00777);

     int k = 1, count;
     FILE *log = NULL, *syslog;
     char name_buffer[100], ch;
     while(k < 31){
         sprintf(name_buffer, "%s%s%d%s", direktori, fileName, k, ext);
         log = fopen(name_buffer, "w");
         syslog = fopen("/var/log/syslog", "r");
         fseek(syslog, 0L, SEEK_END);
         count = ftell(syslog);
         fseek(syslog, 0L, SEEK_SET);
         while(count--){
           ch = fgetc(syslog);
           fputc(ch, log);
         }
         k++;
         fclose(log);
         fclose(syslog);
         sleep(60);
     }
  }
  
  exit(EXIT_SUCCESS);
}
