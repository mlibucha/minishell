#include "mini.h"

int ft_isnumber(char *str)
{
	int a = 0;
	while (str[a])
	{
		if(str[a] < '0' || str[a] > '9')
			return 0;
		a++;
	}
	return 1;
}

int	mini_exit(t_mini *mini)
{
	int	status;

	status = 0;
	if (mini->cmds->argc > 2)
	{
		ft_putendl_fd("mini: exit: too many arguments", 2);
		return (1);
	}
	if (mini->cmds->argc == 2)
	{
		if (!ft_isnumber(mini->cmds->args[1]))
		{
			ft_putstr_fd("mini: exit: ", 2);
			ft_putstr_fd(mini->cmds->args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			status = 2;
		}
		else
			status = ft_atoi(mini->cmds->args[1]);
	}
	free_values(mini);
	exit(status);
}

// pamietaj o aktualizacji pwd
int mini_cd(t_mini *mini)
{
	char *path;

	if (mini->cmds->argc > 2)
	{
		ft_putendl_fd("mini: cd: too many arguments", 2);
		return (1);
	}
	if (mini->cmds->argc == 1)
	{
		path = get_value(&mini->env_list, "HOME");
	}
	else
		path = mini->cmds->args[1];
	if (chdir(path) != 0)
	{
		ft_putstr_fd("mini: cd: ", 2);
		perror(path);
		return (1);
	}
	update_path(mini);
	return (0);
}

int	mini_pwd(t_mini *mini)
{
	(void)mini;
	char *cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("mini: pwd: ", 2);
		perror("");
		return (1);
	}
	
	ft_putendl_fd(cwd, 1);
	free(cwd);
	return (0);
}

int	mini_echo(t_mini *mini)
{
	int	i;
	int	newline;

	(void)mini;
	newline = 1;
	i = 1;
	if (mini->cmds->argc > 1 && ft_strncmp(mini->cmds->args[1], "-n", 2) == 0)
	{
		newline = 0;
		i++;
	}
	while (i < mini->cmds->argc)
	{
		ft_putstr_fd(mini->cmds->args[i], 1);
		if (i < mini->cmds->argc - 1)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}

int	execute_builtin(t_mini *mini)
{
	if (mini->cmds->argc == 0)
		return (-1);
	if (ft_strncmp(mini->cmds->args[0], "exit", 4) == 0)
		return (mini_exit(mini));
	else if (ft_strncmp(mini->cmds->args[0], "cd", 2) == 0)
		return (mini_cd(mini));
	else if (ft_strncmp(mini->cmds->args[0], "pwd", 3) == 0)
		return (mini_pwd(mini));
	else if (ft_strncmp(mini->cmds->args[0], "echo", 4) == 0)
		return (mini_echo(mini));
	// else if (ft_strncmp(mini->cmds->args[0], "unset", 5) == 0 && (mini->cmds->argc == 2));
	// 	del_env(mini->env_list, mini->cmds->args[1]);
	// // else if (ft_strncmp(mini->cmds->args[0], "", 5) == 0 && (mini->cmds->argc == 2));
	// // 	del_env(mini->env_list, mini->cmds->args[1]);
	return (-1);
}
