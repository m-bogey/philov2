//#include "mini_shell.h"
#include <stdio.h>
#include <stdlib.h>
int	main()
{
    char *path = getenv("ntm");
    printf("%s\n", path);
}