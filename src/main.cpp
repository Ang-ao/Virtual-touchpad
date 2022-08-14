#include <QApplication>
#include "Vtouchpad.h"
#include "VMouse.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Vtouchpad vtp;
    vtp.show();

    VMouse vm;
    vm.show();

    QObject::connect(&vtp, SIGNAL(upDateMouse(QPoint)),
                     &vm, SLOT(upDateAxes(QPoint)));
    QObject::connect(&vtp, SIGNAL(setMouse(QPoint)),
                     &vm, SLOT(setAxes(QPoint)));
    QObject::connect(&vtp, SIGNAL(sendMouse(QPoint, mouseType)),
                     &vm, SLOT(doMouseActs(QPoint, mouseType)));

    return app.exec();
}
