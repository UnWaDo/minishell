#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROMPT_STRING	">"



// Helps to work with variables
// Need API
typedef struct s_var {
	char	*key;
	char	*value;
	t_var	*next;
}	t_var;

t_var	*create_var(char *key, char *value);
// Returns -1 if var with such var->key already at list,
// otherwise add it to the end and returns 0
int		append_var(t_var *var, t_var **list);
t_var	*delete_var(t_var **list, char *key);
// Return var->value if finds key
// otherwise returns NULL
char	*get_var(t_var *list, char *key);
// Replaces var->value with new_value searching by key.
// If key not found, returns NULL, otherwise var->value = new_value
// and old value is returned (it probably should be freed)
char	*modify_var(t_var *list, char *key, char *new_value);

typedef struct s_shell {
	char	**env;
	int		fd_read;
	t_var	*variables;
}	t_shell;

/*
TODO: signal handling, opening file if arguments contain file, ...
In case of error must clean up and return non-zero value
*/
int	init_shell(t_shell *shell, int argc, char **argv, char **env)
{
	shell->env = env;
	shell->fd_read = 0;
	return (0);
}

// Clean all unfreed memory, close fds, if needed
int clear_shell(t_shell *shell);

// Parses line and returns tokens (trimmed spaces, processed quotes, etc.)
// Tokens: NULL-terminated array of all tokens
char **split_input(char *line);

//	1. Are there any pipes/redirects?
//		Yes: open necessary descriptors, prepare forks
//	2. Divide tokens by pipes/redirects
//	3. Execute tokens
//	4. Save exit code of last pipe to $? variable (key = ?)
// If command was "exit", should return non-zero result 
// for cycle to be stopped
int	execute_command(t_shell *shell, char **tokens)
{
	return (0);
}

// Free all of the allocated memory
void clean_tokens(char **tokens);

// Main logic of Minishell. 
int shell_operate(t_shell *shell)
{
	char	*line;
	char	**tokens;
	int		is_exit;

	line = readline(PROMPT_STRING);
	tokens = split_input(line);
	free(line);
	if (tokens == NULL)
	{
		perror("Something went wrong: ");
		return (-1);
	}
	is_exit = execute_commands(shell, tokens);
	clean_tokens(tokens);
	return (is_exit);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	if (init_shell(&shell, argc, argv, env))
		exit(EXIT_FAILURE);
	while (shell_operate(&shell));
	clear_shell(&shell);
	exit(EXIT_SUCCESS);
}