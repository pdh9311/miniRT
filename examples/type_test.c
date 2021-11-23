#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void	type_a(const char *str)
{
	printf("TYPE_A Function\n");
}

void	type_b(const char *str)
{
	printf("TYPE_B Function\n");
}

void	type_c(const char *str)
{
	printf("TYPE_C Function\n");
}

void	type_d(const char *str)
{
	printf("TYPE_D Function\n");
}

void	type_e(const char *str)
{
	printf("TYPE_E Function\n");
}

int	main(int 	argc, char *argv[])
{
	char *builtin_str[] = {
		"type_a",
		"type_b",
		"type_c",
		"type_d",
		"type_e"
	};

	void (*builtin_func[]) (const char *) = {
		&type_a,
		&type_b,
		&type_c,
		&type_d,
		&type_e
	};

	if (argc == 1)
		return (0);

int i;
	for (i = 0; i < 5; ++i)
		if (strcmp(builtin_str[i], argv[1]) == 0)
			break ;
	if (i < 5)
	{
		builtin_func[i](argv[1]);
	}
}