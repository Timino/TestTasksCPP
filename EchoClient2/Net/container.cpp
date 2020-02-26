#include "container.hpp"

namespace NetContainer
{


Container::Container() :
    tcpData(0),
    udpData(0),
    m_type(static_cast<quint8>(NOT_SELECTED))
{

}

QByteArray Container::getTcpData() const
{
    return tcpData;
}

void Container::setTcpData(const QByteArray &value)
{
    tcpData = value;
}

QByteArray Container::getUdpData() const
{
    return udpData;
}

void Container::setUdpData(const QByteArray &value)
{
    udpData = value;
}

quint8 Container::getType() const
{
    return m_type;
}

void Container::setType(const quint8 &type)
{
    m_type = type;
}

void Container::clearAll()
{
    tcpData.clear();
    udpData.clear();
}

}
