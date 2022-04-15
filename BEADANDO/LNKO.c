#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int lnko(int n1, int n2);

int main()
{
    //sorok sz�m�t fogja t�rolni ebben
    int n;
    //for ciklushoz sz�ks�ges v�ltoz�
    int i;
    pid_t pid;
    FILE* ptr;

    //deklar�lja a beolvasand� file-t
    ptr = fopen("input.txt", "r");
    if (NULL == ptr)
    {
        printf("file can't be opened \n");
    }


    //deklar�lja a file-t amibe �rni fog
    FILE *fptr = fopen("output.txt", "w");
    if (fptr == NULL)
    {
        printf("Could not open file");
        return 0;
    }


    //beolvassa az els� sort ami tartalmazza a m�retet
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

        //el�sz�r is bez�rja a kimeneti r�sz�t a cs�vezet�knek,
        //majd for ciklus seg�ts�g�vel kettes�vel a cs�be "t�lti" a sz�mokat

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

//Bez�rja az olvas� r�sz�t a cs�vezet�knek,
//majd forciklus seg�ts�g�vel, szint�n kettes�vel
//kiolvassa a sz�mokat v�ltoz�kba, �s ut�na
//kiirja a konzolra, �s egyben file-ba is a sz�mp�rokat lnko-val egy�tt

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


//lnko metodus i-vel val� oszthat�s�g alapj�n vizsg�lja
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
