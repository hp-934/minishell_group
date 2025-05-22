#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

// echo -n a | wc

t_cmd *make_first_cmds(void)
{
	t_cmd *cmd1 = malloc(sizeof(t_cmd));
	// t_cmd *cmd2 = malloc(sizeof(t_cmd));
	// t_cmd *cmd3 = malloc(sizeof(t_cmd));

	// ------- cmd1 -------
	cmd1->path = NULL;
	cmd1->args = malloc(sizeof(char *) * 3);
	cmd1->args[0] = strdup("cd");
	cmd1->args[1] = strdup("..");
	cmd1->args[2] = NULL;
	cmd1->input_fd = open("in.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	cmd1->output_fd = -1;
	cmd1->is_builtin = 0;
	cmd1->next = NULL;

	// // ------- cmd2 -------
	// cmd2->path = NULL;
	// cmd2->args = malloc(sizeof(char *) * 2);
	// cmd2->args[0] = strdup("pwd");
	// cmd2->args[1] = NULL;
	// cmd2->input_fd = -1;
	// cmd2->output_fd = -1;
	// cmd2->is_builtin = 0;
	// cmd2->next = NULL;

	// // ------- cmd3: wc > out.txt -------
	// cmd3->path = strdup("/home/hogu/.capt/root/usr/bin/wc");
	// cmd3->args = malloc(sizeof(char *) * 3);
	// cmd3->args[0] = strdup("wc");
	// cmd3->args[1] = strdup("-l");
	// cmd3->args[2] = NULL;
	// cmd3->input_fd = -1;
	// cmd3->output_fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// cmd3->is_builtin = 0;
	// cmd3->next = NULL;

	return cmd1;
}
t_cmd *make_second_cmds(void)
{
	t_cmd *cmd1 = malloc(sizeof(t_cmd));
	// t_cmd *cmd2 = malloc(sizeof(t_cmd));
	// t_cmd *cmd3 = malloc(sizeof(t_cmd));

	// ------- cmd1 -------
	cmd1->path = NULL;
	cmd1->args = malloc(sizeof(char *) * 2);
	cmd1->args[0] = strdup("pwd");
	cmd1->args[1] = NULL;
	cmd1->input_fd = -1;
	cmd1->output_fd = -1;
	cmd1->is_builtin = 0;
	cmd1->next = NULL;

	// // ------- cmd2 -------
	// cmd2->path = NULL;
	// cmd2->args = malloc(sizeof(char *) * 2);
	// cmd2->args[0] = strdup("pwd");
	// cmd2->args[1] = NULL;
	// cmd2->input_fd = -1;
	// cmd2->output_fd = -1;
	// cmd2->is_builtin = 0;
	// cmd2->next = NULL;

	// // ------- cmd3: wc > out.txt -------
	// cmd3->path = strdup("/home/hogu/.capt/root/usr/bin/wc");
	// cmd3->args = malloc(sizeof(char *) * 3);
	// cmd3->args[0] = strdup("wc");
	// cmd3->args[1] = strdup("-l");
	// cmd3->args[2] = NULL;
	// cmd3->input_fd = -1;
	// cmd3->output_fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// cmd3->is_builtin = 0;
	// cmd3->next = NULL;

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
		printf("is_builtin: %d\n", cmd->is_builtin);
		printf("input_fd: %d\n", cmd->input_fd);
		printf("output_fd: %d\n\n", cmd->output_fd);

		cmd = cmd->next;
		i++;
	}
}

// int main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	(void)envp;
// 	t_cmd *cmd_list = make_test_cmds();
// 	t_cmd *tmp = cmd_list;
// 	while (tmp)
// 	{
// 		find_path(tmp, envp);
// 		tmp = tmp->next;
// 	}
// 	print_structs(cmd_list);
// 	execute(cmd_list, envp);
// 	return 0;
// }

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_cmd *cmd_list1 = make_first_cmds();
	t_cmd *tmp = cmd_list1;
	while (tmp)
	{
		find_path(tmp, envp);
		tmp = tmp->next;
	}
	print_structs(cmd_list1);
	execute(cmd_list1, envp);
	t_cmd *cmd_list2 = make_second_cmds();
	tmp = cmd_list2;
	while (tmp)
	{
		find_path(tmp, envp);
		tmp = tmp->next;
	}
	print_structs(cmd_list2);
	execute(cmd_list2, envp);
	return 0;
}