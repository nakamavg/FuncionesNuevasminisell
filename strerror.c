#include <stdio.h>
#include <string.h>
#include <errno.h>

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
