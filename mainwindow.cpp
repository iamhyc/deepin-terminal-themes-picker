#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dlghelp.h"

#include <QMessageBox>

#include <DTitlebar>
#include <DLabel>
#include <DListWidget>
#include <DApplicationHelper>
#include <QFile>

#include <QColorDialog>

#include <QProcess>
#include <QStringList>
#include <QTemporaryFile>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    DMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setAttribute(Qt::WA_TranslucentBackground);
    DTitlebar *titlebar = this->titlebar();

    if (titlebar)
    {
        titlebar->setMenu(new QMenu(titlebar));
        titlebar->setSeparatorVisible(true);
        auto actAboutAuth = titlebar->menu()->addAction(tr("About Author"));
        connect(actAboutAuth, &QAction::triggered, this, [&]
        {
            QMessageBox::information(this, tr("Information"), tr("This person is lazy and didn't write anything..."));
        });
        titlebar->menu()->addSeparator();
        auto actHelp = titlebar->menu()->addAction(tr("Help"));
        connect(actHelp, &QAction::triggered, this, [&]
        {
            DlgHelp help(this);
            help.exec();
        });

        titlebar->menu()->addSeparator();
        //connect(titlebar->menu(), &QMenu::triggered, this, &MainWindow::onMenuClicked);

        titlebar->setDisableFlags(Qt::WindowMinimizeButtonHint
                                  | Qt::WindowMaximizeButtonHint
                                  | Qt::WindowSystemMenuHint);
        titlebar->setAutoHideOnFullscreen(true);
    }

    setCentralWidget(ui->centralwidget);

    connect(ui->frameThemes, &ThemePanel::themeChanged, this, &MainWindow::onThemeChanged);

    m_btnBindLabel.clear();

    m_btnBindLabel.insert(ui->btnSetForeground, ui->lblForeground);
    m_btnBindLabel.insert(ui->btnSetBackground, ui->lblBackground);
    m_btnBindLabel.insert(ui->btnSetColor1, ui->lblColor1);
    m_btnBindLabel.insert(ui->btnSetColor2, ui->lblColor2);
    m_btnBindLabel.insert(ui->btnSetColor3, ui->lblColor3);
    m_btnBindLabel.insert(ui->btnSetColor4, ui->lblColor4);
    m_btnBindLabel.insert(ui->btnSetColor5, ui->lblColor5);
    m_btnBindLabel.insert(ui->btnSetColor6, ui->lblColor6);
    m_btnBindLabel.insert(ui->btnSetColor7, ui->lblColor7);
    m_btnBindLabel.insert(ui->btnSetColor8, ui->lblColor8);

    foreach (DPushButton *btn, m_btnBindLabel.keys())
    {
        connect(btn, &DPushButton::clicked, this, &MainWindow::onSelectColor);
    }

    setFixedSize(1024, 768);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPalette MainWindow::getPalette(QString szColor)
{
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(szColor));
    return palette;
}

QStringList MainWindow::color2str(QColor color)
{
    QStringList ret;
    ret << QString::number(color.red());
    ret << QString::number(color.green());
    ret << QString::number(color.blue());
    return ret;
}

void MainWindow::onMenuClicked(QAction *)
{

}

void MainWindow::onThemeChanged(QString themeName)
{
    QString szThemeFile = QString(":/themes/themes/%1").arg(themeName);
    QSettings themeSetting(szThemeFile, QSettings::IniFormat);

    ui->lblForeground->setAutoFillBackground(true);
    ui->lblBackground->setAutoFillBackground(true);
    ui->lblColor1->setAutoFillBackground(true);
    ui->lblColor2->setAutoFillBackground(true);
    ui->lblColor3->setAutoFillBackground(true);
    ui->lblColor4->setAutoFillBackground(true);
    ui->lblColor5->setAutoFillBackground(true);
    ui->lblColor6->setAutoFillBackground(true);
    ui->lblColor7->setAutoFillBackground(true);
    ui->lblColor8->setAutoFillBackground(true);

    ui->lblForeground->setPalette(getPalette(themeSetting.value("theme/foreground", "white").toString()));
    ui->lblBackground->setPalette(getPalette(themeSetting.value("theme/background", "black").toString()));
    ui->lblColor1->setPalette(getPalette(themeSetting.value("theme/color_1", "black").toString()));
    ui->lblColor2->setPalette(getPalette(themeSetting.value("theme/color_2", "black").toString()));
    ui->lblColor3->setPalette(getPalette(themeSetting.value("theme/color_3", "black").toString()));
    ui->lblColor4->setPalette(getPalette(themeSetting.value("theme/color_4", "black").toString()));
    ui->lblColor5->setPalette(getPalette(themeSetting.value("theme/color_5", "black").toString()));
    ui->lblColor6->setPalette(getPalette(themeSetting.value("theme/color_6", "black").toString()));
    ui->lblColor7->setPalette(getPalette(themeSetting.value("theme/color_7", "black").toString()));
    ui->lblColor8->setPalette(getPalette(themeSetting.value("theme/color_8", "black").toString()));
}

