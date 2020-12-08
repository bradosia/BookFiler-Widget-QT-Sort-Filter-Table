/*
 * @name BookFiler Widget - Sqlite Model
 * @author Branden Lee
 * @version 1.00
 * @license MIT
 * @brief QAbstractItemModel with a sqlite3 backend.
 */

#ifndef BOOKFILER_WIDGET_SQLITE_MODEL_TEST_H
#define BOOKFILER_WIDGET_SQLITE_MODEL_TEST_H

// config
#include "../core/config.hpp"

// C++
#include <iostream>
#include <map>
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
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QVariant>

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {

/*
 * @brief This class is just a test to be used in place of SqliteModel.
 * SqliteModel has not been implemented yet, so a QSqlTableModel is used which
 * has similar functionality. QSqlTableModel is not used normally because some
 * other modules don't link to QT, so using a sqlite3 database is more portable
 * and a smaller dependency.
 */
class SqliteModelTest : public QSqlTableModel {
  Q_OBJECT
private:
  std::string tableName, viewRootId;
  std::vector<QVariant> headerList;
  boost::signals2::signal<void(std::vector<std::string>,
                               std::vector<std::string>,
                               std::vector<std::string>)>
      updateSignal;
  std::map<std::string, std::string> columnMap;
  std::map<int, int> columnNumMap{{0, 0}, {1, 1}, {2, 2}, {3, 3},
                                  {4, 4}, {5, 5}, {6, 6}};

public:
  SqliteModelTest(QSqlDatabase &database_, std::string tableName_,
                  std::map<std::string, std::string> columnMap_,
                  QObject *parent = nullptr);
  ~SqliteModelTest();

  /* Sets the database to use for the model.
   * @param database mysqlite3 database that this tree widget will be synced
   * with
   * @param tableName the table name
   * @param idColumn The name of the ID column in the database table.
   * for example the sql schema may be: "guid" text(32) NOT NULL
   * * @param idColumn The name of the parent ID column in the database table.
   * for example the sql schema may be: "parent_guid" text(32)
   * @return 0 on success, else error code
   */
  int setData(QSqlDatabase &database, std::string tableName,
              std::map<std::string, std::string> columnMap =
                  std::map<std::string, std::string>());

  /* Sets the root id for the view.
   * @param id the view root. "*" to view all rows with a NULL parent
   * @return 0 on success, else error code
   */
  int setRoot(std::string id);

  /* Sets a map for column number transformation. This is used to re-order
   * column positions
   * @param columnNumMap The column number map
   * @return 0 on success, else error code
   */
  int setColumnNumMap(std::map<int, int> columnNumMap);

  /* Called when the sqlite3 database is updated by another widget, thread, or
   * process. Internally, this method will need to ask the model for the list of
   * QModelIndex that need to be updated.
   * @param addedIdList a list of id that were added. Only the
   * row id provided was added, not the children, unless the child id is
   * also listed
   * @param updatedIdList a list of id that were updated. Only the
   * row id provided was updated, not the children, unless the child id is
   * also listed
   * @param deletedIdList a list of id that were deleted. Only the
   * row id provided was deleted, not the children, unless the child id is
   * also listed
   * @return 0 on success, else error code
   */
  int updateIdHint(std::vector<std::string> addedIdList,
                   std::vector<std::string> updatedIdList,
                   std::vector<std::string> deletedIdList);
  /* Connect a function that will be signaled when the database is updated by
   * this widget
   * @param addedIdList a list of id that were added. Only the
   * row id provided was added, not the children, unless the child id is
   * also listed
   * @param updatedIdList a list of id that were updated. Only the
   * row id provided was updated, not the children, unless the child id is
   * also listed
   * @param deletedIdList a list of id that were deleted. Only the
   * row id provided was deleted, not the children, unless the child id is
   * also listed
   * @return 0 on success, else error code
   */
  int connectUpdateIdHint(
      std::function<void(std::vector<std::string>, std::vector<std::string>,
                         std::vector<std::string>)>);

  /* The vector representation of an SQL "ORDER BY" clause.
   * For example the initialized object:
   * {{"Country","ASC"},{"CustomerName","DESC"}}
   * is converted to the following internally
   * ORDER BY Country ASC, CustomerName DESC;
   * Does not update the view. You should update the view after calling this.
   * @param sortOrderList A list of orders to sort by
   * @return 0 on success, else error code
   */
  int setSort(std::vector<std::pair<std::string, std::string>> sortOrderList);

  /* The vector representation of an SQL "WHERE" clause.
   * For example the initialized object:
   * {{"name","Josephine","="},{"description","funny","match"}}
   * is converted to the following internally
   * WHERE `name`='Josephine' AND `description` MATCH 'funny'
   * the matching methid may be:
   * "=" exact match
   * "match" full-text search
   * "auto" exact match for integers and full text search for strings
   * Does not update the view. You should update the view after calling this.
   * @param sortOrderList A list of orders to sort by
   * @return 0 on success, else error code
   */
  int setFilter(std::vector<std::tuple<std::string, std::string, std::string>>
                    sortOrderList);
};

} // namespace widget
} // namespace bookfiler

#endif // BOOKFILER_WIDGET_SQLITE_MODEL_TEST_H
