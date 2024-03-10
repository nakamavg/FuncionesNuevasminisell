# Rehaciendo el readline

- Tuve problemas con la instalación de readline a través de brew, así que decidí descargarlo desde la página de GNU. Puedes encontrarlo [aquí](https://git.savannah.gnu.org/cgit/readline.git/commit/?id=5d4d92f221d6aac4be445bdd8cd9b48d9ac33f04).

- Después de descargarlo, ejecuté `./configure` en la terminal y luego `make` para obtener el archivo `.a`.

- Todo esto se realiza en el makefile.

# Añadiendo el comando export

- Obtenemos `env`, asignamos memoria para todo el `env` y luego realocamos para agregar nuevas variables.

- En la versión 2, agregué nodos. Aún mantenemos el tipo `char **` por facilidad en algunas operaciones.

# Añadiendo el comando unset

- `unset` se utiliza para eliminar uno de nuestros nodos recorriendo la lista doblemente enlazada y cambiando los punteros dentro de nuestra estructura de manera sencilla. Es mejor tener una estructura con los siguientes campos:
	- valor
	- nombre
	- siguiente
	- anterior

