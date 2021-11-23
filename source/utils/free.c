#include <stdlib.h>

int	free_ptr(char *ptr, int ret)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
	return (ret);
}

int	free_dptr(char **dptr, int ret)
{
	int	i;

	i = 0;
	while (dptr[i] != NULL)
	{
		free(dptr[i]);
		dptr[i] = NULL;
		i++;
	}
	if (dptr != NULL)
	{
		free(dptr);
		dptr = NULL;
	}
	return (ret);
}
