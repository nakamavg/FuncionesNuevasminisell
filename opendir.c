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
