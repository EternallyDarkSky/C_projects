#include <stdio.h>  
#include <utmp.h>
#include <fcntl.h>  
#include <unistd.h>  
#include <time.h>  
#include <string.h>
  
#define SHOWHOST  
  
void showtime(long timeval){  
    char* cp;  
    cp = ctime(&timeval);  
    cp[strlen(cp)-1] = '\0';
    printf("%s",cp+4);  
}  
  
void show_info(struct utmp* utbufp){  
    if(utbufp->ut_type != USER_PROCESS){  
        return ;  
    }  
  
    printf("%-8.8s",utbufp->ut_name);  
    printf(" ");  
    printf("%-8.8s",utbufp->ut_line);  
    printf(" ");  
    showtime(utbufp->ut_time);  
    printf(" ");  
  
#ifdef SHOWHOST  
    if(utbufp->ut_host[0] != '\0'){  
        printf("(%s)",utbufp->ut_host);  
    }  
#endif  
    printf("\n");  
}

int main(){  
    struct utmp current_record;  
    int utmpfd;  
    int reclen = sizeof(current_record);  
  
    if((utmpfd = open(UTMP_FILE,O_RDONLY)) == -1){  
        perror(UTMP_FILE);  
  
        return 1;  
    }  
  
    while( read(utmpfd,&current_record,reclen) == reclen ){  
        show_info(&current_record);  
    }  
  
    close(utmpfd);  
  
    return 0;  
} 