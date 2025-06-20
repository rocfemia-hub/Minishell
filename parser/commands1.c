#include "../minishell.h"

void echo_com(t_com *temp, char *line) //gestiona el echo para meter cada cosa en la estructura
{
    int i = 0;

    while (line[i] == 32)
        i++;
    if (line[i] && line[i] == 'e' && line[i + 1] == 'c' && line[i + 2] == 'h' && line[i + 3] == 'o' && line[i + 4] == ' ')
        temp->command = "echo";
    i += 4;

}

void pwd_com(t_com *temp, char *line) //gestiona el pwd para meter cada cosa en la estructura
{
    
}

void cd_com(t_com *temp, char *line) //gestiona el cd para meter cada cosa en la estructura
{
    
}

void export_com(t_com *temp, char *line) //gestiona el export para meter cada cosa en la estructura
{
    
}

void unset_com(t_com *temp, char *line) //gestiona el unset para meter cada cosa en la estructura
{
    
}