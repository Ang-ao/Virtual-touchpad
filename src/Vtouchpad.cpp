#include "Vtouchpad.h"

Vtouchpad::Vtouchpad(QWidget* parent)
    : QWidget(parent)
    , mvGif_(new QMovie(":/test00.png"))
    , mvLabel_(new MovieLabel(this))
    , isDrag_(false)
    , canMove_(false)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    // this->mvLabel_->setFixedSize(400, 400);
    // this->mvLabel_->setWindowFlags(Qt::FramelessWindowHint);
    // this->mvLabel_->setAttribute(Qt::WA_TranslucentBackground);
    this->mvLabel_->setMovie(this->mvGif_);

    auto layout = new QHBoxLayout;
    layout->addWidget(this->mvLabel_);

    this->setLayout(layout);
}

void Vtouchpad::showEvent(QShowEvent *event)
{
    this->mvGif_->start();

    return QWidget::showEvent(event);
}

void Vtouchpad::hideEvent(QHideEvent *event)
{
    this->mvGif_->stop();

    return QWidget::hideEvent(event);
}

void Vtouchpad::paintEvent(QPaintEvent *event)
{
    /*
    QRect rect(this->mvLabel_->pos(), this->mvLabel_->size());

    QRegion rg1(0, 0, this->width(), rect.y());
    QRegion rg2(0, rect.bottom() + 1, this->width(), this->height() - rect.bottom() - 1);
    QRegion rg3(0, rect.y(), rect.x(), rect.height());
    QRegion rg4(rect.right() + 1, rect.y(), this->width() - rect.left() - 1, rect.height());

    QPainterPath path;
    path.addRegion(rg1);
    path.addRegion(rg2);
    path.addRegion(rg3);
    path.addRegion(rg4);

    QPainter painter(this);
    painter.fillPath(path, QColor(255, 255, 255, 255 / 2));
    */
}

void Vtouchpad::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton and this->canMove_)
    {
        this->isDrag_ = true;
        this->mousePoint_ = event->globalPos();
        this->windowPoint_ = this->frameGeometry().topLeft();
    }
    emit setMouse(event->pos());

    return QWidget::mousePressEvent(event);
}

void Vtouchpad::mouseMoveEvent(QMouseEvent *event)
{
    if(this->isDrag_)
    {
        auto distance = event->globalPos() - this->mousePoint_;
        this->move(this->windowPoint_ + distance);
    }
    emit upDateMouse(event->pos());

    return QWidget::mouseMoveEvent(event);
}

void Vtouchpad::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        this->isDrag_ = false;
    }

    return QWidget::mouseReleaseEvent(event);
}

void Vtouchpad::keyPressEvent(QKeyEvent *event)
{
    auto pos = this->cursor().pos();

    if(event->key() == Qt::Key_Control)
    {
        this->canMove_ = true;
    }

    if(event->key() == Qt::Key_J)
    {
        emit sendMouse(pos, mouseType::LEFT_CLICK_TYPE);
    }
    else if(event->key() == Qt::Key_K)
    {
        emit sendMouse(pos, mouseType::RIGHT_CLICK_TYPE);
    }
    else if(event->key() == Qt::Key_L)
    {
        emit sendMouse(pos, mouseType::DOUBLE_CLICK_TYPE);
    }

    return QWidget::keyPressEvent(event);
}

void Vtouchpad::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Control)
    {
        this->canMove_ = false;
    }

    return QWidget::keyReleaseEvent(event);
}