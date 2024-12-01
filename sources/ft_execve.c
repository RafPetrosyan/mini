#include "minishell.h"

int	ft_execve(t_minishell *minishell, char **env, t_tokens **tokens)
{
	int	status;
	int	id;
	char	**paths;

	paths = ft_split(find_to_env_export("PATH", minishell->env_list, &id)->value, ':');
	if (paths == 0)
		return (1);
	id = fork();
	if (id > 0)
		waitpid(-1, &status, 0);
	else if (id == 0)
	{
		if (find_to_env_export("PATH", minishell->env_list, &id) != 0)
		{
			int	i;
			i = 0;
			while (paths[i] != 0)
			{
				paths[i] = ft_strjoin(paths[i], minishell->tokens[0]);
				if (access(paths[i], 0) == 0 && access(paths[i], 1) == 0)
					execve(paths[i], minishell->tokens, env);
				++i;
			}
		}
		else
		{
			printf("bash: %s: No such file or directory\n", minishell->tokens[0]);
			exit(127);
		}
		if (execve(minishell->tokens[0], minishell->tokens, env) == -1)
			printf("%s: command not found\n", tokens[0]->str);
		exit(127);
	}
	free_string_arr(paths);
}