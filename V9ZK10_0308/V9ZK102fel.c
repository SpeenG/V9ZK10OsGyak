#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main()
{

    // date, pwd, who

    char parancs[50];
    printf("Adjon meg egy érvényes windows cmd parancsot! \n");
    scanf("%s", parancs);
    system(parancs);


}
