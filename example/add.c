#include <assert.h>
#include <test.h>

int
add(int a, int b)
{
	return a + b;
}

static void 
test_add(void) 
{
	assert(add(10, 20) == 30);
	assert(add(20, 40) == 60);
	assert(add(50, -20) == 30);
}

define_test(test_add);
