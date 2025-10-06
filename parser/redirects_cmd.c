#include "../minishell.h"
void fill_cmd(t_com *commands, char *redirect)
{

}
int clean_redirects_cmd(t_com *commands, char *redirect)
{
    if (ft_strnstr(commands->command, ">>>", 3)) // error >>>
    {
        commands->error = ft_strdup("bash: syntax error near unexpected token `>'");
        return (0);
    }
    else if (commands->command[0] != redirect[0] || ft_strnstr(commands->command, "<<<", 3)) // error hola< y <<<
    {
        commands->error = ft_strdup("bash: syntax error near unexpected token `newline'");
        return (0);
    }
    else if (ft_strlen(commands->command) > ft_strlen(redirect)) // si la redireccion esta asi ">adios" --> no es error
    {
        commands->redirects->file = ft_strdup(commands->command + ft_strlen(redirect)); // archivo al que redirecciona
        fill_cmd(commands, redirect);                            // rellena estructura
    }
    // else // el archivo esta separado del simbolo "hola > adios"
    //     if (!aux_parser_redirects(commands, redirect))
    //         return (0);
    return (1);
}

void redirects_cmd(t_com *commands)
{
    if (is_redirect_token(commands->command, "<<") || is_redirect_token(commands->command, ">>"))
    {
        printf("entra << o >> \n");
        if (commands->args[0] || ft_strlen(commands->command) > 2)
        {
            if (is_redirect_token(commands->command, "<<"))
                clean_redirects_cmd(commands, "<<");
            if (is_redirect_token(commands->command, ">>"))
                clean_redirects_cmd(commands, ">>");
            return;
        }
        else
            commands->error = ft_strdup("bash: syntax error near unexpected token `newline'");
    }
    if (is_redirect_token(commands->command, "<") || is_redirect_token(commands->command, ">"))
    {
        printf("entra < o > \n");
        if (commands->args[0] || ft_strlen(commands->command) > 1)
        {
            if (is_redirect_token(commands->command, "<"))
                clean_redirects_cmd(commands, "<");
            if (is_redirect_token(commands->command, ">"))
                clean_redirects_cmd(commands, ">");
            return;
        }
        else
            commands->error = ft_strdup("bash: syntax error near unexpected token `newline'");
    }
}

// < - salto de linea
// < < - falta el tocken <
// < hola - no da error
// <hola - no da error
// <<hola - abre el heardock