#include <assert.h>
#include <test.h>

int
sub(int a, int b)
{
	return a - b;
}

static void 
test_sub(void) 
{
	assert(sub(10, 20) == -10);
	assert(sub(20, 40) ==  20); // wrong on purpose
	assert(sub(50, -20) == 70);
}

define_test(test_sub);
