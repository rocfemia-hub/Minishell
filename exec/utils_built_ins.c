#include "../minishell.h"

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

int valid_number(char *str)
{
    int i = 0;
    
    if (!str || !*str)
        return (0);
    while (str[i] == ' ') // Saltar espacios iniciales
        i++;
    if (str[i] == '+' || str[i] == '-') // Permitir signo opcional
        i++;
    if (!str[i]) // Debe haber al menos un dígito después del signo
        return (0);
    while (str[i]) // Verificar que todos los caracteres restantes sean dígitos
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    
    return (1);
}
