#include "tcpdriver.hpp"

namespace Driver
{
    TCPDriver::TCPDriver()
    {

        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("socket creation failed");
            exit(0);
        }
        createConnection();
    }

    TCPDriver::~TCPDriver()
    {
        close(sockfd); //! close закрывает файловый дескриптор, который после этого не ссылается ни на один и файл и может быть использован повторно.
    }

    void TCPDriver::createConnection()
    {
        memset(&servaddr, 0, sizeof(servaddr));

        //! Заполняем информацию о сервере
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(PORT);
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        if (connect(sockfd, (struct sockaddr*)&servaddr,
                    sizeof(servaddr)) < 0) {
            printf("\n Error : Connect Failed \n");
        }
    }

    void TCPDriver::transmitData(const QByteArray &refData)
    {
        memset(buffer, 0, sizeof(buffer));

        buffer[qMin(PACKET_SIZE_TCP -1 ,refData.size())]='\0';
        std::copy(refData.constBegin(),refData.constBegin()+qMin(PACKET_SIZE_TCP -1,refData.size()),buffer);

        write(sockfd, buffer, sizeof(buffer));
    }


    QByteArray TCPDriver::getResponse(bool askFlag)
    {
        if (askFlag == true)
        {
            printf("TCP message from server: ");
            read(sockfd, buffer, sizeof(buffer));
            puts(buffer);
            QByteArray ba(buffer, sizeof(buffer));
            close(sockfd);
            return ba;
        }
        else
        {
            QByteArray ba;
            ba.clear();
            return ba;
        }
    }
}
