# printf_scanf_C
My alternatives for printf and scanf C funtions

my_printf accepts these formats:
```
* %s - pointer to string
* %d - 32 bit integer
* %f - Double precision float, prints up to 5 numbers after decimal point
* %p - Point structure (x, y)
```

Returns number of displayed chracters

my_scanf accepts these formats:
```
* %d - 32 bit integer
* %f - Double precision float, prints up to 5 numbers after decimal point
* %p - Point structure (x, y)
```

Returns number of succesfully retrieved from input

Example of execution:
```
struct point_t a;
my_printf("Wpisz punkt w postaci (x y): ");
int res = my_scanf("%p", &a);
my_printf("Wynik: [%d;%d;%d]", a.x, a.y, res);

Result:
Wpisz punkt w postaci (x y): (111 222)⏎
Wynik: [111;222;2]
```

