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
#include "ItemEditor.hpp"

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {

/* The initializer list is required to keep the widget embedded in the cell
 * or else the widget appears as a new window
 */
TableItemEditor::TableItemEditor(QWidget *parent) : QComboBox(parent) {
  std::cout << "TableItemEditor\n";
}

} // namespace widget
} // namespace bookfiler
