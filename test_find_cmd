// for builtin commands: set cmd->is_builtin to 1
// for non-builtin commands: 1. set cmd->is_builtin to 0; 2. find path

#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

// pwd
// pwd | cat < in.txt | grep hello | wc > out.txt

// t_cmd *make_test_cmds(void)
// {
// 	t_cmd *cmd1 = malloc(sizeof(t_cmd));

// 	cmd1->path = NULL;
// 	cmd1->args = malloc(sizeof(char *) * 2);
// 	cmd1->args[0] = strdup("cat");
// 	cmd1->args[1] = NULL;
// 	cmd1->input_fd = open("in.txt", O_WRONLY);
// 	cmd1->output_fd = -1;
// 	cmd1->is_builtin = 0;
// 	cmd1->next = NULL;

// 	return cmd1;
// }

t_cmd *make_test_cmds(void)
{
	t_cmd *cmd1 = malloc(sizeof(t_cmd));
	t_cmd *cmd2 = malloc(sizeof(t_cmd));
	t_cmd *cmd3 = malloc(sizeof(t_cmd));
	t_cmd *cmd4 = malloc(sizeof(t_cmd));

	// ------- pwd -------
	cmd1->path = NULL;
	cmd1->args = malloc(sizeof(char *) * 2);
	cmd1->args[0] = strdup("pwd");
	cmd1->args[1] = NULL;
	cmd1->input_fd = -1;
	cmd1->output_fd = -1;
	cmd1->is_builtin = -1;
	cmd1->next = cmd2;

	// ------- cmd2: cat < in.txt -------
	cmd2->path = NULL;
	cmd2->args = malloc(sizeof(char *) * 2);
	cmd2->args[0] = strdup("cat");
	cmd2->args[1] = NULL;
	cmd2->input_fd = open("in.txt", O_WRONLY);
	cmd2->output_fd = -1;
	cmd2->is_builtin = -1;
	cmd2->next = cmd3;

	// ------- cmd3: grep hello  -------
	cmd3->path = NULL;
	cmd3->args = malloc(sizeof(char *) * 3);
	cmd3->args[0] = strdup("bin/ls");
	cmd3->args[1] = strdup("hello");
	cmd3->input_fd = -1;
	cmd3->output_fd = -1;
	cmd3->is_builtin = -1;
	cmd3->next = cmd4;

	// ------- cmd4: wc > out.txt -------
	cmd4->path = NULL;
	cmd4->args = malloc(sizeof(char *) * 2);
	cmd4->args[0] = strdup("wc");
	cmd4->args[1] = NULL;
	cmd4->input_fd = -1;
	cmd4->output_fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	cmd4->is_builtin = -1;
	cmd4->next = NULL;

	return cmd1;
}

void	print_structs(t_cmd *cmd)
{
	int i = 1;
	while (cmd)
	{
		printf("**struct No.%d**\n", i);
		int j = 0;
		while (cmd->args[j])
		{
			printf("args[%d]: %s\n", j, cmd->args[j]);
			j++;
		}
		printf("path: %s\n", cmd->path);
		printf("is_buitlin: %d\n\n", cmd->is_builtin);
		cmd = cmd->next;
		i++;
	}
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_cmd *cmd_list = make_test_cmds();
	t_cmd *tmp = cmd_list;
	while (tmp)
	{
		find_path(tmp, envp);
		tmp = tmp->next;
	}
	print_structs(cmd_list);
	return 0;
}
