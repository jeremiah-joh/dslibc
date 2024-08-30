C coding style guide
====================

Basic
-----

* Set `-ansi -Wall -Wextra -Wpedantic -Werror` compiler option.
* Set `-D_XOPEN_SOURCE=700` if it's needed.
* Code must fits in 79 columns.
* Use tab character of 8 spaces width for identation.
* Never use `goto` to go up. And try not to use `goto`.
* Put copyright and license notice at top of every file in project.

Variable
--------

Declare every local variable at top of function.
```c
void
foo()
{
	int a, b;
	char *str;
}
```

Separate declaration and initialization.
```c
void
foo()
{
	int a, b;
	char *str;

	a = 1;
	b = 2;
	str = "Hello, world!";
}
```

Local variable name should be short. 
```c
#include <stdio.h>

void
foo()
{
	int i;

	for (i = 0; i < 10; i++)
		printf("%d\n", i);
}
```

Global variable name should be descriptive.
```c
static int iter_count = 0;

void
foo()
{
	printf("%d\n", iter_count++);
}

void
bar()
{
	printf("%d\n", iter_count--);
}
```

Flow control
------------

Separate statement and parentheses with a space, because it is not a function.
```c
if (condition)
	/* do something */

while (condition)
	/* do something */

for (initialization; condition; increment)
	/* do something */

do {
	/* do something */
} while (condition);
```

Braces can be omitted when all the bodies have one-line. But must be used when
any of body has multiple lines.
```c
if (condition)
	/* do something in a line */

if (condition) {
	/*
	 * do something
	 * in multiple lines
	 */
} else {
	/* do something in a line */
}
```

DO NOT put code at same line with statement.
```c
if (condition) /* DON'T do anything here */

while (condition); /* DON'T do this neither */
```

Put `case` at the same column with `switch`. Comment if case fall-through.
```c
switch (value) {
case 1: /* fallthrough */
case 2:
	break;
default:
	break;
}
```

Function prototype
------------------

Don't put argument name in function prototype.
```c
void foo(int);
```

Comment is recommended for function prototype. It should explains *what* it
does, not *how* it does.
```c
/* swap two call-by-referenced integers */
void swap(int *, int *);
```

Function definition
-------------------

Here are the rules you have to follow when defining functions.
* Make functions do one thing and do it well.
* Make functions fits it 79 columns and 20 rows.
* Make functions have up to 7 local variables.
* Make functions return error when something went wrong.

Return type should be placed in a separate line.
```c
void
foo(int x)
{
	/* do something */
}
```

Static function should be placed at top of source file.
```c
static void
foo(int x)
{
	/* do something */
}

int
main()
{
	/* do something */
	return 0;
}
```
