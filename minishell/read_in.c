#include "mini.h"

int save_command_block(t_cmd *cmds, int i, int k, char **args)
{
	int x;
	int z;

	x = cmds[0].counter++;
	cmds[x].cmd = ft_strdup(args[k]);
	if (i == k)
	{
		cmds[x].argc = 0;
		return (0);
	}
	z = 0;
	while (++k < i)
		cmds[x].args[z++] = ft_strdup(args[k]);
	cmds[x].argc = z;
	return (1);
}

void parse_to_cmd(t_mini *mini, char **args)
{
	t_cmd	*cmds;
	int		i;
	int		j;

	cmds = ft_calloc(64, sizeof(t_cmd));
	cmds[0].counter = 0;
	i = -1;
	j = 0;
	while (args[++i])
	{
		if (!ft_strcmp(args[i],"|") || !ft_strcmp(args[i],"<") || !ft_strcmp(args[i],">")
			|| !ft_strcmp(args[i],">>") || !ft_strcmp(args[i],"<<"))
		{
			i -= save_command_block(cmds, i, i - j, args);
			j = -1;
		}
		j++;
	}
	save_command_block(cmds, i, i - j, args);
	mini->cmd_count = cmds[0].counter;
	free(args);
	mini->cmds = cmds;
}

void	check_special_chars(char *input, char *parsed_input, int *i, int *j)
{
	if (input[*i] == '|')
	{
		parsed_input[*i + *j] = ' ';
		parsed_input[*i + *j + 1] = '|';
		*j += 2;
		parsed_input[*i + *j] = ' ';
	}
	if (input[*i] == '<' || input[*i] == '>')
	{
		parsed_input[*i + *j] = ' ';
		(*j)++;
		parsed_input[*i + *j] = input[*i];
		if (input[*i + 1] == '<' || input[*i + 1] == '>')
		{
			(*i)++;
			parsed_input[*i + *j] = input[*i];
		}
		(*j)++;
		parsed_input[*i + *j] = ' ';
	}
}

int	input_len(char *input)
{
	int	len;
	int	i;

	len = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '|')
			len += 2;
		if (input[i] == '<' || input[i] == '>')
		{
			if (input[i + 1] == '<' || input[i + 1] == '>')
			{
				i++;
				len++;
			}
			len += 2;
		}
		len++;
	}
	return (len);
}

char	**tokenize_input(char *input)
{
	char	**args;
	char	*parsed_input;
	int		i;
	int		j;

	i = -1;
	j = 0;
	parsed_input = malloc (input_len(input) + 1);
	while (input[++i])
	{
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			check_special_chars(input, parsed_input, &i, &j);
			continue ;
		}
		parsed_input[i + j] = input[i];
	}
	parsed_input[i + j] = 0;
	args = ft_split(parsed_input, ' ');
	free (parsed_input);
	return (args);
}


void free_cmd(t_cmd *cmds)
{
	int i;
	int j;

	i = -1;
	while (++i <= cmds[0].counter)
	{
		if (cmds[i].cmd)
			free(cmds[i].cmd);
		j = -1;
		while (++j < cmds[i].argc)
			if (cmds[i].args[j])
				free(cmds[i].args[j]);
	}
	free(cmds);
}

int	check_input(char *input, t_mini *mini)
{
	int		ret;

	ret = 1;

	parse_to_cmd(mini, tokenize_input(input));
	execute_builtin(mini);
	// printf("%s",  mini->cmds[0].args[0]);
	ret = execute_command(mini);
	free_cmd(mini->cmds);
	return (ret);
}

int	read_input(t_mini *mini)
{
	char	*input;

	update_path(mini);
	using_history();
	while (1)
	{
		input = readline("\033[32mmini> \033[0m");
		if (!input)
		{
			ft_putstr_fd("exit\n", 1);
			exit(mini->status);
		}
		if (*input)
		{
			add_history(input);
			check_input(input, mini);
		}
		free(input);
	}
	return (0);
}
