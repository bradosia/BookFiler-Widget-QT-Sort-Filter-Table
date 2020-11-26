/*
 * @name BookFiler Library - Sort Filter Tree Widget
 * @author Branden Lee
 * @version 1.00
 * @license MIT
 * @brief sqlite3 based tree widget.
 */

// C++
#include <iostream>

// Local Project
#include "ItemDelegate.hpp"

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {

TableItemDelegate::TableItemDelegate() {
  std::cout << "TableItemDelegate\n";
}

QWidget *
TableItemDelegate::createEditor(QWidget *parent,
                                     const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const {
  std::cout << "createEditor() index.row=" << index.row()
            << " index.column=" << index.column() << "\n";
  if (index.data().canConvert<QString>()) {
    TableItemEditor *editor = new TableItemEditor(parent);
    const int row = index.row();
    editor->addItem(QString("one in row %1").arg(row));
    editor->addItem(QString("two in row %1").arg(row));
    editor->addItem(QString("three in row %1").arg(row));
    connect(editor, &TableItemEditor::editingFinished, this,
            &TableItemDelegate::commitAndCloseEditor);
    return editor;
  }
  return QStyledItemDelegate::createEditor(parent, option, index);
}

void TableItemDelegate::setEditorData(QWidget *editor,
                                           const QModelIndex &index) const {
  TableItemEditor *cb = qobject_cast<TableItemEditor *>(editor);
  // get the index of the text in the combobox that matches the current value of
  // the item
  const QString currentText = index.data(Qt::EditRole).toString();
  const int cbIndex = cb->findText(currentText);
  // if it is valid, adjust the combobox
  if (cbIndex >= 0)
    cb->setCurrentIndex(cbIndex);
}

void TableItemDelegate::setModelData(QWidget *editor,
                                          QAbstractItemModel *model,
                                          const QModelIndex &index) const {
  TableItemEditor *cb = qobject_cast<TableItemEditor *>(editor);
  model->setData(index, cb->currentText(), Qt::EditRole);
}

void TableItemDelegate::commitAndCloseEditor() {
  TableItemEditor *editor = qobject_cast<TableItemEditor *>(sender());
  emit commitData(editor);
  emit closeEditor(editor);
}

}
} // namespace FileTreePane
