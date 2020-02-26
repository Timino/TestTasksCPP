#include "server.hpp"
#include <QDebug>

Server::Server()
{
    qDebug() << "Server is working" << endl;

    createTCPSocket();
    createUDPSocket();

    FD_ZERO(&rset);                     //! Очищаем набор дескрипторов сокетов

    maxfdp1 = max(tcpfd, udpfd) + 1;    //! Найдем максимальный int для select`а

    while(true)
    {
        //! Добавляем наши сокеты в "массив" дескрипторов rset типа fd_set
        FD_SET(tcpfd, &rset);
        FD_SET(udpfd, &rset);

        //! Передаем в select наш набор дескрипторов  rset и ждем в цикле пока состояние не обновится
        nready = select(maxfdp1, &rset, NULL, NULL, NULL);

        processTCP();
        processUDP();
    }
}

int Server::max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

void Server::createTCPSocket()
{
    tcpfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    bind(tcpfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(tcpfd, 10);
}

void Server::createUDPSocket()
{
    udpfd = socket(AF_INET, SOCK_DGRAM, 0);

    bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
}

void Server::processTCP()
{
    //! С помощью FD_ISSET можно проверить, были ли изменения по TCP сокету. Если сокет готов, перехватываем с него данные, путем установки
    //! соединения с помощью accept()
    if (FD_ISSET(tcpfd, &rset))
    {
        len = sizeof(cliaddr);

        //! Системный вызов accept() используется с сокетами, ориентированными на установление
        //! соединения (SOCK_STREAM, SOCK_SEQPACKET). accept() извлекает первый запрос на соединение из очереди
        //! ожидающих соединений прослушивающего сокета, sockfd, создаёт новый подключенный сокет и
        //! возвращает новый файловый дескриптор, указывающий на сокет.
        //! Новый сокет более не находится в слушающем состоянии. Исходный сокет sockfd не изменяется при этом вызове.
        connfd = accept(tcpfd, (struct sockaddr*)&cliaddr, &len);
        if ((childpid = fork()) == 0)
        {
            close(tcpfd);
            bzero(buffer, sizeof(buffer));
            printf("Message From TCP client: ");
            read(connfd, buffer, sizeof(buffer));
            puts(buffer);
            write(connfd, (const char*)buffer, sizeof(buffer));
            close(connfd);
            exit(0);
        }
        close(connfd);
    }
}

void Server::processUDP()
{
    //! Здесь же с помощью FD_ISSET можно проверить, были ли изменения по UDP сокету, если да, то получаем сообщение
    if (FD_ISSET(udpfd, &rset))
    {
        len = sizeof(cliaddr);
        bzero(buffer, sizeof(buffer));
        printf("\nMessage from UDP client: ");
        n = recvfrom(udpfd, buffer, sizeof(buffer), 0,
                     (struct sockaddr*)&cliaddr, &len);
        puts(buffer);
        sendto(udpfd, (const char*)buffer, sizeof(buffer), 0,
               (struct sockaddr*)&cliaddr, sizeof(cliaddr));
    }
}
