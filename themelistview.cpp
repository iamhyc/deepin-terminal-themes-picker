#include "themelistview.h"

ThemeListView::ThemeListView(QWidget *parent) : QListView(parent)
{
    setVerticalScrollMode(ScrollPerPixel);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void ThemeListView::focusOutEvent(QFocusEvent *event)
{
    emit focusOut();

    QListView::focusOutEvent(event);
}

void ThemeListView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    // Theme changed.
    if (selected.size())
    {
        QModelIndexList list = selected.indexes();
        const QModelIndex &index = list.first();
        const QString &themeName = index.data(1919810).toString();
        emit themeChanged(themeName);
    }
    QListView::selectionChanged(selected, deselected);
}
