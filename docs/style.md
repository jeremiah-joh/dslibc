Coding style
============

This is a coding style that I prefer.

Basic
-----

Use C90(ISO/IEC 9899:1990) without extension.
Declare variables on top of block.
Use `for (;;)` instead of `while(1)` on infinite loop.

Indentation
-----------

Indentation is Tab character, not spaces. Tab is 8 spaces width. No exception.

Naming
------

Use `snake_case` for everything. No exception.  

Name should be short and clear. Don't try to name like `temporary_value`.
Try to name variable less than 8 characters.
And try to name function less than 16 characters.
But try to explain what the thing does in that short name.

Function
--------

Here are some rules you have to follow when making a function.

* Make function does one thing and does it well.
* Make function body fits in 20 rows.
* Make function has up to 7 local variables.
* Make function returns error when something went wrong.

Only main function can violate these rules.

Put return type and modifier on top of function name.

```c
static int
foo()
{
    /* do something */
}
```

And DO NOT add space between function name and parentheses.

Flow control
------------

Unlike function, { is placed at same line with keyword.
And keyword and parentheses are separated by a space.

```c
if (condition) {
    /* do something */
}

while (condition) {
    /* do something */
}

for (init; condition; incr) {
    /* do something */
}

do {
    /* do something */
} while (condition);
```

Don't use { and } when code inside of flow control is only one line.

Put switch and case on same column. And comment when case fall-through.
```c
switch (value) {
case 0: /* FALLTHOUGH */
case 1:
case 2:
    /* do something */
    break;
default:
    /* do something */
    break;
}
```

