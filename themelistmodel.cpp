#include "themelistmodel.h"

ThemeListModel::ThemeListModel(QObject *parent) : QAbstractListModel(parent)
{
    initThemeData();
}

int ThemeListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_themeData.count();
}

QVariant ThemeListModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role);
    const int row = index.row();
    return m_themeData[row];
}

void ThemeListModel::initThemeData()
{
    m_themeData.append(QStringList
    {
        "aci",
        "aco",
        "argonaut",
        "azu",
        "bim",
        "breeze",
        "cai",
        "chalk",
        "deepin",
        "dracula",
        "elementary",
        "elic",
        "elio",
        "empathy",
        "flat",
        "freya",
        "gruvbox dark",
        "gruvbox light",
        "hemisu dark",
        "hemisu light",
        "hybrid",
        "jup",
        "mar",
        "material",
        "miu",
        "monokai dark",
        "nep",
        "ocean dark",
        "one dark",
        "one light",
        "pali",
        "peppermint",
        "sat",
        "shel",
        "smyck",
        "solarized dark",
        "solarized light",
        "tango",
        "tin",
        "tomorrow",
        "tomorrow night",
        "tomorrow night blue",
        "tomorrow night bright",
        "tomorrow night eighties",
        "ura",
        "vag",
        "white wind"
    });
}
