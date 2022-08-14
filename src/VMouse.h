#pragma once
#ifndef __V_MOUSE__H
#define __V_MOUSE__H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPoint>
#include <QMovie>
#include <QShowEvent>
#include <QHideEvent>

namespace win
{
#include <windows.h>
};

#include "mouseType.h"
#include "MovieLabel.h"

class VMouse : public QDialog
{
    Q_OBJECT
public:
    explicit VMouse(QWidget* parent = Q_NULLPTR)
    : QDialog(parent)
    , mvIcon_(new QMovie(":/test01.png"))
    , mvLabel_(new MovieLabel(this))
    {
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
        this->setAttribute(Qt::WA_TranslucentBackground);

        this->mvLabel_->setMovie(this->mvIcon_);

        auto layout = new QVBoxLayout;
        layout->addWidget(this->mvLabel_);

        this->setLayout(layout);
    }

protected:
    void showEvent(QShowEvent *event) override
    {
        this->mvIcon_->start();

        return QDialog::showEvent(event);
    }

    void hideEvent(QHideEvent *event) override
    {
        this->mvIcon_->stop();

        return QDialog::hideEvent(event);
    }

private slots:
    void upDateAxes(QPoint pos)
    {
        auto oldPos = this->frameGeometry().topLeft();
        auto distance = pos - this->mousePoint_;
        auto newPos = oldPos + distance * 0.1;

        this->move(newPos);
    }

    void setAxes(QPoint pos)
    {
        this->mousePoint_ = pos;
    }

    void doMouseActs(QPoint oldPos, mouseType typeId)
    {
        auto pos = this->frameGeometry().topLeft();

        int x = pos.x() + 12;
        int y = pos.y() + 12;

        win::SetCursorPos(x, y);
        switch(typeId)
        {
            case mouseType::DOUBLE_CLICK_TYPE:
            {
                win::mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
                win::mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP, x, y, 0, 0);
            }
            case mouseType::LEFT_CLICK_TYPE:
            {
                win::mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
                win::mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP, x, y, 0, 0);
            } break;
            case mouseType::RIGHT_CLICK_TYPE:
            {
                win::mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTDOWN, x, y, 0, 0);
                win::mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTUP, x, y, 0, 0);
            } break;

            default:
                break;
        }

        win::SetCursorPos(oldPos.x(), oldPos.y());
        win::mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN, oldPos.x(), oldPos.y(), 0, 0);
        win::mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP, oldPos.x(), oldPos.y(), 0, 0);
    }

private:
    QPoint mousePoint_;

    QMovie* mvIcon_;
    MovieLabel* mvLabel_;
};


#endif // __V_MOUSE__H
