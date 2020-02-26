#include "clientgui.hpp"
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>

namespace GUI
{
    TerminalBrowser::TerminalBrowser()
    {
         connect(this, SIGNAL(textChanged()), this, SLOT(scrollToBottom()));
         TerminalBrowser::atBottom = true;
    }



    ClientGUI::ClientGUI(QWidget *parent) : QWidget(parent)
      ,m_btSend(new QPushButton("Send"))
      ,m_rbTCP(new QRadioButton)
      ,m_rbUDP(new QRadioButton)
      ,m_rbBoth(new QRadioButton)
      ,m_lbRButtonTCP(new QLabel("TCP"))
      ,m_lbRButtonUDP(new QLabel("UDP"))
      ,m_lbRButtonBoth(new QLabel("Both"))
      ,m_lbTCP(new QLabel("TCP"))
      ,m_lbUDP(new QLabel("UDP"))
      ,m_lbFromServer(new QLabel)
      ,m_leTCP(new QLineEdit)
      ,m_leUDP(new QLineEdit)
      ,m_browser(new TerminalBrowser)
      ,activeProtocol(TCP)
    {

        m_rbTCP->setObjectName("rbTCP");
        m_rbUDP->setObjectName("rbUDP");
        m_rbBoth->setObjectName("rbBoth");

        QGridLayout *gridLayout = new QGridLayout;
        QHBoxLayout *hlay = new QHBoxLayout;

        hlay->addWidget(m_rbTCP);
        hlay->addWidget(m_lbRButtonTCP, Qt::AlignLeft);
        hlay->addWidget(m_rbUDP);
        hlay->addWidget(m_lbRButtonUDP, Qt::AlignLeft);
        hlay->addWidget(m_rbBoth);
        hlay->addWidget(m_lbRButtonBoth, Qt::AlignLeft);


        gridLayout->addLayout(hlay,0,0,1,6);
        gridLayout->addWidget(m_lbTCP,          1, 0, 1, 1);
        gridLayout->addWidget(m_leTCP,          1, 1, 1, 2);
        gridLayout->addWidget(m_lbUDP,          1, 3, 1, 1);
        gridLayout->addWidget(m_leUDP,          1, 4, 1, 2);
        gridLayout->addWidget(m_btSend,         2, 0, 1, 6);
        gridLayout->addWidget(m_browser,        3, 0, 1, 6);

        m_rbTCP->setChecked(true);
        chooseForm(TCP);
        setLayout(gridLayout);
        connect(m_rbTCP,  SIGNAL(clicked(bool)), this, SLOT(selectInputForms()));
        connect(m_rbUDP,  SIGNAL(clicked(bool)), this, SLOT(selectInputForms()));
        connect(m_rbBoth, SIGNAL(clicked(bool)), this, SLOT(selectInputForms()));

    }

    void ClientGUI::setBrowserData(QString strData)
    {
        m_browser->append(strData);
    }

    void ClientGUI::chooseForm(FormType fType)
    {
        switch (fType)
        {
            case TCP:
            {
                m_leUDP->clear();
                m_leUDP->setDisabled(true);
                m_leTCP->setEnabled(true);
                break;
            }
            case UDP:
            {
                m_leTCP->clear();
                m_leTCP->setDisabled(true);
                m_leUDP->setEnabled(true);
                break;
            }
            case TCPUDP:
            {
                m_leTCP->setEnabled(true);
                m_leUDP->setEnabled(true);
                break;
            }
            default: break;
        }
    }

    quint8 ClientGUI::getActiveProtocol() const
    {
        return activeProtocol;
    }

    QString ClientGUI::getTCPData() const
    {
        return m_leTCP->displayText();
    }

    QString ClientGUI::getUDPData() const
    {
        return m_leUDP->displayText();
    }

    void ClientGUI::selectInputForms()
    {
        if(sender()->objectName() == "rbTCP")
        {
            chooseForm(TCP);
            activeProtocol = static_cast<quint8>(TCP);
        }
        if(sender()->objectName() == "rbUDP")
        {
            chooseForm(UDP);
            activeProtocol = static_cast<quint8>(UDP);
        }
        if(sender()->objectName() == "rbBoth")
        {
            chooseForm(TCPUDP);
            activeProtocol = static_cast<quint8>(TCPUDP);
        }
    }

}
