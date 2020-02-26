#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <QObject>

namespace NetContainer
{

    enum ProtocolType
    {
        TCP = 0,
        UDP,
        TCPUDP,
        NOT_SELECTED
    };

class Container
{
public:
    Container();

    QByteArray getTcpData() const;              //! @brief Получить из объекта класса контейнера массив данных, передаваемый по TCP протоколу
    void setTcpData(const QByteArray &value);   //! @brief Передать в объект класса контейнера массив данных, передаваемый по TCP протоколу

    QByteArray getUdpData() const;              //! @brief Получить из объекта класса контейнера массив данных, передаваемый по UDP протоколу
    void setUdpData(const QByteArray &value);   //! @brief Передать в объект класса контейнера массив данных, передаваемый по UDP протоколу

    quint8 getType() const;                     //! @brief Получить тип протокола объекта класса контейнера
    void setType(const quint8 &type);           //! @brief Задать тип протокола объекта класса контейнера
    void clearAll();
private:
    QByteArray tcpData;
    QByteArray udpData;
    quint8 m_type;
};

}
#endif // CONTAINER_HPP
