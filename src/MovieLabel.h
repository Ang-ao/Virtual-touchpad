#pragma once
#ifndef __MOVICE_LABEL__H
#define __MOVICE_LABEL__H

#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
#include <QStyle>
#include <QMovie>

class MovieLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MovieLabel(QWidget* parent = Q_NULLPTR)
    : QLabel(parent)
    { }

protected:
    void paintEvent(QPaintEvent* event) override
    {
        auto style = QWidget::style();
        QPainter painter(this);
        painter.setOpacity(0.6);
        // drawFrame(&painter);
        auto cr = this->contentsRect();
        cr.adjust(this->margin(), this->margin(), -this->margin(), -this->margin());
        auto align = QStyle::visualAlignment(this->text() == "" ? Qt::LeftToRight : this->layoutDirection(), this->alignment());

        if(this->movie())
        {
            if(this->hasScaledContents())
            {
                style->drawItemPixmap(&painter, cr, static_cast<int>(align), this->movie()->currentPixmap().scaled(cr.size()));
            }
            else
            {
                style->drawItemPixmap(&painter, cr, static_cast<int>(align), this->movie()->currentPixmap());
            }
        }
        painter.setBrush(QColor(0, 0, 0, 0));
        // painter.drawRoundedRect(this->rect(), 23, 23);
    }
};

#endif // __MOVICE_LABEL__H
