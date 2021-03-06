/*!
 * @file FgControlledAircraft.h
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts that under our control
 *
 *
 * Copyright © 2015-2016 Oleksii Aliakin. All rights reserved.
 * Author: Oleksii Aliakin (alex@nls.la)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FGCONTROLLEDAIRCRAFT_H
#define FGCONTROLLEDAIRCRAFT_H

#include "FgAircraft.h"
#include "autopilot/FgAircraftAutopilot.h"
#include "flightgear/FgFlightgear.h"
#include "flightgear/FgTransport.h"
#include "log.h"

#include <QSettings>

#include <memory>

class FgControlledAircraft : public FgAircraft
{
    Q_OBJECT
    Q_PROPERTY(bool autopilotEngaged READ autopilotEngaged)
    Q_PROPERTY(bool flightgearReady READ flightgearReady NOTIFY flightgearReadyChanged)
    Q_PROPERTY(FgTransport *transport READ transport NOTIFY transportChanged)
    Q_PROPERTY(FgFlightgear *flightgear READ flightgear NOTIFY flightgearChanged)
public:
    explicit FgControlledAircraft(QObject *parent = 0);
    virtual ~FgControlledAircraft();

    inline FgAutopilot *autopilot() const;
    inline FgTransport *transport() const;
    inline FgFlightgear *flightgear() const;

    inline bool autopilotEngaged() const;
    inline void setAilerons(qreal val);
    inline void setElevator(qreal val);
    inline void setRudder(qreal val);
    inline bool flightgearReady() const;
    inline void follow(FgAircraft *aircraft);

    bool setConfig(QSettings &settings);
    bool saveConfig(QSettings &settings);

    Q_INVOKABLE void runFlightGear(bool run = true);
    Q_INVOKABLE void autopilotEngage(bool engage = true);

private:
    std::shared_ptr<FgAircraftAutopilot> m_Autopilot{ std::make_shared<FgAircraftAutopilot>(this) };
    std::shared_ptr<FgFlightgear> m_Flightgear{ std::make_shared<FgFlightgear>(this) };

signals:
    void flightgearStarted();
    void flightgearFinished();
    void flightgearReadyChanged(bool);
    void transportChanged();
    void flightgearChanged();

public slots:
    virtual void onFdmDataChanged(FgTransport *transport);
};

bool FgControlledAircraft::autopilotEngaged() const
{
    return m_Autopilot ? m_Autopilot->engaged() : false;
}

FgAutopilot *FgControlledAircraft::autopilot() const
{
    return m_Autopilot.get();
}

FgTransport *FgControlledAircraft::transport() const
{
    return m_Flightgear->transport().get();
}

bool FgControlledAircraft::flightgearReady() const
{
    return m_Flightgear->ready();
}

void FgControlledAircraft::follow(FgAircraft *aircraft)
{
    m_Autopilot->setFollow(aircraft);
    m_Autopilot->set_engaged(true);
}

FgFlightgear *FgControlledAircraft::flightgear() const
{
    return m_Flightgear.get();
}

Q_DECLARE_METATYPE(FgControlledAircraft *)

#endif /* FGCONTROLLEDAIRCRAFT_H */
