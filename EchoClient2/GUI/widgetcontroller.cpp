#include "widgetcontroller.hpp"
#include <QHBoxLayout>

namespace GUI
{

    WidgetController::WidgetController(QObject *parent) : QObject(parent)
      ,m_clientGUI(new GUI::ClientGUI)
    {
        m_clientGUI->show();
        connect(m_clientGUI->m_btSend, SIGNAL(clicked(bool)), this, SLOT(createContainer()));
    }

    void WidgetController::parseContainer(NetContainer::Container dataContainer)
    {
        quint8 m_type;
        m_type = dataContainer.getType();
        switch (m_type)
        {
            case NetContainer::TCP:
            {
                tcpData = dataContainer.getTcpData();
                QString str(byteArrayToStr(tcpData));
                m_clientGUI->setBrowserData(str);
                break;
            }
            case NetContainer::UDP:
            {
                udpData = dataContainer.getUdpData();
                QString str(byteArrayToStr(udpData));
                m_clientGUI->setBrowserData(str);
                break;
            }
            case NetContainer::TCPUDP:
            {
                tcpData = dataContainer.getTcpData();
                QString strTCP(byteArrayToStr(tcpData));
                udpData = dataContainer.getUdpData();
                QString strUDP(byteArrayToStr(udpData));
                m_clientGUI->setBrowserData(strTCP);
                m_clientGUI->setBrowserData(strUDP);
                break;
            }
            default : break;
        }
    }

    void WidgetController::createContainer()
    {
        NetContainer::Container dataToServerContainer;
        dataToServerContainer.clearAll();


        switch (m_clientGUI->getActiveProtocol())
        {
            case NetContainer::TCP:
            {
                dataToServerContainer.setType(static_cast<quint8>(NetContainer::TCP));
                dataToServerContainer.setTcpData(m_clientGUI->getTCPData().toUtf8());
                break;
            }
            case NetContainer::UDP:
            {
                dataToServerContainer.setType(static_cast<quint8>(NetContainer::UDP));
                dataToServerContainer.setUdpData(m_clientGUI->getUDPData().toUtf8());
                break;
            }
            case NetContainer::TCPUDP:
            {
                dataToServerContainer.setType(static_cast<quint8>(NetContainer::TCPUDP));
                dataToServerContainer.setTcpData(m_clientGUI->getTCPData().toUtf8());
                dataToServerContainer.setUdpData(m_clientGUI->getUDPData().toUtf8());
                break;
            }
            default: break;
        }
        emit sendDataToServer(dataToServerContainer);
    }

    QString WidgetController::byteArrayToStr(const QByteArray &dataArray)
    {
        QString str(dataArray);
        return str;
    }

}
