#include <stdio.h>

int random_procedure()
{
    return 23;
}

int main(void)
{
    int i = 0;
    int x = 5;
    int y = -1;

    while (i < 10)
    {
        i = i + 1;
        y = i + x;
        printf("%d", i);
        if (i > 5)
        {
            x = i;
            printf("more than 5");
        }
    }

    random_procedure();

    for (int j = 0; j < 5; j++)
    {
        int z = j + y;
        printf("%d", z);
        random_procedure();
    }
    return 0;
}