void MainWindow::onSelectColor()
{
    DPushButton *btn = qobject_cast<DPushButton *>(sender());
    if (btn && m_btnBindLabel[btn])
    {
        QColor newColor = QColorDialog::getColor(m_btnBindLabel[btn]->palette().color(QPalette::Background),
                          this, tr("Select New Color"));
        if (newColor.isValid())
        {
            m_btnBindLabel[btn]->setPalette(QPalette(QPalette::Background, newColor));
        }
    }
}

void MainWindow::on_btnSetTheme_clicked()
{
    QString szThemeName = "Dark";
    switch (DApplicationHelper::instance()->themeType())
    {
        case DApplicationHelper::LightType:
            szThemeName = "Light";
            break;
        case DApplicationHelper::DarkType:
        default:
            szThemeName = "Dark";
            break;
    }

    QTemporaryFile tmp_file( QString("terminalwidget5") );
    if ( tmp_file.open() ) {
        QProcess process;
        process.setEnvironment(QProcess::systemEnvironment());
        QSettings setting( tmp_file.fileName(), QSettings::IniFormat );

        {
            setting.setValue("Background/Bold", true);
            setting.setValue("Background/Color", color2str(ui->lblBackground->palette().color(QPalette::Background)));
            setting.setValue("Background/Transparency", false);

            setting.setValue("BackgroundIntense/Bold", true);
            setting.setValue("BackgroundIntense/Color", color2str(ui->lblBackground->palette().color(QPalette::Background)));
            setting.setValue("BackgroundIntense/Transparency", false);

            setting.setValue("Foreground/Bold", true);
            setting.setValue("Foreground/Color", color2str(ui->lblForeground->palette().color(QPalette::Background)));
            setting.setValue("Foreground/Transparency", false);

            setting.setValue("ForegroundIntense/Bold", true);
            setting.setValue("ForegroundIntense/Color", color2str(ui->lblForeground->palette().color(QPalette::Background)));
            setting.setValue("ForegroundIntense/Transparency", false);

            setting.setValue("Color0/Bold", true);
            setting.setValue("Color0/Color", color2str(ui->lblColor1->palette().color(QPalette::Background)));
            setting.setValue("Color0/Transparency", false);

            setting.setValue("Color0Intense/Bold", true);
            setting.setValue("Color0Intense/Color", color2str(ui->lblColor1->palette().color(QPalette::Background)));
            setting.setValue("Color0Intense/Transparency", false);

            setting.setValue("Color1/Bold", true);
            setting.setValue("Color1/Color", color2str(ui->lblColor2->palette().color(QPalette::Background)));
            setting.setValue("Color1/Transparency", false);

            setting.setValue("Color1Intense/Bold", true);
            setting.setValue("Color1Intense/Color", color2str(ui->lblColor2->palette().color(QPalette::Background)));
            setting.setValue("Color1Intense/Transparency", false);

            setting.setValue("Color2/Bold", true);
            setting.setValue("Color2/Color", color2str(ui->lblColor3->palette().color(QPalette::Background)));
            setting.setValue("Color2/Transparency", false);

            setting.setValue("Color2Intense/Bold", true);
            setting.setValue("Color2Intense/Color", color2str(ui->lblColor3->palette().color(QPalette::Background)));
            setting.setValue("Color2Intense/Transparency", false);

            setting.setValue("Color3/Bold", true);
            setting.setValue("Color3/Color", color2str(ui->lblColor4->palette().color(QPalette::Background)));
            setting.setValue("Color3/Transparency", false);

            setting.setValue("Color3Intense/Bold", true);
            setting.setValue("Color3Intense/Color", color2str(ui->lblColor4->palette().color(QPalette::Background)));
            setting.setValue("Color3Intense/Transparency", false);

            setting.setValue("Color4/Bold", true);
            setting.setValue("Color4/Color", color2str(ui->lblColor5->palette().color(QPalette::Background)));
            setting.setValue("Color4/Transparency", false);

            setting.setValue("Color4Intense/Bold", true);
            setting.setValue("Color4Intense/Color", color2str(ui->lblColor5->palette().color(QPalette::Background)));
            setting.setValue("Color4Intense/Transparency", false);

            setting.setValue("Color5/Bold", true);
            setting.setValue("Color5/Color", color2str(ui->lblColor6->palette().color(QPalette::Background)));
            setting.setValue("Color5/Transparency", false);

            setting.setValue("Color5Intense/Bold", true);
            setting.setValue("Color5Intense/Color", color2str(ui->lblColor6->palette().color(QPalette::Background)));
            setting.setValue("Color5Intense/Transparency", false);

            setting.setValue("Color6/Bold", true);
            setting.setValue("Color6/Color", color2str(ui->lblColor7->palette().color(QPalette::Background)));
            setting.setValue("Color6/Transparency", false);

            setting.setValue("Color6Intense/Bold", true);
            setting.setValue("Color6Intense/Color", color2str(ui->lblColor7->palette().color(QPalette::Background)));
            setting.setValue("Color6Intense/Transparency", false);

            setting.setValue("Color7/Bold", true);
            setting.setValue("Color7/Color", color2str(ui->lblColor8->palette().color(QPalette::Background)));
            setting.setValue("Color7/Transparency", false);

            setting.setValue("Color7Intense/Bold", true);
            setting.setValue("Color7Intense/Color", color2str(ui->lblColor8->palette().color(QPalette::Background)));
            setting.setValue("Color7Intense/Transparency", false);

            setting.setValue("General/Description", QString("Deepin Terminal %1 Mode Color").arg(szThemeName));
            setting.setValue("General/Opacity", 1);
        }
        setting.sync();
        
        process.start("pkexec",
            QStringList() <<"--user"<<"root" <<"cp"<<"-f"<<tmp_file.fileName()<<QString("/usr/share/terminalwidget5/color-schemes/%1.colorscheme").arg(szThemeName)
        );
        process.waitForFinished();
        process.close();
        if ( process.exitCode()==0 ) {
            QMessageBox::information(this, tr("Success"), tr("Save %1 mode theme success! \n"
                "Quit all <deepin-terminal> processes, and restart the deepin-terminal!")
                .arg(szThemeName == "Light" ? tr("Light") : tr("Dark")));
            return;
        }
    }

    QMessageBox::information(this, tr("Fail"), tr("Save %1 mode theme fail! \n"
        "Please check your permissions!")
        .arg(szThemeName == "Light" ? tr("Light") : tr("Dark")));
}

