/*
 * @name BookFiler Library - Sort Filter Table Widget
 * @author Branden Lee
 * @version 1.00
 * @license MIT
 * @brief sqlite3 based table widget.
 */

#ifndef BOOKFILER_LIBRARY_SORT_FILTER_TABLE_WIDGET_TABLE_ITEM_H
#define BOOKFILER_LIBRARY_SORT_FILTER_TABLE_WIDGET_TABLE_ITEM_H

// config
#include "../core/config.hpp"

/* sqlite3 3.33.0
 * License: PublicDomain
 */
#include <sqlite3.h>

/* QT 5.13.2
 * License: LGPLv3
 */
#include <QComboBox>
#include <QStyledItemDelegate>
#include <QVariant>
#include <QVector>

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {
/*
 * @brief A container for items of data supplied by the simple tree model.
 */
class TableItem {
public:
  explicit TableItem(const QVector<QVariant> &data,
                      TableItem *parentItem = nullptr);
  ~TableItem();

  void appendChild(TableItem *child);
  void removeChild(int row, int count);

  TableItem *child(int row);
  int childCount() const;
  int columnCount() const;
  QVariant data(int column) const;
  void setData(int column, QVariant value);
  int row() const;
  TableItem *parentItem();

private:
  QVector<TableItem *> m_childItems;
  QVector<QVariant> m_itemData;
  TableItem *m_parentItem;
};

} // namespace widget
} // namespace bookfiler

#endif // BOOKFILER_LIBRARY_SORT_FILTER_TABLE_WIDGET_TABLE_ITEM_H
