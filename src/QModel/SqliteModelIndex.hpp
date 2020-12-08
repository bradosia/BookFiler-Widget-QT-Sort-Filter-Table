/*
 * @name BookFiler Widget - Sqlite Model
 * @author Branden Lee
 * @version 1.00
 * @license MIT
 * @brief QAbstractItemModel with a sqlite3 backend.
 */

#if DEPENDENCY_SQLITE
#ifndef BOOKFILER_WIDGET_SQLITE_MODEL_INDEX_H
#define BOOKFILER_WIDGET_SQLITE_MODEL_INDEX_H

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
 * @brief An index meant to be used with SqliteModel. Implements some caching
 * for queries to be used for the virtual data() function  from
 * QAbstractItemModel
 */
class SqliteModelIndex {
private:
  SqliteModelIndex *parentIndex;

public:
  SqliteModelIndex();
  ~SqliteModelIndex();

  int setParent(SqliteModelIndex *parentIndex);
  int run();
};

} // namespace widget
} // namespace bookfiler

#endif // BOOKFILER_WIDGET_SQLITE_MODEL_INDEX_H
#endif
