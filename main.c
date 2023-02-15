#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

/** TCP **/
short socket_create(void)
{
    short h_socket;
    printf("Create the socket\n");
    h_socket = socket(AF_INET, SOCK_STREAM, 0);
    return h_socket;
}

/** IPv4 **/
int socket_connect(int h_socket)
{
    int i_retval = -1;
    int server_port = 21;
    
    struct sockaddr_in remote = {0};
    remote.sin_addr.s_addr = inet_addr("192.168.0.120");
    remote.sin_family = AF_INET;
    remote.sin_port = htons(server_port);

    i_retval = connect(h_socket, (struct sockaddr *)&remote, sizeof(struct sockaddr_in));

    return i_retval;
}

int socket_send(int h_socket, char *rqst, short len_rqst)
{
    int short_ret_val = -1;
    struct timeval tv;
    tv.tv_sec = 20;
    tv.tv_usec = 0;

    if(0 > setsockopt(h_socket, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(tv)))
    {
        printf("Time Out\n");
        return -1;
    }

    short_ret_val = send(h_socket, rqst, len_rqst, 0);
    return short_ret_val;
}

int socket_receive(int h_socket, char *rsp, short rvc_size)
{
    int short_ret_val = -1;
    struct timeval tv;
    tv.tv_sec = 20;
    tv.tv_usec = 0;

    if(0 > setsockopt(h_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv)))
    {
        printf("Time Out\n");
        return -1;
    }

    short_ret_val = recv(h_socket, rsp, rvc_size, 0);
    //printf("Response: %s\n", rsp);

    return short_ret_val;
}

int main(int argc, char *argv[])
{
    int h_socket = 0, read_size = 0;
    struct sockaddr_in server;
    char send_to_server[100] = {0};
    char server_reply[200] = {0};

    // Criar o socket
    h_socket = socket_create();

    if(-1 == h_socket)
    {
        printf("Nao foi possivel criar o socket");
        return 1;
    }

    //Conecta no servidor
    if(0 > socket_connect(h_socket))
    {
        perror("A conexão falhou");
        return 1;
    }

    printf("Conexão bem sucedida\n");

    read_size = socket_receive(h_socket, server_reply, 200);
    printf("Resposta do servidor: %s\n\n", server_reply);

while(1)
{
    printf("Digite a mensagem: ");
    fgets(send_to_server, 100, stdin);

    // Envia a mensagem para o servidor
    socket_send(h_socket, send_to_server, strlen(send_to_server));

    // Recebe a mensagem do servidor
    read_size = socket_receive(h_socket, server_reply, 200);
    printf("Resposta do servidor: %s\n\n", server_reply);
}

}