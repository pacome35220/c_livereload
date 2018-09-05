#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include "flags.h"
#include "livereload.h"

static void destroy_flags(struct flag_option *flags)
{
	free(flags->source_path);
	free(flags->binary_name);
	free(flags->compile_command);
}

int main(int argc, char **argv)
{
	destructor(destroy_flags) struct flag_option flags = {
		.source_path = NULL,
		.binary_name = NULL,
		.compile_command = NULL
	};
	int inotify_fd;

	if (parse_options(argc, argv, &flags) == -1)
		return usage(argv);
	inotify_fd = inotify_init();
	assert(inotify_fd != -1);
	for (size_t i = 0; flags.source_path[i] != NULL; i++)
		add_watched_file(inotify_fd, flags.source_path[i]);
	run_livereload(inotify_fd, &flags);
	return EXIT_SUCCESS;
}
