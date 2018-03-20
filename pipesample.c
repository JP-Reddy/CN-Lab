#include<stdio.h>
#include<stdlib.h>
// #include <apue.h>  
// #include <sys/types>  
// #include <sys/wait.h>  

// int main(void)  
//  {  
//    int   n;  
//    int   fd[2];  
//    pid_t  pid;  
//    char  data[]="Hello world";  
//    char  line[MAXLINE];  

//    pid = fork();

//    if (pipe(fd) < 0)  
//      printf("pipe error");  
//    if (pid < 0) {  
//      printf("fork error");  
//    } else if (pid > 0) {    /* parent */  
//      close(fd[0]);  
//      write(fd[1], data, strlen(data));  
//    } else {        /* child */  
//      close(fd[1]);  
//      n = read(fd[0], line, MAXLINE);  
//      write(STDOUT_FILENO, line, n);  
//    }  
//    exit(0);  
//  }  

int main()
{
    char * msg="Hello!";
    char msg2[10];
    pid_t res;
    int fd[2];

    pipe(fd);
    res=fork();
    if(res>0)
    {
        printf("Parent is executing\n");
        close(fd[1]);
        read(fd[0],msg2,6);
        printf("%s\n",msg2);
        exit(0);
    }
    else if(res==0)
    {
        printf("Child is executing\n");

        close(fd[0]);
        write(fd[1],msg,6);
        exit(0);
    } 
    else
    {
        printf("Error!");
        exit(0);
    }
    return 1;
}