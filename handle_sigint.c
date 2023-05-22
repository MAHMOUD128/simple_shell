#include "main.h"

/**
  * handle_sigint - prints new line and a prompt when ctrl + c is pressed
  * @sig: number passed by os when SIGINT signal is generated
  */
void handle_sigint(int sig)
{
	(void) sig;
	write(STDOUT_FILENO, "\n$ ", 3);
}
