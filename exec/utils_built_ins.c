#include "minishell.h"

int salto_linea(char *line)
{
    int i;

    i = 0;
    if(!ft_strnstr(line, "-n", 2))
        return(0);
    while(line[i])
    {
        if(line[i] == '-' && line[i + 1] == 'n' && line[i + 2] == ' ')
            return(1);
        i++;
    }
    return(0);
}