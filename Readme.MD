# Añadiendo el comando export
- Obtenemos env , mallocamos para todo el env y luego realocamos para 
	añadir variables nuevas
- En la version 2, agregue nodos. Aun mantenemos el tipo char ** por facilidad en algunas operaciones.
- Obtenemos `env`, asignamos memoria para todo el `env` y luego realocamos para agregar nuevas variables.


# Añadiendo el comando unset

- `unset` se utiliza para eliminar uno de nuestros nodos recorriendo la lista doblemente enlazada y cambiando los punteros dentro de nuestra estructura de manera sencilla. Es mejor tener una estructura con los siguientes campos:
	- valor
	- nombre
	- siguiente
	- anterior
- Pequeña actualización para que export funcione asi:
```bash
export paco
``` 
sin el caracter `=` deberia iniciar una variable vacia con comillas simples

- Me he pegado con la parte que checkea si existe en el export
	- deberia de hacer lo mismo en el unset 

# Añadiendo el comando cd

- `cd` se utiliza para cambiar el directorio de trabajo. Para ello, se utiliza la función `chdir` de la librería `unistd.h`.
- Estoy actualizando la variable `PWD` con nuestra función `export` para que siempre tenga el valor del directorio actual.
- Añadí una función que se encarga de actualizar la variable `OLDPWD` con el valor de `PWD` antes de cambiar de directorio.
