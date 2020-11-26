/*
 * @name BookFiler Library - Sort Filter Tree Widget
 * @author Branden Lee
 * @version 1.00
 * @license MIT
 * @brief sqlite3 based tree widget.
 */

 /*
    @brief A container for items of data supplied by the simple tree model.
*/

// C++
#include <iostream>

// Local Project
#include "TableItem.hpp"

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {

TableItem::TableItem(const QVector<QVariant> &data,
                               TableItem *parent)
    : m_itemData(data), m_parentItem(parent) {}

TableItem::~TableItem() { qDeleteAll(m_childItems); }

void TableItem::appendChild(TableItem *item) {
  m_childItems.append(item);
}

void TableItem::removeChild(int row, int count) {
  m_childItems.remove(row, count);
}

TableItem *TableItem::child(int row) {
  if (row < 0 || row >= m_childItems.size())
    return nullptr;
  return m_childItems.at(row);
}

int TableItem::childCount() const { return m_childItems.count(); }

int TableItem::columnCount() const { return m_itemData.count(); }

QVariant TableItem::data(int column) const {
  if (column < 0 || column >= m_itemData.size())
    return QVariant();
  return m_itemData.at(column);
}
void TableItem::setData(int column, QVariant value) {
  m_itemData[column] = value;
}
TableItem *TableItem::parentItem() { return m_parentItem; }

int TableItem::row() const {
  if (m_parentItem)
    return m_parentItem->m_childItems.indexOf(
        const_cast<TableItem *>(this));

  return 0;
}

}
} // namespace FileTreePane
