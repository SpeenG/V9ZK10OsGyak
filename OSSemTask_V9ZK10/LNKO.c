#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int lnko(int n1, int n2);

int main()
{
    //sorok számát fogja tárolni ebben
    int n;
    //for ciklushoz szükséges változó
    int i;
    pid_t pid;
    FILE* ptr;

    //deklarálja a beolvasandó file-t
    ptr = fopen("input.txt", "r");
    if (NULL == ptr)
    {
        printf("file can't be opened \n");
    }


    //deklarálja a file-t amibe írni fog
    FILE *fptr = fopen("output.txt", "w");
    if (fptr == NULL)
    {
        printf("Could not open file");
        return 0;
    }


    //beolvassa az elsõ sort ami tartalmazza a méretet
    fscanf(ptr, "%d", &n);
    printf("%d\n", n);

    int fd[2];


    if(pipe(fd)==-1)
    {

        printf("An error");
        return 1;

    }

    int id = fork();



    if(id == 0)
    {
        close(fd[0]);

        //elõször is bezárja a kimeneti részét a csõvezetéknek,
        //majd for ciklus segítségével kettesével a csõbe "tölti" a számokat

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

//Bezárja az olvasó részét a csõvezetéknek,
//majd forciklus segítségével, szintén kettesével
//kiolvassa a számokat változókba, és utána
//kiirja a konzolra, és egyben file-ba is a számpárokat lnko-val együtt

        for(i = 0; i < n; i++)
        {
            read(fd[0], &y, sizeof(int));
            read(fd[0], &z, sizeof(int));


            printf("%d %d %d\n", y, z, lnko(y,z));

            fprintf(fptr,"%d %d %d\n", y, z, lnko(y,z));

        }


        close(fd[0]);


    }

    return 0;
}


//lnko metodus i-vel való oszthatóság alapján vizsgálja
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
