#include "udpdriver.hpp"

namespace Driver
{

    UDPDriver::UDPDriver()
    {
        // Создаем файловый дескиптор сокета
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            printf("socket creation failed");
            exit(0);
        }
        createConnection();
    }

    UDPDriver::~UDPDriver()
    {
        close(sockfd); //! close закрывает файловый дескриптор, который после этого не ссылается ни на один и файл и может быть использован повторно.
    }

    void UDPDriver::transmitData(const QByteArray &refData)
    {

        memset(buffer, 0, sizeof(buffer));
        buffer[qMin(PACKET_SIZE_UDP -1 ,refData.size())]='\0';
        std::copy(refData.constBegin(),refData.constBegin()+qMin(PACKET_SIZE_UDP -1,refData.size()),buffer);


        sendto(sockfd, (const char*)buffer, strlen(buffer),
               0, (const struct sockaddr*)&servaddr,
               sizeof(servaddr));

//        getResponse();

    }

    void UDPDriver::createConnection()
    {
        memset(&servaddr, 0, sizeof(servaddr));

        servaddr.sin_family = AF_INET; // Заполняем информацию о сервере
        servaddr.sin_port = htons(PORT);
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    }

    QByteArray UDPDriver::getResponse(bool askFlag)
    {
        if(askFlag == true)
        {
        printf("UDP message from server: ");

        socklen_t addrlen = sizeof(servaddr);

        recvfrom(sockfd, (char*)buffer, PACKET_SIZE_UDP,
                 0, (struct sockaddr*)&servaddr,
                 &addrlen);

        puts(buffer);
        QByteArray ba(buffer, sizeof(buffer));
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
