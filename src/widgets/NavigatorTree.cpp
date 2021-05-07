#include "NavigatorTree.hpp"
#include "utils/StringFormatting.hpp"

#include <QMetaEnum>

NavigatorTree::NavigatorTree(QWidget * parent)
    : QTreeWidget { parent }
{
    _initView();
    _setupConnections();
}

auto NavigatorTree::addUser()
    -> NavigatorTree::Error
{
    return NoError;
}

void NavigatorTree::_initView()
{
    setIconSize({ 25, 25 });

    // Setup root nodes
    auto const typeEnum = _getTypeMetaEnum();
    auto typeCount = typeEnum.keyCount();
    for (auto typeIdx = 0; typeIdx < typeCount; ++typeIdx)
    {
        QString const displayName { _getTypeMetaEnum().key(typeIdx) };
        auto const iconPath = ":/icons/%1.svg"_s % displayName.toLower();

        auto typeItem = new QTreeWidgetItem(this, { displayName });
        if (QFile::exists(iconPath))
            typeItem->setIcon(0, QIcon(iconPath));

        typeItem->addChild(new QTreeWidgetItem(typeItem, { "Child of "_s % displayName }));

        addTopLevelItem(typeItem);
    }

    selectionModel()->select(model()->index(0, 0),
                             QItemSelectionModel::SelectionFlag::Select);
}

void NavigatorTree::_setupConnections()
{
}

auto NavigatorTree::_getTypeMetaEnum()
    -> QMetaEnum
{
    return QMetaEnum::fromType<NavigatorTree::Type>();
}
