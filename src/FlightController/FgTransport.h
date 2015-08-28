/*!
 * @file FgTransport.h
 *
 * @brief Transport for interacting with FlightGear
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Aug 28, 2015
 */

#ifndef FGPROTOCOL_H
#define FGPROTOCOL_H

#include "FgGenericProtocol.h"

#include <QObject>
#include <QSettings>
#include <QUdpSocket>
#include <QHostAddress>

#include <memory>

class FgTransport : public QObject
{
    Q_OBJECT
public:
    explicit FgTransport(QObject *parent = 0);
    ~FgTransport();

    inline QHostAddress listenHost() const;
    inline void         setListenHost(const QHostAddress address);
    inline int          listenPort() const;
    inline void         setListenPort(const int _port);
    inline QHostAddress host() const;
    inline void         setHost(const QHostAddress address);
    inline int          port() const;
    inline void         setPort(const int _port);

    bool setConfig(QSettings& settings);
    bool saveConfig(QSettings& settings);

    inline QString getString(const QString& node, bool *exists = nullptr) const;
    inline qreal getFloat(const QString& node, bool *exists = nullptr) const;
    inline qint32 getInt(const QString& node, bool *exists = nullptr) const;

    inline std::shared_ptr<FgGenericProtocol> protocol() const;

    bool writeData(const QString& data);
    inline QString networkParams() const;

private:
    std::shared_ptr<QUdpSocket>        m_Socket    { std::make_shared<QUdpSocket>()        };
    std::shared_ptr<QUdpSocket>        m_SocketOut { std::make_shared<QUdpSocket>()        };
    std::shared_ptr<FgGenericProtocol> m_Protocol  { std::make_shared<FgGenericProtocol>() };

    bool         m_GenericEnabled       { false };
    QHostAddress m_ListenHost           { "127.0.0.1" };
    quint16      m_ListenPort           { 8000 };
    QString      m_ListenProtocol       { "udp" };
    QString      m_ListenGenericProtocol{ "FgaProtocol" };
    int          m_ListenFrequency      { 40 };
    QHostAddress m_WriteHost            { "127.0.0.1" };
    quint16      m_WritePort            { 8001 };
    QString      m_WriteProtocol        { "udp" };
    QString      m_WriteGenericProtocol { "FgaProtocol" };
    int          m_WriteFrequency       { 40 };
    QByteArray   m_Buffer               { };
    QStringList  m_FdmData              { };

signals:
    void fgDataReceived(const FgTransport &transport);

private slots:
    void onSocketRead();

public slots:

    friend class ControlledAircraftTest;
};

//
QHostAddress FgTransport::listenHost() const
{
    return m_ListenHost;
}

void FgTransport::setListenHost(const QHostAddress address)
{
    m_ListenHost = address;
}

int FgTransport::listenPort() const
{
    return m_ListenPort;
}

void FgTransport::setListenPort(const int _port)
{
    m_ListenPort = _port;
}

QHostAddress FgTransport::host() const
{
    return m_WriteHost;
}

void FgTransport::setHost(const QHostAddress address)
{
    m_WriteHost = address;
}

int FgTransport::port() const
{
    return m_WritePort;
}

void FgTransport::setPort(const int _port)
{
    m_WritePort = _port;
}

QString FgTransport::getString(const QString& node, bool *exists) const
{
    int paramIndex = m_Protocol->getParamIndex(node);
    if (paramIndex > -1)
    {
        if (exists)
        {
            *exists = true;
        }
        return m_FdmData[paramIndex]; //! @todo check index
    }

    if (exists)
    {
        *exists = false;
    }
    return "";
}

qreal FgTransport::getFloat(const QString& node, bool *exists) const
{
    QString param = getString(node);
    return param.isEmpty() ? 0.0 : param.toFloat(exists);
}

qint32 FgTransport::getInt(const QString& node, bool *exists) const
{
    QString param = getString(node);
    return param.isEmpty() ? 0 : param.toInt(exists);
}

std::shared_ptr<FgGenericProtocol> FgTransport::protocol() const
{
    return m_Protocol;
}

QString FgTransport::networkParams() const
{
    if (!m_GenericEnabled)
        return "";

    return QString("--generic=socket,out,%1,%2,%3,%4,%5 --generic=socket,in,%6,%7,%8,%9,%10")
            .arg(m_ListenFrequency)
            .arg(m_ListenHost.toString())
            .arg(m_ListenPort)
            .arg(m_ListenProtocol, m_ListenGenericProtocol)
            .arg(m_WriteFrequency)
            .arg(m_WriteHost.toString())
            .arg(m_WritePort)
            .arg(m_WriteProtocol, m_WriteGenericProtocol);
}

#endif // FGPROTOCOL_H
