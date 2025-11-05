#include "../minishell.h"

char **realloc_redirect_args(char **flag)
{
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
		if (is_redirect_token(commands->args[i], "<<") || is_redirect_token(commands->args[i], ">>") || is_redirect_token(commands->args[i], "<") || is_redirect_token(commands->args[i], ">"))
			find(commands);
		i++;
	}
	if (!commands->command || ft_strlen(commands->command) < 1)
	{
		if (commands->args[0])
		{
			if (commands->command)
				free(commands->command);
			commands->command = ft_strdup(commands->args[0]);
			temp = realloc_redirect_args(commands->args);
			commands->args = temp;
		}
	}
}

void fill_cmd(t_com *commands, char *redirect, char *file)
{
	if (ft_strncmp(redirect, "<", 2) == 0)
		handle_redirect_array(&commands->redirects->input_file, &commands->redirects->redirect_in, file);
	else if (ft_strncmp(redirect, ">", 2) == 0)
		handle_redirect_array(&commands->redirects->output_file, &commands->redirects->redirect_out, file);
	else if (ft_strncmp(redirect, ">>", 3) == 0)
		handle_redirect_array(&commands->redirects->append_file, &commands->redirects->redirect_append, file);
	else if (ft_strncmp(redirect, "<<", 3) == 0)
	{
		commands->redirects->delimiter = ft_strdup(file);
		commands->redirects->redirect_heredoc = 1;
	}
	free(file);
}

int clean_redirects_cmd(t_com *commands, char *redirect, int type)
{
	char	*tmp_file;
	char	*tmp_cmd;
	int		i;

	i = 0;
	if (ft_strnstr(commands->command, ">>>", 3)) // error >>>
	{
		commands->error = ft_strdup("bash: syntax error near unexpected token `>'");
		commands->vars->exit_status = 2;
		return (0);
	}
	else if (ft_strnstr(commands->command, "<<<", 3)) // error hola< y <<<
	{
		commands->error = ft_strdup("bash: syntax error near unexpected token `newline'");
		commands->vars->exit_status = 2;
		return (0);
	}
	else if (ft_strlen(commands->command) > ft_strlen(redirect)) // cat>Makefile
	{
		while (commands->command[i] && ft_strncmp(commands->command + i, redirect, ft_strlen(redirect)) != 0)
			i++;
		tmp_file = ft_strdup(commands->command + i + ft_strlen(redirect));
		fill_cmd(commands, redirect, tmp_file);
		fill_type_redirect(commands, type);
		tmp_cmd = commands->command;
		commands->command = ft_substr(tmp_cmd, 0, i);
		free(tmp_cmd);
	}
	else if (commands->args[0])
	{
		tmp_file = ft_strdup(commands->args[0]);
		fill_cmd(commands, redirect, tmp_file);
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
	return (0);
}
