# Funciones que vamos a necesitar

## `char *readline (const char *prompt);`
 - Para usar esta funcion necesitaremos vaarias cosas
		- [Tener brew instalado gracias al bash
		de lloquim](brewTosGoinfre.sh)
		- includes 
		- brew install brew install readline
		- y necistamos compilar con esto :
```plaintext
-L/usr/local/lib -I/usr/local/include -lreadline
```
```c
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
```
- lo que conseguimos con esta funcion es que nos peremite guardar un input a la vez que mostramos un mensaje por pantalla