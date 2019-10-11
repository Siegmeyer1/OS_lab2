#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    char buf[160];
    int fd[2];
    pid_t pid;
    if (pipe(fd) < 0){
        printf("Can\'t create pipe\n");
        return -1;
    }

    gets(buf);

    pid = fork();
    if (pid < 0){
        printf("Can\'t fork\n");
        return -1;

    } else if (pid > 0){
        close(fd[1]);
        char c = '1';
        while (c != EOF)
        {
            read(fd[0], &c, sizeof(char));
            if (c != EOF) {
                if (('a' <= (int)c) && ((int)c <= 'z'))
                    c = c - 32;
                printf("%c", c);
            }
        }
        close(fd[0]);
        return 0;

    } else {
        char c = EOF;
        close(fd[0]);
        dup2(fd[1], 1);
        system(buf);
        write(1, &c, 1);
        close(fd[1]);
        exit(0);
    }
}