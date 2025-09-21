#include "../minishell.h"

char **realloc_redirect_flags(char **flag)
{ // extender los char ** en caso de haber mas de 1 redireccion
    int i;
    int j;
    char **realloc_matrix;

    i = 0;
    j = 0;
    while (flag[j])
        j++;
    realloc_matrix = ft_calloc(j + 2, sizeof(char *));
    if (!realloc_matrix)
        return (NULL);
    j = -1;
    while (flag[++j])
        realloc_matrix[j] = ft_strdup(flag[j]);
    return (realloc_matrix);
}

char **copy_redirect_matrix(char **args, int start, int end)
{ // copiar matriz de args sin el simbolo de redireccion y el nombre del archivo
    int i;
    int j;
    char **new_arg;

    i = 0;
    j = 0;
    while (args[j])
        j++;
    new_arg = ft_calloc(j + 1, sizeof(char *));
    if (!new_arg)
        return (NULL);
    j = 0;
    while (args[j])
    {
        if (j < start || j > end)
        {
            new_arg[i] = ft_strdup(args[j]);
            i++;
        }
        j++;
    }
    ft_free_free(args);
    return (new_arg);
}

void handle_redirect_array(char ***arr, int *count, char *file)
{
    if (!*arr)
        *arr = ft_calloc(2, sizeof(char *));
    else
        *arr = realloc_redirect_flags(*arr);
    (*arr)[*count] = ft_strdup(file);
    (*count)++;
}

void fill(t_com *commands, int start, int end, char *redirect)
{
    commands->args = copy_redirect_matrix(commands->args, start, end);
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
