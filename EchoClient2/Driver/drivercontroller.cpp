#include "drivercontroller.hpp"

namespace Driver
{

DriverController::DriverController(QObject *parent) : QObject(parent)
{

}

void DriverController::createContainerFromServer(const QByteArray & arrTCPData,const QByteArray & arrUDPData, NetContainer::ProtocolType type)
{
    NetContainer::Container containerToClient;
    containerToClient.clearAll();

    quint8 typeID = static_cast<quint8>(type);

    switch(typeID)
    {
        case NetContainer::TCP:
        {
            containerToClient.setTcpData(arrTCPData);
            containerToClient.setType(typeID);
            break;
        }
        case NetContainer::UDP:
        {
            containerToClient.setUdpData(arrUDPData);
            containerToClient.setType(typeID);
            break;
        }
        case NetContainer::TCPUDP:
        {
            containerToClient.setTcpData(arrTCPData);
            containerToClient.setUdpData(arrUDPData);
            containerToClient.setType(typeID);
            break;
        }
        default: break;
    }
    emit getDataFromServer(containerToClient);

}

void DriverController::sendDataToServer(NetContainer::Container dataContainer)
{
    switch(dataContainer.getType())
    {
        case NetContainer::TCP:
        {
            tcpDriver.transmitData(dataContainer.getTcpData());
            createContainerFromServer(tcpDriver.getResponse(true),udpDriver.getResponse(false),  NetContainer::TCP);
            break;
        }
        case NetContainer::UDP:
        {
            udpDriver.transmitData(dataContainer.getUdpData());
            createContainerFromServer(tcpDriver.getResponse(false), udpDriver.getResponse(true), NetContainer::UDP);
            break;
        }
        case NetContainer::TCPUDP:
        {
            tcpDriver.transmitData(dataContainer.getTcpData());
            udpDriver.transmitData(dataContainer.getUdpData());
            createContainerFromServer(tcpDriver.getResponse(true), udpDriver.getResponse(true), NetContainer::TCPUDP);
            break;
        }
        default: break;
    }
}

}
