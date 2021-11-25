#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void plotLine(int x0, int y0, int x1, int y1)
{
	int dx =  abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;

	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;

	printf("dx: %d, dy: %d\n", dx, dy);
	printf("sx: %d, sy: %d\n", sx, sy);

	/* error value e_xy */
	int err = dx + dy;
	int e2;
	printf("err: %d\n", err);
	while (1)	/* loop */
	{
		// setPixel(x0,y0);
		e2 = 2 * err;
		printf("(%d, %d)\terr:%d\te2: %d\tdy: %d\tdx: %d\n", x0, y0, err, e2, dy, dx);
		if (e2 >= dy)	// e_xy + e_x > 0
		{
			if (x0 == x1)
				break ;
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)	// e_xy + e_y < 0
		{
			if (y0 == y1)
				break ;
			err += dx;
			y0 += sy;
		}
	}
}

int	main(void)
{
	printf("------------------------\n");
	plotLine(0, 0, 4, -5);
	printf("------------------------\n");
	plotLine(1, 1, 6, 5);
	printf("------------------------\n");
	plotLine(-1, -1, 5, -6);
	printf("------------------------\n");
	plotLine(1, 1, -6, -15);
	printf("------------------------\n");
	return (0);
}
