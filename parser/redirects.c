#include "../minishell.h"

void redirects(t_com *commands)
{
    printf("print arg\n");
    printf_matrix(commands->args);
}