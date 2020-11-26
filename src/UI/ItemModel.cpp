/*
 * @name BookFiler Library - Sort Filter Tree Widget
 * @author Branden Lee
 * @version 1.00
 * @license MIT
 * @brief sqlite3 based tree widget.
 */

/* QT 5.13.2
 * License: LGPLv3
 */
#include <QStringList>

// Local Project
#include "ItemModel.hpp"

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {

TableItemModel::TableItemModel(QObject *parent) : QAbstractItemModel(parent) {
  rootItem = new TableItem({tr("Name"), tr("Value")});
}

TableItemModel::~TableItemModel() { delete rootItem; }

/* Custom methods
 *
 *
 *
 *
 */

void TableItemModel::addData(std::shared_ptr<sqlite3> database, std::string tableName,
                          std::string idColumn, std::string parentColumn) {
  // TODO: set data
}

/* Base methods for the view
 *
 *
 *
 */

int TableItemModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return static_cast<TableItem *>(parent.internalPointer())->columnCount();
  return rootItem->columnCount();
}

QVariant TableItemModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  TableItem *item = static_cast<TableItem *>(index.internalPointer());

  // Normal data display
  if (role == Qt::DisplayRole) {
    return item->data(index.column());
  }
  // Data displayed in the edit box
  else if (role == Qt::EditRole) {
    return item->data(index.column());
  }

  // for all else
  return QVariant();
}

Qt::ItemFlags TableItemModel::flags(const QModelIndex &index) const {
  if (!index.isValid())
    return Qt::NoItemFlags;

  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable |
         Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

QVariant TableItemModel::headerData(int section, Qt::Orientation orientation,
                                 int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    return rootItem->data(section);

  return QVariant();
}

QModelIndex TableItemModel::index(int row, int column,
                               const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent))
    return QModelIndex();

  TableItem *parentItem;

  if (!parent.isValid())
    parentItem = rootItem;
  else
    parentItem = static_cast<TableItem *>(parent.internalPointer());

  TableItem *childItem = parentItem->child(row);
  if (childItem)
    return createIndex(row, column, childItem);
  return QModelIndex();
}

QModelIndex TableItemModel::parent(const QModelIndex &index) const {
  if (!index.isValid())
    return QModelIndex();

  TableItem *childItem = static_cast<TableItem *>(index.internalPointer());
  TableItem *parentItem = childItem->parentItem();

  if (parentItem == rootItem)
    return QModelIndex();

  return createIndex(parentItem->row(), 0, parentItem);
}

int TableItemModel::rowCount(const QModelIndex &parent) const {
  TableItem *parentItem;
  if (parent.column() > 0)
    return 0;

  if (!parent.isValid())
    parentItem = rootItem;
  else
    parentItem = static_cast<TableItem *>(parent.internalPointer());

  return parentItem->childCount();
}

bool TableItemModel::setData(const QModelIndex &index, const QVariant &value,
                          int role) {
  if (role) {
    // TODO
  }
  TableItem *item = static_cast<TableItem *>(index.internalPointer());
  item->setData(index.column(), value);
  return true;
}

Qt::DropActions TableItemModel::supportedDropActions() const {
  return Qt::CopyAction | Qt::MoveAction;
}

bool TableItemModel::removeRows(int row, int count, const QModelIndex &parent) {
  TableItem *parentItem = static_cast<TableItem *>(parent.internalPointer());
  parentItem->removeChild(row, count);
  return true;
}

} // namespace widget
} // namespace bookfiler
