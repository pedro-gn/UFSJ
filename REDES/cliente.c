#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>


unsigned long long receive_file(int sockfd, char *outputFilename, int bufferSize) {
    FILE *fp;
    int n;
    char buffer[bufferSize];

    unsigned long long totalBytesReceived = 0;

    fp = fopen(outputFilename, "w");
    if (fp == NULL) {
        perror("[-]Error in creating output file.");
        exit(1);
    }

    while (1) {
        n = recv(sockfd, buffer, bufferSize, 0);
        if (n <= 0) {
            break;
        }
        totalBytesReceived += n;

        if (fwrite(buffer, 1, n, fp) != n) {
            perror("[-]Error in writing to output file.");
            exit(1);
        }

        bzero(buffer, bufferSize);
    }

    fclose(fp);
    printf("[+]File received successfully. Check output file: %s\n", outputFilename);

    return totalBytesReceived;
}



int main(int argc, char **argv) {

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <host_ip> <port> <buffer_size>\n", argv[0]);
        exit(1);
    }

    int bufferSize = atoi(argv[2]);
    char *ip = argv[1];
    int port = atoi(argv[2]);
    int e;


    int sockfd;
    struct sockaddr_in server_addr;
    char filename[bufferSize];
    char outputFilename[bufferSize];


    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Client socket created successfully.\n");


    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);


    e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (e == -1) {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Connected to Server.\n");


    printf("Enter the filename to request: ");
    fgets(filename, bufferSize, stdin);
    filename[strcspn(filename, "\n")] = '\0';  // Remove newline character


    printf("Enter the output filename: ");
    fgets(outputFilename, bufferSize, stdin);
    outputFilename[strcspn(outputFilename, "\n")] = '\0';  // Remove newline character


    struct timeval start, end;
    gettimeofday(&start, NULL);  // começa medir o tempo na hora que manda o nome do arquivo


    if (send(sockfd, filename, bufferSize, 0) == -1) {
        perror("[-]Error in sending filename.");
        exit(1);
    }

    unsigned long long totalBytesReceived = receive_file(sockfd, outputFilename, bufferSize);

    gettimeofday(&end, NULL);  // para de medir o tempo quando recebe todo o arquivo

    double elapsedTime = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) * 1e-6;
    double transferRate = totalBytesReceived / elapsedTime;

    printf("[+]Total transfer time: %.6f seconds\n", elapsedTime);
    printf("[+]Total bytes transferred: %llu bytes\n", totalBytesReceived);
    printf("[+]Transfer rate: %.2f Bps\n", transferRate);

    printf("[+]Closing the connection.\n");
    close(sockfd);

    return 0;
}
