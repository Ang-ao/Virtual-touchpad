#pragma once
#ifndef __V_TOUCHPAD__H
#define __V_TOUCHPAD__H

#include <QWidget>
#include <QPaintEvent>
#include <QShowEvent>
#include <QHideEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainterPath>
#include <QPoint>
#include <QMouseEvent>
#include <QKeyEvent>

#include "mouseType.h"
#include "MovieLabel.h"

class Vtouchpad : public QWidget
{
    Q_OBJECT
public:
    explicit Vtouchpad(QWidget* parent = Q_NULLPTR);
    ~Vtouchpad() override = default;

protected:
    void paintEvent(QPaintEvent* event) override;
    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

signals:
    void upDateMouse(QPoint);
    void setMouse(QPoint);
    void sendMouse(QPoint, mouseType);

private:
    QMovie* mvGif_;
    MovieLabel* mvLabel_;

    bool isDrag_;
    bool canMove_;
    QPoint mousePoint_;
    QPoint windowPoint_;
};

#endif // __V_TOUCHPAD__H
