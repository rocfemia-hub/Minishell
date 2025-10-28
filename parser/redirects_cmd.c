#include "../minishell.h"

char **realloc_redirect_args(char **flag)
{ // acortar los char **
    int i;
    int j;
    char **realloc_matrix;

    j = 0;
    while (flag[j])
        j++;
    realloc_matrix = ft_calloc(j, sizeof(char *));
    if (!realloc_matrix)
        return (NULL);
    i = 0;
    j = 0;
    while (flag[++i])
    {
        realloc_matrix[j] = ft_strdup(flag[i]);
        j++;
    }
    ft_free_free(flag);
    return (realloc_matrix);
}

void look_for_cmd(t_com *commands)
{
    char **temp;
    int i;

    i = 0;
    if (!commands || !commands->args)
        return;
    while (commands->args[i])
    {
        if(is_redirect_token(commands->args[i], "<<") || is_redirect_token(commands->args[i], ">>") || is_redirect_token(commands->args[i], "<") || is_redirect_token(commands->args[i], ">"))
            find(commands);
        i++;
    }
    if (ft_strlen(commands->command) < 1 || ft_strlen(commands->args[i]))
    {
        commands->command = ft_strdup(commands->args[i]);
        temp = realloc_redirect_args(commands->args);
        commands->args = temp;
    }
}

void fill_cmd(t_com *commands, char *redirect)
{
    if (ft_strncmp(redirect, "<", 2) == 0)
        handle_redirect_array(&commands->redirects->input_file, &commands->redirects->redirect_in, commands->redirects->file);
    else if (ft_strncmp(redirect, ">", 2) == 0)
        handle_redirect_array(&commands->redirects->output_file, &commands->redirects->redirect_out, commands->redirects->file);
    else if (ft_strncmp(redirect, ">>", 3) == 0)
        handle_redirect_array(&commands->redirects->append_file, &commands->redirects->redirect_append, commands->redirects->file);
    else if (ft_strncmp(redirect, "<<", 3) == 0)
    {
        commands->redirects->delimiter = ft_strdup(commands->redirects->file);
        commands->redirects->redirect_heredoc = 1;
    }
    free(commands->redirects->file);
}

int clean_redirects_cmd(t_com *commands, char *redirect, int type)
{
    if (ft_strnstr(commands->command, ">>>", 3)) // error >>>
    {
        commands->error = ft_strdup("bash: syntax error near unexpected token `>'");
        commands->vars->exit_status = 2;
        return (0);
    }
    else if (commands->command[0] != redirect[0] || ft_strnstr(commands->command, "<<<", 3)) // error hola< y <<<
    {
        commands->error = ft_strdup("bash: syntax error near unexpected token `newline'");
        commands->vars->exit_status = 2;
        return (0);
    }
    else if (ft_strlen(commands->command) > ft_strlen(redirect)) // si la redireccion esta asi ">adios" --> no es error
    {
        commands->redirects->file = ft_strdup(commands->command + ft_strlen(redirect)); // archivo al que redirecciona
        fill_cmd(commands, redirect);                                                   // rellena estructura
        fill_type_redirect(commands, type);
        free(commands->command);
        commands->command = ft_strdup("");
    }
    else if (commands->args[0])
    {
        commands->redirects->file = ft_strdup(commands->args[0]);
        fill_cmd(commands, redirect);
        free(commands->command);
        commands->command = ft_strdup("");
        commands->args = realloc_redirect_args(commands->args);
        fill_type_redirect(commands, type);
    }
    return (1);
}

int redirects_cmd(t_com *commands)
{
    if (is_redirect_token(commands->command, "<<") || is_redirect_token(commands->command, ">>"))
    {
        if (commands->args[0] || ft_strlen(commands->command) > 2)
        {
            if (is_redirect_token(commands->command, "<<"))
                if (!clean_redirects_cmd(commands, "<<", 4))
                    return (0);
            if (is_redirect_token(commands->command, ">>"))
                if (!clean_redirects_cmd(commands, ">>", 3))
                    return (0);
            look_for_cmd(commands);
            return (1);
        }
        else
        {
            commands->error = ft_strdup("bash: syntax error near unexpected token `newline'");
            commands->vars->exit_status = 2;
            return (0);
        }
    }
    if (is_redirect_token(commands->command, "<") || is_redirect_token(commands->command, ">"))
    {
        if (commands->args[0] || ft_strlen(commands->command) > 1)
        {
            if (is_redirect_token(commands->command, "<"))
                clean_redirects_cmd(commands, "<", 1);
            if (is_redirect_token(commands->command, ">"))
                clean_redirects_cmd(commands, ">", 2);
            look_for_cmd(commands);
            return (1);
        }
        else
        {
            commands->error = ft_strdup("bash: syntax error near unexpected token `newline'");
            commands->vars->exit_status = 2;
            return (0);
        }
    }
}
