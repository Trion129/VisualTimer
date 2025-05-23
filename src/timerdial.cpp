#include "timerdial.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QSizeF>
#include <QStyleOption>
#include <QDateTime>
#include <QMessageLogger>

TimerDial::TimerDial(QGraphicsItem *parent)
    : QGraphicsItem(parent),
      m_dialColor(Qt::lightGray),
      m_remainingColor(Qt::red),
      m_handleColor(Qt::darkRed),
      m_maxAngle(360.0),
      m_currentAngle(150.0), // Start at 25m
      m_remainingAngle(150.0), // Same here
      m_maxTime(3600),
      m_currentTime(0),
      m_isRunning(false),
      m_isDragging(false),
      m_lastUpdateTime(0)
{
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &TimerDial::updateTimer);

    updateTime();
}

TimerDial::~TimerDial()
{
    if (m_timer) {
        m_timer->stop();
        delete m_timer;
    }
}

QRectF TimerDial::boundingRect() const
{
    return QRectF(-DIAL_SIZE/2, -DIAL_SIZE/2, DIAL_SIZE, DIAL_SIZE);
}

void TimerDial::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    
    painter->setRenderHint(QPainter::Antialiasing);
    
    // Draw background dial
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_dialColor);
    painter->drawEllipse(boundingRect());
    
    // Draw remaining time pie
    painter->setBrush(m_remainingColor);
    painter->drawPie(boundingRect(), 90 * 16, -m_remainingAngle * 16);
    
    // Draw center
    painter->setBrush(Qt::white);
    painter->drawEllipse(QPointF(0, 0), 8, 8);
    
    // Draw minute ticks - always use 5-minute intervals
    painter->setPen(QPen(Qt::black, 1));
    
    // Calculate how many minutes to display based on max time
    int maxMinutes = m_maxTime / 60;
    
    // Draw tick marks every 5 minutes
    for (int i = 0; i < maxMinutes; i += 5) {
        qreal angle = (i * 60.0 / m_maxTime) * 360.0;
        
        // Different tick lengths
        int tickLength = 10;
        QPointF outer = angleToPoint(angle, DIAL_SIZE/2);
        QPointF inner = angleToPoint(angle, DIAL_SIZE/2 - tickLength);
        
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(outer, inner);
        
        // Add minute labels for all 5-minute intervals
        QPointF textPos = angleToPoint(angle, DIAL_SIZE/2 - 25);
        
        QFont smallerFont = painter->font();
        smallerFont.setPointSize(8);
        painter->setFont(smallerFont);
        
        // Adjust text alignment based on position around the dial
        QFontMetrics fm(smallerFont);
        int textWidth = fm.horizontalAdvance(QString::number(i));
        int textHeight = fm.height();
        
        // Calculate horizontal and vertical alignment adjustments
        qreal angleRad = (angle - 90) * M_PI / 180.0;
        qreal cosAngle = qCos(angleRad);
        qreal sinAngle = qSin(angleRad);
        int xOffset = -textWidth/2 + (cosAngle * textWidth/2);
        int yOffset = textHeight/4 + (sinAngle * textHeight/2);
        
        painter->drawText(textPos.x() + xOffset, textPos.y() + yOffset, QString::number(i));
    }
    
    // Special case for 60 (avoid overlap with 0) - more compact
    if (maxMinutes >= 60) {
        QPointF textPos = angleToPoint(0, DIAL_SIZE/2 - 38);
        painter->drawText(textPos.x() - 12, textPos.y(), "60");
    }
    
    // Draw handle at current position - smaller for compact display
    QPointF handlePos = angleToPoint(m_currentAngle, DIAL_SIZE/2 - 5);
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_handleColor);
    painter->drawEllipse(handlePos, 4, 4);
}

void TimerDial::startTimer()
{
    if (!m_isRunning && m_currentTime > 0) {
        m_isRunning = true;
        m_lastUpdateTime = QDateTime::currentMSecsSinceEpoch();
        m_timer->start(UPDATE_INTERVAL_MS);
    }
}

void TimerDial::pauseTimer()
{
    if (m_isRunning) {
        m_isRunning = false;
        m_timer->stop();
    }
}

