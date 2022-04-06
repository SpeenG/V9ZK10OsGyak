#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    char buf[20];

    int bufLength;
    int fileDescriptor;
    int writeInfo;
    int seekInfo;
    int readInfo;

    fileDescriptor = open("V9ZK10.txt", O_RDWR);
    if(fileDescriptor == -1)
    {
        perror("Megnyitasi hiba!");
        exit(fileDescriptor);
    }
    printf("File Descriptor erteke: %d\n", fileDescriptor);


    seekInfo = lseek(fileDescriptor, 0, SEEK_SET);
    if(seekInfo == -1)
    {
        perror("A pozicionalas nem volt sikeres!");
        exit(seekInfo);
    }
    printf("A kurzor pozicioja: %d\n", seekInfo);

    readInfo = read(fileDescriptor, buf, 15);
    if(readInfo == -1)
    {
        perror("Az olvasas sikertelen volt!");
        exit(seekInfo);
    }
    printf("A read() erteke: %d\n", readInfo);
    printf("A beolvasott ertek: %s\n", buf);

    strcpy(buf, "\nEz egy teszt\n");
    bufLength = strlen(buf);
    writeInfo = write(fileDescriptor, buf, bufLength);

    if(writeInfo == -1)
    {
        perror("Az iras sikertelen volt!");
        exit(writeInfo);
    }
    printf("A write-al beirt byte-ok szama: %d\n", writeInfo);

    return 0;
}


