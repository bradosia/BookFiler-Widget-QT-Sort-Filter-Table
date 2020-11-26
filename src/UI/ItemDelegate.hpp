/*
 * @name BookFiler Library - Sort Filter Table Widget
 * @author Branden Lee
 * @version 1.00
 * @license MIT
 * @brief sqlite3 based table widget.
 */

#ifndef BOOKFILER_LIBRARY_SORT_FILTER_TABLE_WIDGET_ITEM_DELEGATE_H
#define BOOKFILER_LIBRARY_SORT_FILTER_TABLE_WIDGET_ITEM_DELEGATE_H

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

// Local Project
#include "ItemEditor.hpp"

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {

/* This class provides complete control over the editing and display of
 * items.
 */
class TableItemDelegate : public QStyledItemDelegate {
  Q_OBJECT
public:
  TableItemDelegate();
  ~TableItemDelegate() {}

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const override;
  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const;

private:
  void commitAndCloseEditor();
};

} // namespace widget
} // namespace bookfiler

#endif // BOOKFILER_LIBRARY_SORT_FILTER_TABLE_WIDGET_ITEM_DELEGATE_H
