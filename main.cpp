#include "configcreator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConfigCreator w;
    w.show();
    
    return a.exec();
}
