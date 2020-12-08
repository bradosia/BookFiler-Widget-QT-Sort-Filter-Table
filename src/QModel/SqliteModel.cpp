/*
 * @name BookFiler Widget - Sqlite Model
 * @author Branden Lee
 * @version 1.00
 * @license MIT
 * @brief QAbstractItemModel with a sqlite3 backend.
 */

#if DEPENDENCY_SQLITE

/* QT 5.13.2
 * License: LGPLv3
 */
#include <QStringList>

// Local Project
#include "SqliteModel.hpp"

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {

SqliteModel::SqliteModel(std::shared_ptr<sqlite3> database_,
                         std::string tableName_,
                         std::map<std::string, std::string> columnMap_,
                         QObject *parent)
    : QAbstractItemModel(parent) {
  setData(database_, tableName_, columnMap_);
}

SqliteModel::~SqliteModel() {}

/* Custom methods
 *
 *
 *
 *
 */

int SqliteModel::setData(std::shared_ptr<sqlite3> database_,
                         std::string tableName_,
                         std::map<std::string, std::string> columnMap_) {
  int rc = 0;

  // Set sqlite database information
  database = database_;
  tableName = tableName_;

  // Use default column map if none provided
  if (!columnMap_.empty()) {
    columnMap = columnMap_;
  }

  /* Get the table headers */
  std::string sqlQuery =
      "SELECT name FROM pragma_table_info('" + tableName + "');";

  sqlite3_stmt *stmt = nullptr;
  rc = sqlite3_prepare_v2(database.get(), sqlQuery.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return rc;

  int rowCount = 0;
  rc = sqlite3_step(stmt);
  while (rc != SQLITE_DONE && rc != SQLITE_OK) {
    rowCount++;
    int colCount = sqlite3_column_count(stmt);
    for (int colIndex = 0; colIndex < colCount; colIndex++) {
      int type = sqlite3_column_type(stmt, colIndex);
      const char *columnName = sqlite3_column_name(stmt, colIndex);
      const unsigned char *valChar = sqlite3_column_text(stmt, colIndex);
      headerList.push_back(reinterpret_cast<const char *>(valChar));
#if BOOKFILER_LIBRARY_SORT_FILTER_TREE_WIDGET_TREE_MODEL_SET_DATA
      std::cout << "row: " << rowCount << ", col: " << colCount
                << ", colName: " << columnName << ", valChar: " << valChar
                << std::endl;
#endif
    }
    rc = sqlite3_step(stmt);
  }

  rc = sqlite3_finalize(stmt);
  if (rc != 0) {
    return rc;
  }
  return 0;
}

int SqliteModel::setRoot(std::string id) {
  viewRootId = id;
  return 0;
}

int SqliteModel::setColumnNumMap(std::map<int, int> columnNumMap_) {
  columnNumMap = columnNumMap_;
  return 0;
}

int SqliteModel::connectUpdateIdHint(
    std::function<void(std::vector<std::string>, std::vector<std::string>,
                       std::vector<std::string>)>
        slot) {
  updateSignal.connect(slot);
  return 0;
}

/* Base methods for the view
 *
 *
 *
 */

int SqliteModel::columnCount(const QModelIndex &parent) const {
#if BOOKFILER_LIBRARY_SORT_FILTER_TREE_WIDGET_TREE_MODEL_COLUMN_COUNT
  std::cout << "SqliteModel::columnCount row: " << parent.row()
            << ", col: " << parent.column();
  if (parent.internalPointer()) {
    std::string parentId =
        *static_cast<std::string *>(parent.internalPointer());
    std::cout << ", parentId: " << parentId;
  }
  std::cout << std::endl;
#endif
  return headerList.size();
}

QVariant SqliteModel::data(const QModelIndex &index, int role) const {
#if BOOKFILER_LIBRARY_SORT_FILTER_TREE_WIDGET_TREE_MODEL_DATA
  std::cout << "SqliteModel::data index.row: " << index.row()
            << ", index.col: " << index.column();
  if (index.internalPointer()) {
    std::string indexId = *static_cast<std::string *>(index.internalPointer());
    std::cout << ", parentId: " << indexId;
  }
  std::cout << std::endl;
#endif

  if (!index.isValid())
    return QVariant();

  std::string childId = *static_cast<std::string *>(index.internalPointer());

  // Get the parentID from the SELECT of the id
  std::string sqlQuery =
      "SELECT `" + headerList[index.column()].toString().toStdString() + "` FROM `" + tableName
      + "` WHERE `" + columnMap.at("id") + "`='" + childId + "'";
  sqlQuery.append(" LIMIT 1;");

  sqlite3_stmt *stmt = nullptr;
  int rc = sqlite3_prepare_v2(database.get(), sqlQuery.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
      return QModelIndex();
  }

  std::string *value = nullptr;
  rc = sqlite3_step(stmt);
  while (rc != SQLITE_DONE && rc != SQLITE_OK) {
      int colCount = sqlite3_column_count(stmt);
      for (int colIndex = 0; colIndex < colCount; colIndex++) {
          const unsigned char *valChar = sqlite3_column_text(stmt, colIndex);
          if (valChar) {
              value = new std::string(reinterpret_cast<const char *>(valChar));
          }
      }
      rc = sqlite3_step(stmt);
  }

  rc = sqlite3_finalize(stmt);
  if (rc != 0) {
      return QVariant();
  }


  // Normal data display
  if (role == Qt::DisplayRole) {
      return value ? QVariant::fromValue<QString>(QString::fromStdString(*value)) : QVariant();
      //return item->data(index.column());
  }
  // Data displayed in the edit box
  else if (role == Qt::EditRole) {
     //return item->data(index.column());
     return value ? QVariant::fromValue<QString>(QString::fromStdString(*value)) : QVariant();
  }

  // for all else
  return QVariant();
}

Qt::ItemFlags SqliteModel::flags(const QModelIndex &index) const {
#if BOOKFILER_LIBRARY_SORT_FILTER_TREE_WIDGET_TREE_MODEL_DATA
  std::cout << "SqliteModel::flags index.row: " << index.row()
            << ", index.col: " << index.column();
  if (index.internalPointer()) {
    std::string indexId = *static_cast<std::string *>(index.internalPointer());
    std::cout << ", indexId: " << indexId;
  }
  std::cout << std::endl;
#endif
  if (!index.isValid())
    return Qt::NoItemFlags;

  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable |
         Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

QVariant SqliteModel::headerData(int section, Qt::Orientation orientation,
                                 int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    return headerList.at(section);
  }

  return QVariant();
}

QModelIndex SqliteModel::index(int row, int column,
                               const QModelIndex &parent) const {
  int rc = 0;
  std::string parentId;
  std::string *childId;

#if BOOKFILER_LIBRARY_SORT_FILTER_TREE_WIDGET_TREE_MODEL_DATA
  std::cout << "SqliteModel::index parent.row: " << parent.row()
            << ", parent.col: " << parent.column();
  std::cout << ", row: " << row << ", col: " << column;
  if (parent.internalPointer()) {
    parentId = *static_cast<std::string *>(parent.internalPointer());
    std::cout << ", parentId: " << parentId;
  }
  std::cout << std::endl;
#endif

  if (!hasIndex(row, column, parent))
    return QModelIndex();

  if (!parent.isValid())
    parentId = viewRootId;
  else
    parentId = *static_cast<std::string *>(parent.internalPointer());

  // Get the parentID from the SELECT of the id
  std::string sqlQuery =
      "SELECT `" + columnMap.at("id") + "` FROM `" + tableName + "`";
  sqlQuery.append(whereSQLCondition(parentId));
  sqlQuery.append(sortSQL());
  sqlQuery.append(" LIMIT " + std::to_string(row) + ",1;");

  sqlite3_stmt *stmt = nullptr;
  rc = sqlite3_prepare_v2(database.get(), sqlQuery.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    return QModelIndex();
  }

  rc = sqlite3_step(stmt);
  while (rc != SQLITE_DONE && rc != SQLITE_OK) {
    int colCount = sqlite3_column_count(stmt);
    for (int colIndex = 0; colIndex < colCount; colIndex++) {
      const unsigned char *valChar = sqlite3_column_text(stmt, colIndex);
      childId = new std::string(reinterpret_cast<const char *>(valChar));
    }
    rc = sqlite3_step(stmt);
  }

  rc = sqlite3_finalize(stmt);
  if (rc != 0) {
    return QModelIndex();
    ;
  }

#if BOOKFILER_LIBRARY_SORT_FILTER_TREE_WIDGET_TREE_MODEL_ROW_COUNT
  std::cout << "SqliteModel::index childId: " << *childId << std::endl;
#endif

  if (childId)
    return createIndex(row, column, childId);
  return QModelIndex();
}

QModelIndex SqliteModel::parent(const QModelIndex &index) const {
  int rc = 0;
  std::string *parentId = nullptr;
  std::string indexId;

#if BOOKFILER_LIBRARY_SORT_FILTER_TREE_WIDGET_TREE_MODEL_DATA
  std::cout << "SqliteModel::parent row: " << index.row()
            << ", col: " << index.column();
  if (index.internalPointer()) {
    indexId = *static_cast<std::string *>(index.internalPointer());
    std::cout << ", indexId: " << indexId;
  }
  std::cout << std::endl;
#endif

  if (!index.isValid())
    return QModelIndex();

  // Get the parentID from the SELECT of the id
  std::string sqlQuery = "SELECT `" + columnMap.at("parentId") + "` FROM `" +
                         tableName + "` WHERE `" + columnMap.at("id") + "`='" +
                         indexId + "';";

  sqlite3_stmt *stmt = nullptr;
  rc = sqlite3_prepare_v2(database.get(), sqlQuery.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return QModelIndex();

  rc = sqlite3_step(stmt);
  while (rc != SQLITE_DONE && rc != SQLITE_OK) {
    int colCount = sqlite3_column_count(stmt);
    for (int colIndex = 0; colIndex < colCount; colIndex++) {
      int type = sqlite3_column_type(stmt, colIndex);
      if (type == SQLITE_NULL) {
        break;
      }
      const unsigned char *valChar = sqlite3_column_text(stmt, colIndex);
      parentId = new std::string(reinterpret_cast<const char *>(valChar));
    }
    rc = sqlite3_step(stmt);
  }

  rc = sqlite3_finalize(stmt);
  if (rc != 0) {
    return QModelIndex();
  }

#if BOOKFILER_LIBRARY_SORT_FILTER_TREE_WIDGET_TREE_MODEL_ROW_COUNT
  if (parentId) {
    std::cout << "SqliteModel::parent parentId: " << *parentId << std::endl;
  }
#endif

  if (!parentId)
    return QModelIndex();

  return createIndex(0, 0, parentId);
}

int SqliteModel::rowCount(const QModelIndex &parent) const {
  int rc = 0;
  int rowCountRet = 0;
  std::string parentId;

#if BOOKFILER_LIBRARY_SORT_FILTER_TREE_WIDGET_TREE_MODEL_DATA
  std::cout << "SqliteModel::rowCount parent.row: " << parent.row()
            << ", parent.col: " << parent.column();
  if (parent.internalPointer()) {
    parentId = *static_cast<std::string *>(parent.internalPointer());
    std::cout << ", parentId: " << parentId;
  }
  std::cout << std::endl;
#endif
  /*if (parent.column() > 0)
    return 0;*/

  if (!parent.isValid())
    parentId = viewRootId;
  else
    parentId = *static_cast<std::string *>(parent.internalPointer());

#if BOOKFILER_LIBRARY_SORT_FILTER_TREE_WIDGET_TREE_MODEL_ROW_COUNT
  std::cout << "SqliteModel::rowCount isValid: "
            << (parent.isValid() ? "true" : "false")
            << ", parentId: " << parentId << std::endl;
#endif

  // Get the parentID from the SELECT of the id
  std::string sqlQuery = "SELECT COUNT(1) FROM `" + tableName + "`";
  sqlQuery.append(whereSQLCondition(parentId));
  sqlQuery.append(";");
  sqlite3_stmt *stmt = nullptr;
  rc = sqlite3_prepare_v2(database.get(), sqlQuery.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return 0;

  rc = sqlite3_step(stmt);
  while (rc != SQLITE_DONE && rc != SQLITE_OK) {
    int colCount = sqlite3_column_count(stmt);
    for (int colIndex = 0; colIndex < colCount; colIndex++) {
      rowCountRet = sqlite3_column_int(stmt, colIndex);
    }
    rc = sqlite3_step(stmt);
  }

  rc = sqlite3_finalize(stmt);
  if (rc != 0) {
    return 0;
  }

#if BOOKFILER_LIBRARY_SORT_FILTER_TREE_WIDGET_TREE_MODEL_ROW_COUNT
  std::cout << "SqliteModel::rowCount rowCountRet: " << rowCountRet
            << std::endl;
#endif

  return rowCountRet;
}

bool SqliteModel::setData(const QModelIndex &index, const QVariant &value,
                          int role) {
  if (role) {
    // TODO
  }
  return true;
}

Qt::DropActions SqliteModel::supportedDropActions() const {
  return Qt::CopyAction | Qt::MoveAction;
}

bool SqliteModel::removeRows(int row, int count, const QModelIndex &parent) {
  // TODO
  return true;
}

int SqliteModel::setSort(std::vector<std::pair<std::string, std::string> > sortOrderList)
{
    sortOrder = sortOrderList;
    return 0;
}

int SqliteModel::setFilter(std::vector<std::tuple<std::string, std::string, std::string> > filterList)
{
    filter = filterList;
    return 0;
}

std::string SqliteModel::whereSQLCondition(const std::string &parentId) const
{
    std::string whereClause;
    if (parentId != "*") {
        whereClause.append(" `" + columnMap.at("parentId") + "`='" + parentId +
                        "'");
    }

    std::string filterStrings;
    for (auto filterElement: filter) {
        auto fieldName = std::get<0>(filterElement);
        auto value = std::get<1>(filterElement);
        auto condition = std::get<2>(filterElement);
        std::string filterString;
        if (condition == "=") {
            filterString = "`" + fieldName + "` = '" + value + "'";
        } else if (condition == "match") {
            filterString = "`" + fieldName + "` like '%" + value + "%'";
        } else if (condition == "auto") {
        }
        filterStrings.append((filterString.empty() ? "" : " AND ") + filterString);
    }

    if (!whereClause.empty()) {
        if (!filterStrings.empty()) {
            whereClause = " AND ";
        }
    }
    whereClause += filterStrings;
    whereClause = whereClause.empty() ? "" : " WHERE " + whereClause;
    return  whereClause;
}

std::string SqliteModel::sortSQL() const
{
    std::string sortSQLClause;
    for (auto sortElement: sortOrder) {
        std::string sortField = "`" + sortElement.first + "` " + sortElement.second;
        sortSQLClause.append((sortSQLClause.empty() ? "" : " , ") + sortField);
    }

    sortSQLClause = (sortSQLClause.empty() ? "" : " ORDER BY ") + sortSQLClause;
    return sortSQLClause;
}


} // namespace widget
} // namespace bookfiler

#endif
