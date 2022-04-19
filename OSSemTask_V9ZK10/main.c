#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define FIFO_NAME "Fifo"


int lnko(int n1, int n2);

int main()
{
    int n;
    int i;
    pid_t pid;
    FILE* ptr;

    ptr = fopen("input.txt", "r");
    if (NULL == ptr)
    {
        printf("file can't be opened \n");
    }

    FILE *fptr = fopen("output.txt", "w");
    if (fptr == NULL)
    {
        printf("Could not open file");
        return 0;
    }

    fscanf(ptr, "%d", &n);
    printf("%d\n", n);

    int fd[2];


    if(pipe(fd)==-1)
    {

        printf("An error");
        return 1;

    }


    if(mkfifo(FIFO_NAME, 0666) < 0){
    perror("mkfifo");
    }

    int id = fork();



    if(id == 0)
    {
        close(fd[0]);


        int x;
        int y;


        for(i = 0; i < n ; i++)
        {

            fscanf(ptr,"%d %d", &x, &y);

            write(fd[1], &x, sizeof(int));
            write(fd[1], &y, sizeof(int));

        }



        close(fd[1]);
    }

    else
    {
        close(fd[1]);
        int y;
        int z;


        for(i = 0; i < n; i++)
        {
            read(fd[0], &y, sizeof(int));
            read(fd[0], &z, sizeof(int));


            printf("got from child proc %d %d %d\n", y, z, lnko(y,z));

            fprintf(fptr,"%d %d %d\n", y, z, lnko(y,z));

        }


        close(fd[0]);


    }

    return 0;
}



int lnko(int n1, int n2)
{
    int gcd = -1;
    int i;
    for(i=1; i <= n1 && i <= n2; ++i)
    {

        if(n1%i==0 && n2%i==0)
            gcd = i;
    }
    return gcd;
}

