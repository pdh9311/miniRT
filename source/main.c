#include "miniRT.h"
#include "libft.h"
#include "list.h"
// #include "test.h"

int main(int argc, char *argv[])
{
	t_lst	*lst;

	lst = NULL;
	if (argc != 2)
		return (EXIT_FAILURE);
    readfile(argv[1], &lst);
	// print_lst(lst);	
	return (EXIT_SUCCESS);
}