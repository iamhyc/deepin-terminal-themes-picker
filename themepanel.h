#ifndef THEMEPANEL_H
#define THEMEPANEL_H

#include <DFrame>

class ThemeListView;
class ThemeListModel;

DWIDGET_USE_NAMESPACE

class ThemePanel : public DFrame
{
    Q_OBJECT
public:
    explicit ThemePanel(QWidget *parent = nullptr);

signals:
    void themeChanged(const QString themeName);

private:
    ThemeListView *m_themeView = nullptr;
    ThemeListModel *m_themeModel = nullptr;
};

#endif  // THEMEPANEL_H
