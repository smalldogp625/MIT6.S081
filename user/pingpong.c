#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char argv[]){
    int p[2];//P[1]写， P[0]读
    char* par2chl = "a";
    char* chl2par = "b";
    char buf[2];
    pipe(p);
    if(fork() == 0){ // 子进程
        if(read(p[0], buf, 1)!=1){
            fprintf(2, "Can not receive parent !\n");
            exit(1);
        }
        printf("chiled received:%c \n", buf[0]);
        close(p[0]);

       printf("%d: received ping\n", getpid());
        if (write(p[1], chl2par, 1) != 1){
            fprintf(2, "Can't write to parent!");
        }
        close(p[1]);
        exit(0);
    }else{ //父进程
        if(write(p[1], par2chl, 1 ) != 1){
            fprintf(2, "Can not send to chiled! \n");
            exit(1);
        }
        close(p[1]);

        wait(0);
        if(read(p[0], buf, 1)!=1){
            fprintf(2, "Can not receive child !\n");
            exit(1);
        }
        printf("parent received : %c\n", buf[0]);
        close(p[0]);
        printf("%d: received pong\n", getpid());
        exit(0);
    }


}