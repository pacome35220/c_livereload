#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include "flags.h"

void print_compile_log(char **compile_command)
{
	printf("Change file are detected !\n");
	printf("Recompiling with : `");
	for (int i = 0; compile_command[i] != NULL; i++) {
		if (compile_command[i + 1] != NULL)
			printf("%s ", compile_command[i]);
		else
			printf("%s", compile_command[i]);
	}
	printf("`\n");
}

int compile(char **compile_command)
{
	pid_t pid;
	int status;

	print_compile_log(compile_command);
	pid = fork();
	if (pid == -1)
		return 1;
	else if (pid == 0)
		execvp(compile_command[0], compile_command);
	else
		wait(&status);
	return status;
}