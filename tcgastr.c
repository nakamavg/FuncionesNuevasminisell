//main de ejemmplo para saber que hace la funcion tcgetattr
 #include <stdio.h>
 #include <termios.h>
 #include <unistd.h>
 #include <stdlib.h>
 #include <string.h>
 #include <errno.h>
 #include <sys/ioctl.h>
 #include <signal.h>
 #include <sys/types.h>
 #include <sys/wait.h>
 #include <fcntl.h>
 int main (void)
 {
	 //que es termios
	 //es una estructura que contiene los atributos del terminal
	 //tcgetattr obtiene los atributos del terminal
	 // si me viene una señal control c, el terminal me la manda
	 struct termios term;

	 int ret;
	 ret = tcgetattr(STDIN_FILENO, &term);
	 if (ret == -1)
	 {
		 printf("Error: %s\n", strerror(errno));
		 return (1);
	 }
	 printf("ret: %d\n", ret);	
	 return (0);
 }