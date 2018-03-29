#include <stdio.h>
#include <stdlib.h>
#define BLOCK_SIZE 512
int main()
{
    printf("Start\n");
    char *buf = malloc(BLOCK_SIZE);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 7; j >= 0; j--)
        // for (int j = 0; j < 8; j++)
        {
            // printf("%d ", (j+1) & 1);
            if (!(buf[i] >> j & 1))
            {
                printf("%d\n", (i * 8) + (7 - j));
            }
        }
        printf("\n");
    }

    // printf("value : %d\n", value);
}