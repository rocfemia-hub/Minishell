#include "../minishell.h"

int aux_quotes(char *line, t_com *temp)
{
    int i = 0;
    int flag_simple = 0; // 0-cerrada    1-abierta
    int flag_doble = 0; // 0-cerrada    1-abierta

    while (line[i])
    {
        if (line[i] == 34) //dobles
            flag_simple = !flag_simple;
        if (line[i] == 39) //simples
            flag_doble = !flag_doble;
        i++;
    }
    if(flag_doble == 1 || flag_simple == 1)
    {
        if(flag_doble == 1 && flag_simple == 0 || flag_doble == 0 && flag_simple == 1)
            return(1);
        return(0);
    }
    return(1);
}

int quotes(char *line, t_com *temp)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == 34 || line[i] == 39) //comillas dobles-34 y comillas simples-39
            if (doble_quotes(line, temp) == 0)
            {
                printf("entra en doble_quotes\n");
                temp->command = ft_strdup("error");
                return(0);
            }
        i++;
    }
    return(1);
}
