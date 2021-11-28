#include "mainwindow.h"

#include <unistd.h>

#include <DApplication>
#include <DAboutDialog>

#include <QMessageBox>
#include <QTranslator>

int main(int argc, char *argv[])
{
    DApplication a(argc, argv);
    a.loadTranslator();

    QTranslator translator;
    QLocale locale;
    if (locale.language() == QLocale::Chinese)
    {
        translator.load(QString(":/common/deepin-terminal-themes_zh_CN.qm"));
        a.installTranslator(&translator);
    }

    a.setProductName(QObject::tr("Deepin Terminal Themes Changer"));
    a.setApplicationHomePage("http://www.hxhlb.org");
    a.setApplicationName(QObject::tr("Deepin Terminal Themes Changer"));
    a.setApplicationVersion("V 1.0");
    a.setApplicationDisplayName(QObject::tr("Deepin Terminal Themes Changer"));
    a.setApplicationDescription("Modified by sudo_free.");

    // if (geteuid())
    // {
    //     QMessageBox::critical(nullptr, QObject::tr("Error"),
    //                           QObject::tr("This program need RUN AS ROOT!!!\n"
    //                                       "Please use the command: \n\n"
    //                                       "sudo %1")
    //                           .arg(argv[0]));
    //     return 0;
    // }

    MainWindow w;
    w.show();
    return a.exec();
}
