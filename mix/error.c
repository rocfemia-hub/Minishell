#include "../minishell.h"

int ft_error() //funcion para gestion de error, no esta hecha
{
  
}

void printf_matrix(char **split) // debugueo de la matrix, escribiendola
{
    int i = 0;

    while (split[i])
    {
        printf("%s\n", split[i]);
        i++;
    }
}
