#ifndef ICONHELPER_H
#define ICONHELPER_H

#include <QPixmap>
#include <QPainter>
#include <QColor>
#include <QPainterPath>

class IconHelper 
{
public:
    static QPixmap createPlayIcon() {
        QPixmap pixmap(48, 48);
        pixmap.fill(Qt::transparent);
        
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        
        // Draw circle background
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(76, 175, 80, 50));  // Light green
        painter.drawEllipse(4, 4, 40, 40);
        
        // Draw play triangle
        QPolygonF triangle;
        triangle << QPointF(16, 12) << QPointF(36, 24) << QPointF(16, 36);
        
        painter.setPen(QPen(QColor(76, 175, 80), 2));
        painter.setBrush(QColor(76, 175, 80));
        painter.drawPolygon(triangle);
        
        return pixmap;
    }
    
    static QPixmap createPauseIcon() {
        QPixmap pixmap(48, 48);
        pixmap.fill(Qt::transparent);
        
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        
        // Draw circle background
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(255, 152, 0, 50));  // Light orange
        painter.drawEllipse(4, 4, 40, 40);
        
        // Draw pause bars
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(255, 152, 0));
        painter.drawRect(16, 12, 6, 24);
        painter.drawRect(26, 12, 6, 24);
        
        return pixmap;
    }
    
    static QPixmap createResetIcon() {
        QPixmap pixmap(48, 48);
        pixmap.fill(Qt::transparent);
        
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        
        // Draw circle background
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(33, 150, 243, 50));  // Light blue background
        painter.drawEllipse(4, 4, 40, 40);
        
        // Draw reset circular arrow
        QPainterPath path;
        
        // Create a circular arc that doesn't close entirely
        painter.setPen(QPen(QColor(33, 150, 243), 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawArc(8, 8, 32, 32, 30 * 16, 300 * 16);
        
        // Draw the arrowhead
        QPolygonF arrowHead;
        arrowHead << QPointF(38, 18) << QPointF(40, 12) << QPointF(34, 15);
        
        painter.setBrush(QColor(33, 150, 243));
        painter.drawPolygon(arrowHead);
        
        return pixmap;
    }
};

#endif // ICONHELPER_H
