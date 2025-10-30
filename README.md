# C Userspace Sections Experiment

This repository is an experimental playground to explore an idea from low-level
C, combining linker sections with macros to implement a form of metaprogramming
- a concept traditionally found in higher-level languages.

## Motivation

C gives you powerful low-level constructs, but traditionally it lacks runtime
reflection and metaprogramming (Rust's attributes, Java annotations, Python
decorators).

By using custom sections (`__attribute__((section("...")))`), we can achieve a
form of static metaprogramming that is resolved entirely at compile/link time.

This pattern is commonly used in low-level systems programming:

* Linux kernel `__initcall` arrays
* Device driver registration
* Firmware table initialization (UEFI, IDTs, IRQs)

Here, we experiment with it in user-space C.

## Experiment Description

The experiment is a small test framework.

A structure is defined to represent the unit of data that is going to be
contained in a section (in this case, `testcases` section).

```
typedef struct {
    const char *name;
    void (*fn)(void);
} __TestData;
```

To define a test, one should declare a public symbol in a source file, and
place this symbol in the desired section.

```
__TestData __tdata_test_add __attribute__((section("testcases"))) = { .name = "add_fn", .fn = test_add };
```

To make it more readable, we can wrap this in a macro.

```
#define define_test(test_fn) \
	__TestData __tdata_##test_fn __attribute__((section("testcases"))) = { .name = #test_fn, .fn = test_fn }

...

define_test(test_add);
```

Unfortunately, to use the data contained in the section we need to rely on
compiler-dependent features. For each custom section present, GCC provides
a `__start_SECTION` and `__stop_SECTION` symbols to link with our program.

```
extern __TestData __start_testcases;
extern __TestData __stop_testcases;
```

And after that, we can use the linked symbols.

```
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
```

# Caveats

* Order is not guaranteed, and items in sections may appear in any order
* This relies on compiler/linker support (`__attribute__((section))`) and may
  not work with all toolchains.
* Code may appear “magical” if the pattern is not clearly documented.

# Possible use-cases

* Unit tests: Functions automatically registered in a `testcases` section.
* HTTP handlers: Routes registered in `http.handlers` and iterated at startup.
* Printf extensions: Format specifiers registered in a custom `printformats` section.

