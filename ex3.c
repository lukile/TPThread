

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

//Code client-server multi-process, with multi-thread
void *create_socket(void *socket_connection) {
    char str[100];
    while(1) {

        bzero(str, 100);

        read(*(int*)socket_connection,str,100);

        write(2,str,100);

        write(*(int*)socket_connection, str, strlen(str)+1);

    }
}

int main() {

    int listen_fd, conn_fd;

    pthread_t thread;

    struct sockaddr_in servaddr;
    struct sockaddr cliaddr;
    socklen_t sa_len=sizeof(cliaddr);

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    bzero( &servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(8081);

    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    listen(listen_fd, 10);


    //conn_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
    while(1) {
        conn_fd = accept(listen_fd, &cliaddr, &sa_len);

        pthread_create(&thread, NULL, create_socket, (void*)&conn_fd);
    }
}
