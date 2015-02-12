/*!
 * @file FgController.cpp
 *
 * @brief Controller
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 08, 2015
 * @date Modified Feb 12, 2015
 */

#ifndef FGCONTROLLER_H
#define FGCONTROLLER_H

#include <QObject>
#include <QHash>


class FgAircraft;
class FgTransport;

class FgController : public QObject
{
    Q_OBJECT
public:
    explicit FgController(QObject *parent = 0);
    typedef QHash<QString, FgAircraft*> TFgAircraftList;

private:
    FgTransport *m_Transport;
    TFgAircraftList m_OurAircrafts;
    TFgAircraftList m_OtherAircrafts;
    qint32 m_AircraftsCount;

    void updateOurAircraftsCount();
    void updateOtherAircraftsCount();

private slots:
    void onDataReceived();

public slots:
    void updateAircraft(const QString &aircraftId);

signals:
    void aircraftConnected(FgAircraft* aircraft);
    void ourAircraftConnected(FgAircraft* aircraft);
    void aircraftDisconnected(FgAircraft* aircraft);
    void aircraftUpdateded(FgAircraft* aircraft);
};

#endif // FGCONTROLLER_H