void MainWindow::on_btnRestore_clicked()
{
    QString szThemeName = "Dark";
    switch (DApplicationHelper::instance()->themeType())
    {
        case DApplicationHelper::LightType:
            szThemeName = "Light";
            break;
        case DApplicationHelper::DarkType:
        default:
            szThemeName = "Dark";
            break;
    }

    QString defaultConfig = QString(":/themesDefault/themesDefault/%1.colorscheme").arg(szThemeName);
    QString targetConfig = QString("/usr/share/terminalwidget5/color-schemes/%1.colorscheme")
                           .arg(szThemeName);
    QFile fSrc(defaultConfig);
    QFile fDst(targetConfig);

    if (fSrc.open(QIODevice::ReadOnly | QIODevice::Text) &&
        fDst.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        fDst.write(fSrc.readAll());
        fSrc.close();
        fDst.close();

        QMessageBox::information(this, tr("Success"), tr("Restore %1 mode theme success! \n"
                                 "Quit all <deepin-terminal> processes, and restart the deepin-terminal!")
                                 .arg(szThemeName == "Light" ? tr("Light") : tr("Dark")));
    }
    else
    {
        QMessageBox::information(this, tr("Fail"), tr("Restore %1 mode theme fail! \n"
                                 "Please check your permissions!")
                                 .arg(szThemeName == "Light" ? tr("Light") : tr("Dark")));
    }
}
