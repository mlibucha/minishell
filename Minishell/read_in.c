#include "mini.h"

static int	parse_to_cmd(t_mini *mini, char **args)
{
	t_cmd	*cmd;
	int		i;


	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (1);
	ft_memset(cmd, 0, sizeof(t_cmd));
	i = 0;
	while (args[i] && i < MAX_ARGS - 1)
	{
		cmd->args[i] = args[i];
		i++;
	}
	cmd->argc = i;
	cmd->args[i] = NULL;
	mini->cmds = cmd;
	return (execute_builtin(mini, cmd));
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
	printf("%d\n",input_len(input));
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


int check_input(char *input, t_mini *mini)
{
	char	**args;
	int		ret;

	args = tokenize_input(input);
	if (!args)
		return (1);
	ret = parse_to_cmd(mini, args);
	if (ret == 0 || ret == 1)
	{
		ft_free(args);
		return (ret);
	}
	ret = execute_command(args, mini);
	ft_free(args);
	free(mini->cmds);
	mini->cmds = NULL;
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
		if (*input)
		{
			add_history(input);
			check_input(input, mini);
		}
		free(input);
	}
	return (0);
}
