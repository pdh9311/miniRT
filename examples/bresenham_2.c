#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

int	error_value(int x, int y, int dx, int dy)
{
	int	x0 = 0;
	int y0 = 0;

	return (abs((y - y0) * dx - (x - x0) * dy));
}

void plotLine(int x0, int y0, int x1, int y1)
{
	int dx = abs(x1-x0);
	int sx = x0 < x1 ? 1 : -1;

	int dy = -abs(y1-y0);
	int sy = y0 < y1 ? 1 : -1;

	int	error[3];
	printf("dx: %d, dy: %d\n", dx, dy);

	while (1)	/* loop */
	{
		// setPixel(x0,y0);
		printf("(%d, %d)\t", x0, y0);
		if (x0 == x1 && y0 == y1)
			break ;
		error[0] = error_value(x0 + 1, y0, dx, dy);
		error[1] = error_value(x0, y0 + 1, dx, dy);
		error[2] = error_value(x0 + 1, y0 + 1, dx, dy);

		printf("%3d | %3d |%3d\n", error[0], error[1], error[2]);


		if (error[0] < error[1] && error[0] < error[2])
			x0 += sx;
		else if (error[1] < error[2])
			y0 += sy;
		else
		{
			x0 += sx;
			y0 += sy;
		}
		// sleep(5);
	}
}

int	main(void)
{
	plotLine(0, 0, 4, -5);
	// plotLine(1, 1, 6, 5);
	// plotLine(-1, -1, 5, -6);
	// plotLine(1, 1, -6, -15);
	return (0);
}
