/*
 * @name BookFiler Library - Sort Filter Table Widget
 * @author Branden Lee
 * @version 1.00
 * @license MIT
 * @brief sqlite3 based table widget.
 */

#ifndef BOOKFILER_LIBRARY_SORT_FILTER_TABLE_WIDGET_ITEM_MODEL_H
#define BOOKFILER_LIBRARY_SORT_FILTER_TABLE_WIDGET_ITEM_MODEL_H

// config
#include "../core/config.hpp"

// C++
#include <iostream>
#include <memory>
#include <queue>

/* boost 1.72.0
 * License: Boost Software License (similar to BSD and MIT)
 */
#include <boost/signals2.hpp>

/* QT 5.13.2
 * License: LGPLv3
 */
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

// Local Project
#include "TableItem.hpp"

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {

/*
 * @brief Provides a simple table model.
 */
class TableItemModel : public QAbstractItemModel {
  Q_OBJECT

public:
  explicit TableItemModel(QObject *parent = nullptr);
  ~TableItemModel();

  /* Custom methods
   */
  void addData(std::shared_ptr<sqlite3> database, std::string tableName,
               std::string idColumn, std::string parentColumn);

  /* Essential QAbstractTableItemModel methods
   *
   * https://doc.qt.io/qt-5/qabstractTableItemModel.html
   * When subclassing QAbstractTableItemModel, at the very least you must implement
   * index(), parent(), rowCount(), columnCount(), and data().
   * These functions are used in all read-only models, and form the basis of
   * editable models.
   */
  QModelIndex index(int row, int column,
                    const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &index) const override;
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  /* Copy and move operations methods
   */
  Qt::DropActions supportedDropActions() const override;
  bool removeRows(int row, int count,
                  const QModelIndex &parent = QModelIndex()) override;
  /* Other QAbstractTableItemModel methods
   */
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;

private:
  TableItem *rootItem;
};

} // namespace widget
} // namespace bookfiler

#endif // BOOKFILER_LIBRARY_SORT_FILTER_TABLE_WIDGET_ITEM_MODEL_H
