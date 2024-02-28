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

## `getcwd()`
- Esto es literalmente un pwd

```c
int main(void)
{
	char *pwd;
 	pwd =  getcwd(NULL,0);
    printf("%s\n", pwd);
    return (0);
}
```
output
```bash
*[nakama][~/FuncionesNuevasminisell]$ ./a.out
/Users/dgomez-m/FuncionesNuevasminisell
```
## `chdir()`
 - Esta funcion es literalmente la llave maestra(junto ccon lla anterior) para el cd aqui un ejemplo:


```c
int main(void)
{
	char *pwd;
	char *cdroute;
	char *cdin;
	int i;
	i=0;
 	pwd =  getcwd(NULL,0);
    printf("%s\n", pwd);
	cdroute = ft_strrchr(pwd,'/');
	cdin = ft_substr(pwd,0, ft_strlen(pwd) - ft_strlen(cdroute));
    printf("%s\n",cdin);
	chdir(cdin);
	pwd =  getcwd(NULL,0);
    printf("%s\n", pwd);
	
		
    return (0);
}
```
```bash
*[cositas][~/FuncionesNuevasminisell]$ ./minishell
/Users/dgomez-m/FuncionesNuevasminisell
/Users/dgomez-m
/Users/dgomez-m
```