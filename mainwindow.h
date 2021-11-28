#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include "dwidgetstype.h"

namespace Ui
{
    class MainWindow;
}

DWIDGET_USE_NAMESPACE

DWIDGET_BEGIN_NAMESPACE
class DLabel;
DWIDGET_END_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QPalette getPalette(QString);
    QStringList color2str(QColor);

private slots:
    void onMenuClicked(QAction *);
    void onThemeChanged(QString);

    void onSelectColor();

    void on_btnSetTheme_clicked();
    void on_btnRestore_clicked();

private:
    Ui::MainWindow *ui;

    QMap<DPushButton *, DLabel *> m_btnBindLabel;
};

#endif // MAINWINDOW_H
