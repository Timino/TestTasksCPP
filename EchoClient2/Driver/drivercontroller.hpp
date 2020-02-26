#ifndef DRIVERCONTROLLER_HPP
#define DRIVERCONTROLLER_HPP

#include <QObject>
#include "../Net/container.hpp"
#include "tcpdriver.hpp"
#include "udpdriver.hpp"

namespace Driver
{

class DriverController : public QObject
{
    Q_OBJECT
public:
    explicit DriverController(QObject *parent = nullptr);
    void createContainerFromServer(const QByteArray & arrTCPData,
                                   const QByteArray & arrUDPData,
                                   NetContainer::ProtocolType type); //! @brief Упаковка данных с сервера и отправка их в @class WidgetController
    //! посредством сигнала getDataFromServer(NetContainer::Container data)
signals:
    void getDataFromServer(NetContainer::Container data);   //! @brief Сигнал для отправки упакованных данных с сервера
public slots:
    void sendDataToServer(NetContainer::Container data);    //! @brief Слот для получения упакованных данных от клиента и передачи их на сервер
private:
    TCPDriver tcpDriver;
    UDPDriver udpDriver;
};

}
#endif // DRIVERCONTROLLER_HPP
