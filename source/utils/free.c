#include <stdlib.h>

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