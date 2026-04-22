#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    while(1)
    {
        malloc(1024*1024);
        printf("mem\n");
        sleep(1);
    }
}
