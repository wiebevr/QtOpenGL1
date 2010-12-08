#include <QApplication>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    Widget widget(argc > 1 ? argv[1] : "");
    widget.show();

    return application.exec();
}
