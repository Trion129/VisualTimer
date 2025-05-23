#ifndef TIMERDIAL_H
#define TIMERDIAL_H

#include <QGraphicsItem>
#include <QColor>
#include <QTimer>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QtMath>

class TimerDial : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    TimerDial(QGraphicsItem *parent = nullptr);
    ~TimerDial();

    // QGraphicsItem interface implementation
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // Timer control methods
    void startTimer();
    void pauseTimer();
    void stopTimer();
    void resetTimer();
    
    // Get current time in seconds
    int getCurrentTime() const;
    
    // Set maximum time
    void setMaxTime(int seconds);
    int getMaxTime() const;
    
    // Check if timer is running
    bool isRunning() const;

signals:
    void timeUpdated(int secondsRemaining);
    void timerFinished();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    static const int DIAL_SIZE = 180;
    static const int UPDATE_INTERVAL_MS = 1000;
    
    QColor m_dialColor;
    QColor m_remainingColor;
    QColor m_handleColor;
    
    qreal m_maxAngle;        // 360 degrees
    qreal m_currentAngle;    // Set time before start was done.
    qreal m_remainingAngle;  // Time remaining in current cycle.
    
    int m_maxTime;
    int m_currentTime;
    
    bool m_isRunning;
    bool m_isDragging;
    
    QTimer *m_timer;         // Timer for updates
    qint64 m_lastUpdateTime; // Last time the timer was updated
    
    qreal angleToTime(qreal angle) const;
    qreal timeToAngle(int seconds) const;
    void updateTime();
    QPointF angleToPoint(qreal angle, qreal radius) const;

private slots:
    void updateTimer();
};

#endif // TIMERDIAL_H
