#include <test.h>
#include <stdio.h>

extern __TestData __start_testcases[];
extern __TestData __stop_testcases[];

int
main(void)
{
	__TestData *t;
	for(t = __start_testcases; t < __stop_testcases; t++) {
		fprintf(stderr, "Testing %s... ", t->name);
		t->fn();
		fprintf(stderr, "ok...\n");
	}
}

