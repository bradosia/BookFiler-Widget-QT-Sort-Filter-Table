/*
 * @name BookFiler Widget - Sqlite Model
 * @author Branden Lee
 * @version 1.00
 * @license MIT
 * @brief QAbstractItemModel with a sqlite3 backend.
 */

/* QT 5.13.2
 * License: LGPLv3
 */
#include <QStringList>

// Local Project
#include "SqliteModelTest.hpp"

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {

SqliteModelTest::SqliteModelTest(QSqlDatabase &database_,
                                 std::string tableName_,
                                 std::map<std::string, std::string> columnMap_,
                                 QObject *parent)
    : QSqlTableModel(parent, database_) {
  setData(database_, tableName_, columnMap_);
}

SqliteModelTest::~SqliteModelTest() {}

/* Custom methods
 *
 *
 *
 *
 */

int SqliteModelTest::setData(QSqlDatabase &database_, std::string tableName_,
                             std::map<std::string, std::string> columnMap_) {
  Q_UNUSED(database_);

  // Set sqlite database information
  tableName = tableName_;
  setTable(QString().fromStdString(tableName));
  setEditStrategy(QSqlTableModel::OnManualSubmit);
  select();

  // Use default column map if none provided
  if (!columnMap_.empty()) {
    columnMap = columnMap_;
  }
  return 0;
}

int SqliteModelTest::setRoot(std::string id) {
  viewRootId = id;
  return 0;
}

int SqliteModelTest::setColumnNumMap(std::map<int, int> columnNumMap_) {
  columnNumMap = columnNumMap_;
  return 0;
}

int SqliteModelTest::updateIdHint(std::vector<std::string> addedIdList,
                                  std::vector<std::string> updatedIdList,
                                  std::vector<std::string> deletedIdList) {
  return 0;
}
int SqliteModelTest::connectUpdateIdHint(
    std::function<void(std::vector<std::string>, std::vector<std::string>,
                       std::vector<std::string>)>
        slot) {
  updateSignal.connect(slot);
  return 0;
}

int setSort(std::vector<std::pair<std::string, std::string>> sortOrderList) {
  // TODO
  return 0;
}

int setFilter(std::vector<std::tuple<std::string, std::string, std::string>>
                  sortOrderList) {
  // TODO
  return 0;
}

} // namespace widget
} // namespace bookfiler
