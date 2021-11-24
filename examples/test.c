#include <stdio.h>

int	error(int x, int y)
{
	return ((y - 1) * 5 - (x - 1) * 4);
}

int	main(void)
{

	int	x, y;

	for (y = 10; y >= 0; y--)
	{
		for (x = 0; x <= 10; x++)
		{
			printf("(%3d) ", error(x, y));
		}
		printf("\n");
	}
	return (0);
}
