#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    QWidget parentWidget;
    QVBoxLayout *layout = new QVBoxLayout(&parentWidget);
    parentWidget.showFullScreen();

    Widget widget(argc > 1 ? argv[1] : "");
    layout->addWidget(&widget);

    parentWidget.show();

    return application.exec();
}
