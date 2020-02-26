#ifndef TCPDRIVER_HPP
#define TCPDRIVER_HPP

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include <arpa/inet.h>
#include <netdb.h>

#include <QByteArray>
#include <QObject>

#define PORT 5000
#define PACKET_SIZE_TCP 1024

namespace Driver
{
    class TCPDriver
    {
    public:
        TCPDriver();
        ~TCPDriver();
        void transmitData(const QByteArray &refData);   //! @brief Передаем данные на сервер
        QByteArray getResponse(bool askFlag = false);   //! @brief Получаем данные с сервера
    private:
        void createConnection();                        //! @brief Конфигурируем и создаем соединение с сервером
        int sockfd;
        char buffer[PACKET_SIZE_TCP];
        struct sockaddr_in servaddr;
    };
}
#endif // TCPDRIVER_HPP
