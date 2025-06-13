/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:01:44 by e                 #+#    #+#             */
/*   Updated: 2025/06/13 13:21:34 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
	transform_spaces(args);
	return (args);
}

int check_input(char *input, t_mini *mini)
{
	int ret;

	if (!input || !*input)
		return (0);
	ret = 1;
	mini->cmds = NULL;
	mini->cmd_count = 0;
	input = transform_quotes(input, mini->env_list);
	parse_to_cmd(mini, tokenize_input(input));
	if (!mini->cmds || mini->cmd_count == 0 || !mini->cmds[0] || !mini->cmds[0]->cmd)
	{
		free_all_cmds(mini);
		return (0);
	}
	mini->cmd_left = mini->cmd_count;
	if(mini->cmd_count > 1)
		return(execute_pipeline(mini));
	ret = execute_builtin(mini, mini->cmd_count -1 );
	if(ret != -1)
		mini->cmd_left--;
	if (mini->cmd_left == 0)
	{
		free_all_cmds(mini);
		return (ret);
	}
	ret = execute_command(mini);
	free_all_cmds(mini);
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
