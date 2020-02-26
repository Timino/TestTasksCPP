#include <QApplication>
#include <QString>
#include <QByteArray>
#include <QObject>

#include "Driver/drivercontroller.hpp"
#include "GUI/widgetcontroller.hpp"


//! @mainpage Сторона клиента выполнена по следующей "архитектуре".:)
//! @class DriverController представляет собой контроллер, общающейся с сервером посредством 2 драйверов каждый для TCP и UDP
//! соединения соответсвенно. А со стороной GUI и всем внешнем миром, посредством транспортного контейнера, @class Container
//! чей функционал может расширяться в зависимости от расширения требований или изменения задачи. В базовом варианте он содержит
//! тип соединения, который надо использовать для взаимодействием с сервером, а также QByteArray для передачи инфомации, так как в QByteArray
//! при желании можно положить что угодно, а Qt предоставляет широкий инструментарий для работы с ним, а также возмодности его(QByteArray`я)
//! применения в другом функционале фреймворка.
//! @class WidgetController отвечающий за функционирование класса GUI @class ClientGUI, а также за взаимодействие с внешним миром, посредством
//! приемопередачи объектов класса транспортного контейнера @class Container

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Driver::DriverController    *m_driver           = new Driver::DriverController;
    GUI::WidgetController       *widgetController   = new GUI::WidgetController;

    QObject::connect(m_driver, SIGNAL(getDataFromServer(NetContainer::Container)),
                     widgetController, SLOT(parseContainer(NetContainer::Container)));

    QObject::connect(widgetController, SIGNAL(sendDataToServer(NetContainer::Container)),
                     m_driver, SLOT(sendDataToServer(NetContainer::Container)));

    return a.exec();
}
