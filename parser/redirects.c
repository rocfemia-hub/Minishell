#include "../minishell.h"

void fill_struct_redirect(t_com *commands, int j)
{
    int i = 0;

    if (commands->args[j])
    {
        if ((!commands->args[j + 1]) || (commands->args[j][i + 1] && commands->args[j][i + 1] != '>'))
        {
            commands->redirects->input_file = ft_strdup("error sintax");
            // printf("error: %s\n", commands->redirects->input_file);
            return;
        }
        else
        {
            if (commands->args[j] && commands->args[j][i] == '>' && commands->args[j][i+1] == '>')
            {
                commands->redirects->append_file = ft_strdup(commands->args[j + 1]);
                commands->redirects->redirect_append = 1; 
                // printf("append_file: %s\n", commands->redirects->append_file);
                // printf("redirect_append: %d\n", commands->redirects->redirect_append);
                return;                
            }
            else
            {
                commands->redirects->input_file = ft_strdup(commands->args[j + 1]);
                commands->redirects->redirect_out = 1; 
                // printf("input_file: %s\n", commands->redirects->input_file);
                // printf("redirect_out: %d\n", commands->redirects->redirect_out);
                return;
            }
        }
    }
}

void look_for_redirects(t_com *commands)
{
    int i;
    int j;
    t_red redirects;

    ft_bzero(&redirects, sizeof(t_red));
    commands->redirects = &redirects;
    j = 0;
    while(commands->args[j])
    {
        i = 0;
        while(commands->args[j][i])
        {
            while(commands->args[j][i] == 32)
                i++;
            if((commands->args[j][i]) == '>')
                fill_struct_redirect(commands, j);
            i++;
        }
        j++;
    }
}

void redirects(t_com *commands)
{
    look_for_redirects(commands);
}