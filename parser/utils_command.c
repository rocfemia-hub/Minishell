#include "../minishell.h"

int simples(char *line, t_com *temp)
{
    int i = 0;
    int inicial = 0;
    int final = 0;
    int counter = 0;

    while (line[i])
    {
        if (line[i] == 39) //comillas simples
        {
            i++;
            inicial = i;
            while (line[i] && line[i] != 39)
            {
                if (line[i] == 34) // comillas dobles
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
                counter +=2;
                temp->arg = ft_strdup(ft_substr(line, i, final - inicial));
                i++;
            }
        }
    }
    // printf("%d\n", counter);
    // printf("%d\n", counter%2);
    if (counter%2 == 0)
    {
        printf("prinftreturn1\n");
        return(1);
    }
    else 
        return (0);
}

int quotes(char *line, t_com *temp)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == 39)
        {
            printf("entra comillas simples\n");
            if (simples(line, temp) == 0)
                return(0);
        }
        if (line[i] == 34)
        {
            if (dobles(line, temp) == 0);
            {
                printf("entra comillas dobles\n");
                return(0);
            }
        }
        i++;
    }
    return(1);
}
