#include <stdio.h>
#include <time.h>
#include <stdlib.h>

char *timestr(struct tm t, char *time_str)
{
    time_t now = time(NULL);
    t = *localtime(&now);
    printf("It is: %s", asctime(&t));
}

int main()
{
    char *str_time = malloc(256 * sizeof(char));
    struct tm t;
    timestr(t, str_time);
    
    return 0;
}