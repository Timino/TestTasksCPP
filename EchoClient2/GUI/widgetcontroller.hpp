#ifndef WIDGETCONTROLLER_HPP
#define WIDGETCONTROLLER_HPP

#include "clientgui.hpp"
#include "../Net/container.hpp"

#include <QObject>

namespace GUI
{

    class WidgetController : public QObject
    {
        Q_OBJECT
    public:
        explicit WidgetController(QObject *parent = nullptr);
    signals:
        void sendDataToServer(NetContainer::Container dataContainer);   //! @brief сигнал для отправки сконфигурированного контейнера с данными
    public slots:
        void parseContainer(NetContainer::Container dataContainer);     //! @brief Парсинг полученного от @class DriverController
        //! контейнера с данными
    private slots:
        void createContainer(); //! @brief Конфигурируем и отправляем контейнер с данными с GUI на @class DriverController, с помощью
        //! сигнала sendDataToServer(NetContainer::Container dataContainer)
    private:
        GUI::ClientGUI *m_clientGUI;
        QString     byteArrayToStr(const QByteArray& dataArray);        //! @brief Метод для преобразования QByteArray в QString
        QByteArray  tcpData;
        QByteArray  udpData;
    };

}

#endif // WIDGETCONTROLLER_HPP
