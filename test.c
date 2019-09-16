

#include <stdio.h>

void	call_test()
{
	static int a = 5;
	a++;
	printf ("a is now %i\n", a);
	
}




int	main()
{

	call_test();
	call_test();
	call_test();	
	return (0);
}
