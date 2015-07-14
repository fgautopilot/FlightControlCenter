/*!
 * @file aircraftwidget.h
 *
 * @brief Custom widget to represent an autopilot panel
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 14, 2015
 * @date Modified Jul 14, 2015
 */

#ifndef AUTOPILOTWIDGET_H
#define AUTOPILOTWIDGET_H

#include <QWidget>

class QQmlEngine;
class QQmlComponent;
class QQuickWindow;
class QVBoxLayout;
class QQmlContext;

class AutopilotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AutopilotWidget(QWidget *parent = 0);

private:
    AutopilotWidget(const AutopilotWidget& other);
    AutopilotWidget& operator=(const AutopilotWidget& other);

    QQmlEngine    *engine  { nullptr };
    QQmlComponent *qmlView { nullptr };
    QQuickWindow  *window  { nullptr };
    QVBoxLayout   *layout  { nullptr };
    QQmlContext   *Root    { nullptr };

signals:

public slots:
};

#endif // AUTOPILOTWIDGET_H
