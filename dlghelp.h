#ifndef DLGHELP_H
#define DLGHELP_H

#include <DDialog>

namespace Ui
{
    class DlgHelp;
}

DWIDGET_USE_NAMESPACE

class DlgHelp : public DDialog
{
    Q_OBJECT

public:
    explicit DlgHelp(QWidget *parent = nullptr);
    ~DlgHelp();

private:
    Ui::DlgHelp *ui;
};

#endif // DLGHELP_H
