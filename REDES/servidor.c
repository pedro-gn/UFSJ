#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>


//Envia o arquivo solicitado para o servidor
// Envia o arquivo solicitado para o servidor
void send_file(FILE *fp, int sockfd, int bufferSize) {
    int n;
    char data[bufferSize];
    
    while (1) {
        size_t bytesRead = fread(data, 1, bufferSize, fp);
        
        if (bytesRead > 0) {
            if (send(sockfd, data, bytesRead, 0) == -1) {
                perror("[-]Error in sending file.");
                exit(1);
            }
        }
        
        if (bytesRead < bufferSize) {
            // Se a leitura for menor que o tamanho do buffer, chegamos ao final do arquivo
            break;
        }
    }
}


int main(int argc, char **argv) {

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <port> <buffer_size>\n", argv[0]);
        exit(1);
    }

    int bufferSize = atoi(argv[2]);
    char *ip = "127.0.0.1";
    int port = atoi(argv[1]);
    int e;


    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char filename[bufferSize];
    FILE *fp;


    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Server socket created successfully.\n");


    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);


    e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (e < 0) {
        perror("[-]Error in bind");
        exit(1);
    }
    printf("[+]Binding successful.\n");


    if (listen(sockfd, 10) == 0) {
        printf("[+]Listening....\n");
    } else {
        perror("[-]Error in listening");
        exit(1);
    }


    addr_size = sizeof(new_addr);
    new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);


    // Recebe o nome do arquivo do cliente
    if (recv(new_sock, filename, bufferSize, 0) == -1) {
        perror("[-]Error in receiving filename.");
        exit(1);
    }


    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("[-]Error in reading file.");
        exit(1);
    }


    send_file(fp, new_sock, bufferSize);
    printf("[+]File data sent successfully.\n");


    // Fecha a conecao
    close(new_sock);
    close(sockfd);


    return 0;
}
