#include "fat.h"

int main(){
   system("clear");
   char input_str[10000];
   int ch;
   int i;
	while (1){
		memset(input_str,0x0000,sizeof(input_str));
		printf("->"); // o que aparecera no console
		for (i = 0; (i < (sizeof(input_str)-1) &&
         ((ch = fgetc(stdin)) != EOF) && (ch != '\n')); i++){
	 		input_str[i] = ch;
	 	}

			input_str[i] = '\0';

		if (strcmp(input_str,"init") == 0){
			init();
		}else if (strcmp(input_str,"load") == 0){
			load();
		} else if (strcmp(input_str,"exit") == 0){
            exit(0);

        }else if (strcmp(input_str,"clear") == 0){
            system("clear");
		}else if (strstr(input_str, "\"") != NULL) {
			char *cpy = malloc(strlen(input_str)*sizeof(char)); 
			 strcpy(cpy, input_str);

			char * token;

			token = strtok(cpy," \""); // pega a primeira palavra  antes do espaço

			if (strcmp(token,"write") == 0){

				char *string = strtok(NULL, "\""); 
				
				char *path = strtok(NULL, " \"");
				write(string,path);

			} else if (strcmp(token,"append") == 0){

				char *string = strtok(NULL, "\""); 
				
				char *path = strtok(NULL, " \"");
				append(string,path);

			}

		}else {

			 char *cpy = malloc(strlen(input_str)*sizeof(char)); 
			 strcpy(cpy, input_str);

			char * token;

			token = strtok(cpy," "); // pega a primeira palavra  antes do espaço

			if(strcmp(token,"ls") == 0){

				token = strtok(NULL, " "); // apenas o caminho a ser utilizado
				char *teste = malloc(strlen(token)*sizeof(char)); 
				memcpy(teste,token,strlen(token)*sizeof(char));
				ls(token);

			}else if (strcmp(token,"mkdir") == 0){

				token = strtok(NULL, " "); // apenas o caminho a ser utilizado
				mkdir(token);

			}else if (strcmp(token,"create") == 0){
				char *path = strtok(NULL, " "); // apenas o caminho a ser utilizado
				create(path);

			}else if (strcmp(token,"unlink") == 0){

				char *path = strtok(NULL, " "); // apenas o caminho a ser utilizado
				unlink(path);

			}else if (strcmp(token,"read") == 0){

				char *path = strtok(NULL, " "); // apenas o caminho a ser utilizado
				read(path);

			}else {
				printf("Comando não encontrado!\n");
			}

			free(cpy);
		}
	}
	

   return 0;
}