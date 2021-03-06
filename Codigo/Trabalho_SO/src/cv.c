#include "headers/auxiliar.h"

int main(int argc, char* argv[]){
	char byte[200];
	ssize_t size;	
	size_t nstrings;
	
	char pidchar[50];
	char output[200];
	sprintf(pidchar, "%d", getpid());
	strcpy(output, "C");
	strcat(output, pidchar);
	int fifo = mkfifo(output, 0600);

	while((size = readln(STDIN_FILENO, byte, 200)) > 0){

		char** lista = strsplit(byte, " ", &nstrings);
		char aux[200];
		sprintf(aux, "%ld", nstrings);
		
		if(nstrings <= 2 && nstrings > 0 && isDigit(lista[0])){
			if(nstrings == 2 && ((lista[1][0] == '-' && isDigit(lista[1]+1)) || isDigit(lista[1]) )){
					
					char input[260];
					strcpy(input, pidchar);
					strcat(input, " ");
					strcat(input, byte);
					strcat(input, "\n");
					int fdInput = open("inputCliente", O_WRONLY);
					write(fdInput, input, strlen(input)+1);
					close(fdInput);
					char resultado[100];

					int fdOutput = open(output, O_RDONLY);
					readln(fdOutput, resultado, 100);
					close(fdOutput);
					strcat(resultado,"\n");
					write(STDOUT_FILENO, resultado, strlen(resultado));
			}
			else if(nstrings == 1){
					char input[260];
					strcpy(input, pidchar);
					strcat(input, " ");
					strcat(input, byte);
					strcat(input, "\n");
					int fdInput = open("inputCliente", O_WRONLY);
					write(fdInput, input, strlen(input)+1);
					close(fdInput);

					char resultado[100];
					int fdOutput = open(output, O_RDONLY);
					readln(fdOutput, resultado, 100);
					close(fdOutput);
					strcat(resultado,"\n");
					write(STDOUT_FILENO, resultado, strlen(resultado));
			}
			else {write(STDOUT_FILENO, "Comando inválido!\n", 19);}
		} 
		else {write(STDOUT_FILENO, "Comando inválido!\n", 19);}
	}

	return 0;
}