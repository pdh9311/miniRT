#include "miniRT.h"
#include "libft.h"
#include "element.h"

int main(int argc, char *argv[])
{

	if (argc != 2)
		return (EXIT_FAILURE);
    readfile(argv[1]);
	return (EXIT_SUCCESS);
}