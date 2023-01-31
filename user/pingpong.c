/**
 * 功能：利用一对pipes在两个进程之间ping-pong一个字节
 *       1、父进程发送一个字节给子进程
 *       2、子进程打印“<pid>: received ping”,然后将pipe上的字节写回给父进程，最后退出
 *       3、父进程读取来自子进程的字节，并打印“<pid>: received pong”，最后退出
 *
 */
#include "kernel/types.h" // 定义uint等类型
#include "kernel/stat.h"
#include "user/user.h" // 库函数和system call都在这里声明

int
main(int argc, char* argv[]){
    int fd[2];
    char ping='a';
    char pong;
    pipe(fd); // create a pipe
    
    if(fork()==0){// 子进程
        printf("%d: received ping\n", getpid());
	read(fd[0], &pong, 1); // 读取父进程写在管道上的字节，当父进程没有写的时候，因为管道上没有数据，所以会阻塞
	write(fd[1], &pong, 1); // 将读取的字节写回给父进程
	exit(0);
	
    }else{// 父进程
	write(fd[1], &ping, 1);// 写一个字节给管道
	wait(0); // 等子进程结束
        read(fd[0], &ping, 1); //读取来自子进程的字节
	printf("%d: received pong\n", getpid());
	exit(0);
    }

}
