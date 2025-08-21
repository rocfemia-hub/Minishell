#include "../minishell.h"

char **copy_matrix(char **args) //copiar matriz con los argumentos cuando hay redirreciones
{
    char **new_arg;
    int i = 0;
    int j = 0;
    int lines_char = 0;
    while (args[j] && args[j][0] != '>')
    {
        lines_char++;
        j++;
    }
    new_arg = ft_calloc(lines_char + 1, sizeof(char *));
    lines_char = 0;
    j = 0;
    while(args[j] && args[j][0] != '>')
    {
        new_arg[i] = ft_strdup(args[j]);
        i++;
        j++;
    }
    return(new_arg);
}
void reorder_arguments(t_com *commands)
{
    commands->redirects->new_arg = copy_matrix(commands->args); // hacer una copia para poder modificar
}

void fill_struct_redirect(t_com *commands)
{
    int i;

    i = 0;
    if (commands->args[commands->redirects->j])
    {
        if ((!commands->args[commands->redirects->j + 1]) || (commands->args[commands->redirects->j][i + 1] && commands->args[commands->redirects->j][i + 1] != '>'))
        {
            commands->redirects->input_file = ft_strdup("error sintax");
            return;
        }
        else
        {
            if (commands->args[commands->redirects->j] && commands->args[commands->redirects->j][i] == '>' && commands->args[commands->redirects->j][i+1] == '>')
            {
                commands->redirects->append_file = ft_strdup(commands->args[commands->redirects->j + 1]);
                commands->redirects->redirect_append = 1; 
                return;                
            }
            else
            {
                commands->redirects->input_file = ft_strdup(commands->args[commands->redirects->j + 1]);
                commands->redirects->redirect_out = 1; 
                return;
            }
        }
    }
}

void look_for_redirects(t_com *commands)
{
    while(commands->args[commands->redirects->j])
    {
        commands->redirects->i = 0;
        while(commands->args[commands->redirects->j][commands->redirects->i])
        {
            while(commands->args[commands->redirects->j][commands->redirects->i] == 32)
                commands->redirects->i++;
            if((commands->args[commands->redirects->j][commands->redirects->i]) == '>')
                fill_struct_redirect(commands);
            commands->redirects->i++;
        }
        commands->redirects->j++;
    }

}

void redirects(t_com *commands)
{
    commands->redirects = ft_calloc(1, sizeof(t_red));
    look_for_redirects(commands);
    if (commands->redirects->redirect_append || commands->redirects->redirect_out)
        reorder_arguments(commands); 
}
