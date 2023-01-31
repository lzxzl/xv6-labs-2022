#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char* argv[]){
    int cnt = 0;
    // If the user forgets to pass an argument, sleep should print an error message.
    if(argc < 2){
        fprintf(2, "Usage: sleep second \n");
        exit(1);
    }
    cnt = atoi(argv[1]);
    sleep(cnt);
    exit(0);
}
