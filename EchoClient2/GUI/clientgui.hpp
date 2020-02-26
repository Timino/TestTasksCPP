#ifndef CLIENTGUI_HPP
#define CLIENTGUI_HPP

#include <QWidget>
#include <QRadioButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextBrowser>
#include <QtGui>
#include <QTextEdit>
#include <QScrollBar>
#include <QPushButton>

namespace GUI
{
    enum FormType
    {
        TCP = 0,
        UDP,
        TCPUDP
    };

    class TerminalBrowser : public QTextBrowser //! @class Класс оболочка над QTextBrowser, для обработки области скроллинга
    {
        Q_OBJECT
    public:
        bool atBottom;
        TerminalBrowser();
    public slots:
        void scrollToBottom(void)
        {
            if(this->atBottom)
            {
                this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum());
            }
        }
    };

    class ClientGUI : public QWidget
    {
        Q_OBJECT
    public:
        explicit ClientGUI(QWidget *parent = nullptr);
        void setBrowserData(QString strData);   //! @brief Отображает приходящие данные в окне браузера
        quint8 getActiveProtocol() const;       //! @brief Возвращает тип протокола, который пользователь выбрал с помощью QRadiButton
        QString getTCPData() const;             //! @brief Получить данные с поля ввода информация для передачи по TCP протоколу
        QString getUDPData() const;             //! @brief Получить данные с поля ввода информация для передачи по UDP протоколу
        QPushButton     *m_btSend;
    private:
        void chooseForm(FormType fType);        //! @brief Дизейбл и очистка форм ввода, в зависимости от типа протокола выбранного пользователем
        QRadioButton    *m_rbTCP, *m_rbUDP, *m_rbBoth;
        QLabel          *m_lbRButtonTCP, *m_lbRButtonUDP, *m_lbRButtonBoth;
        QLabel          *m_lbTCP, *m_lbUDP, *m_lbFromServer;
        QLineEdit       *m_leTCP, *m_leUDP;
        TerminalBrowser *m_browser;
        QTextEdit       m_textInBrowser;
        quint8          activeProtocol;
    private slots:
        void selectInputForms();                //! @brief Выбор типа протокола в GUI, вызов метода chooseForm(FormType fType)

    };
}

#endif // CLIENTGUI_HPP
