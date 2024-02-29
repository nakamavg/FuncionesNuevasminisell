#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *entry;

    // Abre el directorio actual
    dir = opendir(".");
    if (dir == NULL) {
        printf("No se pudo abrir el directorio.\n");
        return 1;
    }
	//imprimir el contenido  del directorio
	while ((entry = readdir(dir)) != NULL) {
		printf("%s\n", entry->d_name);
		printf("Numero de inodo: %llu\n", entry->d_ino);
		printf("Tipo de archivo: %d\n", entry->d_type);
		printf("Longitud de nombre: %d\n", entry->d_reclen);
		printf("\n");
	}
	
    closedir(dir);

    return 0;
}
