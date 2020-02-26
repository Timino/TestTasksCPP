#ifndef SERVER_HPP
#define SERVER_HPP

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define PORT 5000
#define PACKET_SIZE 1024

class Server
{
public:
    Server();
private:
    int max(int x, int y);
    void createTCPSocket(); //! @brief Создаем TCP сокет и связываем его bind`ом со структурой серверного сокета
    void createUDPSocket(); //! @brief Создаем TCP сокет и связываем его bind`ом со структурой серверного сокета
    void processTCP();      //! @brief Ожидаем, получаем и передаем обратно сообщение. Для TCP соединения
    void processUDP();      //! @brief Ожидаем, получаем и передаем обратно сообщение. Для UDP соединения
    int tcpfd, connfd, udpfd, nready, maxfdp1;
    char buffer[PACKET_SIZE];
    pid_t childpid;                         //! Pid_t тип данных - целое число со знаком, ID процесса.
    fd_set rset;                            //! Набор дескрипторов сокетов, предназначенных для операций чтения, записи
    ssize_t n;
    socklen_t len;                          //! Представляет длину структуры sockaddr.
    struct sockaddr_in cliaddr, servaddr;   //! Структура sockaddr_in описывает сокет для работы с протоколами IP
};

#endif // SERVER_HPP
