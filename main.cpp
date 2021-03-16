#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QTranslator translator;
    // look up e.g. :/i18n/myapp_de.qm
    if (translator.load(QLocale(), QLatin1String("Inventory"), QLatin1String("_"), QLatin1String(":/i18n"))) {
    QCoreApplication::installTranslator(&translator);
    }
    MainWindow w;
    w.show();
    return a.exec();
}
