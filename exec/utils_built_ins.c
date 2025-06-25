#include "minishell.h"

int valid_n_option(char *str)
{
    int i;
    
    if (!str || str[0] != '-' || !str[1])
        return (0);
    i = 1;
    while (str[i])
    {
        if (str[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}
