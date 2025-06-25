#include "../minishell.h"

int dobles(char *line, t_com *temp)
{
    int i = 0;
    int inicial = 0;
    int final = 0;
    int counter = 0;

    while (line[i])
    {
        if (line[i] == 39) // comillas dobles
        {
            i++;
            inicial = i;
            while (line[i] && line[i] != 39)
            {
                if (line[i] == 34) // comillas simples
                    if(!simples(line + i, temp));
                        return(0);
                i++;
            }
            if (line[i] == 39)
            {
                final = i - 1;
                counter++;
                temp->arg = ft_strdup(ft_substr(line, i, final - inicial));
            }
        }
    }
    if (counter%2 == 0)
        return(1);
    else 
        return (0);
}
int dobles(char *line, t_com *temp)
{
    int i = 0;
    int inicial = 0;
    int final = 0;
    int counter = 0;

    while (line[i])
    {
        if (line[i] == 34) // comillas dobles
        {
            i++;
            inicial = i;
            while (line[i] && line[i] != 34)
            {
                if (line[i] == 39) // comillas simples
                    if(!simples(line + i, temp))
                        return(0);
                i++;
            }
            if (line[i] == 34)
            {
                final = i - 1;
                counter++;
                temp->arg = ft_strdup(ft_substr(line, i, final - inicial));
            }
        }
    }
    if (counter%2 == 0)
        return(1);
    else 
        return (0);
}

void quotes(char *line, t_com *temp)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == 39)
            if (!simples(line, temp))
                return(0);
        if (line[i] == 34)
            if (!dobles(line, temp));
                return(0);
    }
}