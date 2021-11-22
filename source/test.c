#include <stdio.h>

void	print_str_arr(char **str_arr)
{	
	int	i;

	i = 0;
	while (str_arr[i])
	{
		printf("%s\t", str_arr[i]);
		i++;
	}
	printf("\n");
}