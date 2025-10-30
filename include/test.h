#ifndef TEST_H
#define TEST_H

typedef struct
{
	const char *name;
	void (*fn)(void);
} __TestData;

#define define_test(test_fn) \
	__TestData __tdata_##test_fn __attribute__((section("testcases"))) = { .name = #test_fn, .fn = test_fn }

#endif
