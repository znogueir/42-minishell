# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <string.h>

int i = 0;

int main()
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        printf("child: %d\n", ++i);
    }
    else
    {
        wait(NULL);
        printf("parent: %d\n", i);
    }
}