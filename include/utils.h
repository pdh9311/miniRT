#ifndef UTILS_H
# define UTILS_H

# define C_NC		"\033[0m"
# define C_BLOCK	"\033[30m"
# define C_RED		"\033[31m"
# define C_GREEN	"\033[32m"
# define C_YELLOW	"\033[33m"
# define C_BLUE		"\033[34m"
# define C_PURPLE	"\033[35m"
# define C_AQUA		"\033[36m"

int	free_ptr(char *ptr, int ret);
int	free_dptr(char **dptr, int ret);

#endif
