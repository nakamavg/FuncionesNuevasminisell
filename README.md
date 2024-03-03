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
# Funciones para directorios que no a usado el cabron de lloquim xd
## Libreria  include <dirent.h>
### `DIR *opendir(const char *filename)`
 - Esta funcion devuelve un puntero al directorio que podemos usar despues para manipularlo.

### `struct dirent *readdir(DIR *dirp)`

- El fichero previamente abierto por la interior funcion ahora nos devuelve un puntero al siguiente elemento del directorio cada vez que la llamas.

	- el struct Dirent contiene cosas como:
		-  d_ino : numero de serie(inode) del archivo que es unico en el sistema
		- char d_name[]: nombre del archivo/carpeta
	- dependiendo de la plataforma tendra mas cosas
		- d_namelen longitud del nombre
		- d_type tipo de archivo
	
### `int closedir(DIR *dirp)`
	
- cierra el directorio devuelve 0 o menos 1 en caso de error
### Main de ejemplo
```c
#include <stdio.h>
#include <dirent.h>

int main() {
    // Ruta del directorio a abrir
    const char* directorio = ".";

    // Abrir el directorio
    DIR* dir = opendir(directorio);
    if (dir == NULL) {
        printf("No se pudo abrir el directorio.\n");
        return 1;
    }

    // Leer y mostrar los nombres de los archivos en el directorio
    struct dirent* entrada;
    while ((entrada = readdir(dir)) != NULL) {
        printf("%s\n", entrada->d_name);
		//imprimir cada cosa de la estructura
		printf("d_ino: %llu\n", entrada->d_ino);
		printf("d_reclen: %d\n", entrada->d_reclen);
		printf("d_type: %d\n", entrada->d_type);
		printf("d_namlen: %d\n", entrada->d_namlen);
		printf("\n");
    }

    // Cerrar el directorio
    closedir(dir);

    return 0;
}

```
# Errores 

## `char * strerror(int errnum)`

- Le pasas el numero de error y te devuele un puntero a el string del error
 	- ver la relacion entero error [aqui](erroreslista.txt)
## `void perror(const char *s)`
- Le pasas el mensaje de error

### Main de ejemplo con las diferencias  entre estas dos colegas
```c
int main() {
	char *manolo = "no_existe.txt";
	  FILE *file = fopen(manolo, "r");
    if (file == NULL) {
		printf("%s",strerror(errno));
        perror("\nError al abrir el archivo");
		return 1;
    }
    return 0;
}

```
```bash
Error al abrir el archivo: No such file or directory
No such file or directory%  
```
