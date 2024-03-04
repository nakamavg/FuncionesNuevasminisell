#include <stdio.h>
#include <termios.h>
#include <signal.h>

void handleSignal(int signal) {
	// No hacer nada en este caso
}

int main() {
	struct termios term;
	
	// Capturar la señal de control C
	signal(SIGINT, handleSignal);
	
	// Obtener los atributos actuales del terminal
	if (tcgetattr(0, &term) == -1) {
		perror("tcgetattr");
		return 1;
	}
	
	// Imprimir los atributos del terminal
	printf("Atributos del terminal:\n");
	printf("c_iflag: %x\n", term.c_iflag);
	printf("c_oflag: %x\n", term.c_oflag);
	printf("c_cflag: %x\n", term.c_cflag);
	printf("c_lflag: %x\n", term.c_lflag);
	
	return 0;
}
