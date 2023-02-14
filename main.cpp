#include <QApplication>
#include <QPushButton>
#include "widgetdraw.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    widgetDraw x;
    x.show();
    return a.exec();
}
