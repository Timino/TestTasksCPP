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
                                   NetContainer::ProtocolType type); //! @brief �������� ������ � ������� � �������� �� � @class WidgetController
    //! ����������� ������� getDataFromServer(NetContainer::Container data)
signals:
    void getDataFromServer(NetContainer::Container data);   //! @brief ������ ��� �������� ����������� ������ � �������
public slots:
    void sendDataToServer(NetContainer::Container data);    //! @brief ���� ��� ��������� ����������� ������ �� ������� � �������� �� �� ������
private:
    TCPDriver tcpDriver;
    UDPDriver udpDriver;
};

}
#endif // DRIVERCONTROLLER_HPP
