#include "../minishell.h"

void redirects_cmd(t_com *commands)
{
    if (is_redirect_token(commands->command, "<") || is_redirect_token(commands->command, ">"))
    {
        if (commands->args[0])
            return ;
        if (ft_strlen(commands->command) > 1)
            return;
        commands->error = ft_strdup("bash: syntax error near unexpected token `newline'");
    }
    if (is_redirect_token(commands->command, "<<") || is_redirect_token(commands->command, ">>"))
    {
        if (commands->args[0])
            return ;
        if (ft_strlen(commands->command) > 2)
            return;
        commands->error = ft_strdup("bash: syntax error near unexpected token `newline'");
    }
}

// < - salto de linea
// < < - falta el tocken <
// < hola - no da error
// <hola - no da error
// <<hola - abre el heardock