void TimerDial::stopTimer()
{
    if (m_isRunning) {
        m_isRunning = false;
        m_timer->stop();
    }
}

void TimerDial::resetTimer()
{
    stopTimer();
    m_currentTime = angleToTime(m_currentAngle);
    m_remainingAngle = m_currentAngle;
    updateTime();
    update();
}

int TimerDial::getCurrentTime() const
{
    return m_currentTime;
}

void TimerDial::setMaxTime(int seconds)
{
    m_maxTime = seconds;
    updateTime();
    update();
}

int TimerDial::getMaxTime() const
{
    return m_maxTime;
}

bool TimerDial::isRunning() const
{
    return m_isRunning;
}

void TimerDial::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QPointF mousePos = event->pos();
        qreal angle = qAtan2(mousePos.x(), -mousePos.y()) * 180 / M_PI;
        
        if (angle < 0) 
            angle += 360;

        if (QLineF(QPointF(0, 0), mousePos).length() <= DIAL_SIZE/2) {
            m_isDragging = true;
            m_currentAngle = angle;
            
            // Snap to 5-minute intervals
            int seconds = angleToTime(m_currentAngle);
            int fiveMinIntervals = qRound(seconds / 300.0); // 5 minutes = 300 seconds
            m_currentAngle = timeToAngle(fiveMinIntervals * 300);
            m_remainingAngle = m_currentAngle;
            
            updateTime();
            update();
        }
    }
    QGraphicsItem::mousePressEvent(event);
}

void TimerDial::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_isDragging) {
        QPointF mousePos = event->pos();
        qreal angle = qAtan2(mousePos.x(), -mousePos.y()) * 180 / M_PI;
        
        if (angle < 0) 
            angle += 360;
        m_currentAngle = angle;
        
        // Snap to 5-minute intervals
        int seconds = angleToTime(m_currentAngle);
        int fiveMinIntervals = qRound(seconds / 300.0); // 5 minutes = 300 seconds
        m_currentAngle = timeToAngle(fiveMinIntervals * 300);
        m_remainingAngle = m_currentAngle;
        
        updateTime();
        update();
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void TimerDial::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isDragging = false;
    }
    QGraphicsItem::mouseReleaseEvent(event);
}

qreal TimerDial::angleToTime(qreal angle) const
{
    qreal rawSeconds = (angle / 360.0) * m_maxTime;
    
    // Round to the nearest 5 minutes when setting via drag
    if (m_isDragging) {
        int fiveMinIntervals = qRound(rawSeconds / 300.0); // 300 seconds = 5 minutes
        return fiveMinIntervals * 300.0;
    } else {
        // Keep precision when not dragging (for countdown)
        return rawSeconds;
    }
}

qreal TimerDial::timeToAngle(int seconds) const
{
    // Convert time to angle in degrees
    return (static_cast<qreal>(seconds) / m_maxTime) * 360.0;
}

void TimerDial::updateTime()
{
    m_currentTime = angleToTime(m_remainingAngle);
    emit timeUpdated(m_currentTime);
}

QPointF TimerDial::angleToPoint(qreal angle, qreal radius) const
{
    // Convert angle in degrees to radians (0 degrees is at 3 o'clock)
    qreal angleRad = (angle - 90) * M_PI / 180.0;
    qreal x = radius * qCos(angleRad);
    qreal y = radius * qSin(angleRad);
    return QPointF(x, y);
}

void TimerDial::updateTimer()
{
    if (!m_isRunning || m_currentTime <= 0) 
        return;
        
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    qreal elapsedSeconds = (currentTime - m_lastUpdateTime) / 1000.0;
    m_currentTime -= 1.0;
    m_lastUpdateTime = currentTime;
    if (m_currentTime <= 0) {
        m_currentTime = 0;
        m_remainingAngle = 0;
        stopTimer();
        emit timerFinished();
    } else {
        m_remainingAngle = (static_cast<qreal>(m_currentTime) / m_maxTime) * 360.0;
    }
    
    emit timeUpdated(m_currentTime);
    update();
}
