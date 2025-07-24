#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define END 35
__attribute__((noreturn))
void primeproc(int p[2]){
    close(p[1]);
    int prime;
    if(read(p[0], &prime, sizeof(int)) != sizeof(int)){
        close(p[0]);
        exit(0);
    }

    printf("prime %d\n", prime);
    int next;
    int nextp[2];
    pipe(nextp);
    if(fork()==0){
        close(p[0]);
        primeproc(nextp);
        exit(0);
    }else{
        while(read(p[0], &next, sizeof(int))==sizeof(int)){
            if(next % prime!=0){
                write(nextp[1], &next, sizeof(int));
            }
        }
        close(p[0]);
        close(nextp[1]);
        wait(0);
        exit(0);
    }
}

int main(int argc, char* argv[]){
    int p[2];// p[0]read, p[1]write;

    pipe(p);

    if(fork()==0){
        primeproc(p);
        exit(0);
    }else{
        for(int i = 2;i <=END;i++ ){
            write(p[1], &i, sizeof(i));
        }
        close(p[1]);
        wait(0);
        exit(0);
    }
}