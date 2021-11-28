#include "dlghelp.h"
#include "ui_dlghelp.h"


DlgHelp::DlgHelp(QWidget *parent) :
    DDialog(parent),
    ui(new Ui::DlgHelp)
{
    ui->setupUi(this);

    addContent(ui->label, Qt::AlignHCenter | Qt::AlignVCenter);
    setFixedSize(460, 320);
}

DlgHelp::~DlgHelp()
{
    delete ui;
}
