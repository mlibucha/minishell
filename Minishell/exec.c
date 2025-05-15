#include "mini.h"

void update_path(t_mini *mini)
{
    char *pwd = getcwd(NULL, 0);
    
    if (pwd == NULL)
    {
        ft_putstr_fd("mini: error: cannot get current directory: ", STDERR_FILENO);
        ft_putendl_fd(strerror(-1), STDERR_FILENO);
        mini->status = 1;
        return;
    }
    free(mini->path);
    mini->path = pwd;
    mini->status = 0;
}

static void setup_redirections(t_cmd *cmd)
{
    int fd;
    
    if (cmd->input != NULL)
    {
        fd = open(cmd->input, O_RDONLY);
        if (fd < 0)
        {
            perror("mini: open input");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
    
    if (cmd->output != NULL)
    {
        int flags = O_WRONLY | O_CREAT;
        if (cmd->append)
        {
            flags = flags | O_APPEND;
        }
        else
        {
            flags = flags | O_TRUNC;
        }
        fd = open(cmd->output, flags, 0644);
        if (fd < 0)
        {
            perror("mini: open output");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
}

static void exec_command(t_cmd *cmd, t_mini *mini)
{
    char *path = find_executable(cmd->args[0]);
    
    if (path == NULL)
    {
        ft_putstr_fd("mini: command not found: ", 2);
        ft_putendl_fd(cmd->args[0], 2);
        exit(127);
    }
    
    setup_redirections(cmd);
    execve(path, cmd->args, mini->envp);
    perror("mini");
    free(path);
    exit(EXIT_FAILURE);
}

int execute_pipeline(t_cmd *cmds, int cmd_count, t_mini *mini)
{
    int prev_pipe = -1;
    int pipefd[2];
    pid_t pid;
    int status;
    int i = 0;

    while (i < cmd_count)
    {
        if (i < cmd_count - 1)
        {
            if (pipe(pipefd) != 0)
            {
                perror("mini: pipe");
                return 1;
            }
        }
        
        pid = fork();
        if (pid == 0)
        {
            if (i > 0)
            {
                dup2(prev_pipe, STDIN_FILENO);
                close(prev_pipe);
            }
            if (i < cmd_count - 1)
            {
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }
            exec_command(&cmds[i], mini);
        }
        else if (pid < 0)
        {
            perror("mini: fork");
            return 1;
        }
        
        if (i > 0)
        {
            close(prev_pipe);
        }
        if (i < cmd_count - 1)
        {
            close(pipefd[1]);
            prev_pipe = pipefd[0];
        }
        i++;
    }
    
    i = 0;
    while (i < cmd_count)
    {
        waitpid(-1, &status, 0);
        i++;
    }
    
    if (WIFEXITED(status))
    {
        return WEXITSTATUS(status);
    }
    return 1;
}

char *find_executable(char *cmd)
{
    char *path;
    char *path_copy;
    char *dir;
    char *full_path;
    size_t len;

    if (ft_strchr(cmd, '/'))
    {
        if (access(cmd, X_OK) == 0)
            return ft_strdup(cmd);
        return NULL;
    }

    path = getenv("PATH");
    if (path == NULL)
        return NULL;

    path_copy = ft_strdup(path);
    dir = ft_strtok(path_copy, ":");
    
    while (dir != NULL)
    {
        len = ft_strlen(dir) + ft_strlen(cmd) + 2;
        full_path = malloc(len);
        if (full_path == NULL)
            break;
        
        ft_strlcpy(full_path, dir, len);
        ft_strlcat(full_path, "/", len);
        ft_strlcat(full_path, cmd, len);
        
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return full_path;
        }
        free(full_path);
        dir = ft_strtok(NULL, ":");
    }
    free(path_copy);
    return NULL;
}