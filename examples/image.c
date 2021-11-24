#include "mlx.h"
#include <stdio.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

/**
 * int offset = (y * line_length + x * (bits_per_pixel / 8));	// byte 단위로 계산되는 과정
 */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*((unsigned int *)dst) = color;	// (unsigned int *)가 int값을 넣기위한 형변환 이고, int포인터이기 때문에 int값 차체를 변경해주기위해 *로 접근해서 int값을 color로 변경해주는 과정
}

/** image
 * image를 만들었다면, 우리는 'mlx_get_data_addr'을 불러올 수 있다.
 * 'bits_per_pixel', 'line_length', 'endian'의 주소를 보낸다.
 * 그러고 나서 보내진 주소는 "현재 데이터 주소"를 위해 적절히 set될 것이다.
 */
int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	int		img_width;
	int		img_height;
	t_data	data;

	img_width = 500;
	img_height = 500;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, img_width, img_height, "TEST");
	data.img = mlx_new_image(mlx, img_width, img_height);	// 이미지 instance 생성
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);	// 이미지의 주소 할당
	printf("bits_per_pixel : %d\n", data.bits_per_pixel);	// bits_per_pixel: 32bit	→ 4byte
	printf("line_length: %d\n", data.line_length);			// line_length: 2000byte	→ 4byte * img_width(500)
	printf("my_mlx_pixel_put->offset: %d\n" , 0 * data.line_length + 3 * (data.bits_per_pixel / 8));
	printf("endian: %d\n", data.endian);					// endiian : 0			→ ?
	for (int i = 0; i < 100 ; i++)
	{
		my_mlx_pixel_put(&data, i, i, 0x00FF0000);	// 빨간색 선을 대각선으로 그린다.
		my_mlx_pixel_put(&data, 5, i, 0x0000FF00);	// 초록색 선을 세로로 그린다.
		my_mlx_pixel_put(&data, i, 5, 0x000000FF);	// 파란색 선을 가로로 그린다.
	}
	mlx_put_image_to_window(mlx, mlx_win, data.img, 0, 0);	// 이미지를 윈도우에 올린다.
	mlx_loop(mlx);
	return (0);
}
