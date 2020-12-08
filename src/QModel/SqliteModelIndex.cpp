/*
 * @name BookFiler Widget - Sqlite Model
 * @author Branden Lee
 * @version 1.00
 * @license MIT
 * @brief QAbstractItemModel with a sqlite3 backend.
 */

#if DEPENDENCY_SQLITE

// C++
#include <iostream>

// Local Project
#include "SqliteModelIndex.hpp"

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {

SqliteModelIndex::SqliteModelIndex() {}

SqliteModelIndex::~SqliteModelIndex() {}

int SqliteModelIndex::setParent(SqliteModelIndex *parentIndex_) {
  parentIndex = parentIndex_;
  return 0;
}
int SqliteModelIndex::run() {

    return 0;
}

} // namespace widget
} // namespace bookfiler

#endif
