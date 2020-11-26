/*
 * @name BookFiler Library - Sort Filter Tree Widget
 * @author Branden Lee
 * @version 1.00
 * @license MIT
 * @brief Super fast tree sorting and filtering tree widget.
 */

/*
 * piwebapi-ucdavis 1.0
 */
#include "MainWidget.hpp"

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {

TableImpl::TableImpl() { this->setObjectName("BookFiler Tree Widget"); };
TableImpl::~TableImpl(){};

int TableImpl::setData(std::shared_ptr<sqlite3> database_,
                       std::string tableName_, std::string idColumn_) {
  database = database_;
  tableName = tableName_;
  idColumn = idColumn_;
  itemModel = std::make_shared<TableItemModel>();
  this->setModel(itemModel.get());
  itemDelegate = std::make_shared<TableItemDelegate>();
  this->setItemDelegate(itemDelegate.get());
  return 0;
}

int TableImpl::update() { return 0; }
int TableImpl::updateIdHint(std::vector<std::string> addedIdList,
                            std::vector<std::string> updatedIdList,
                            std::vector<std::string> deletedIdList) {
  return 0;
}
int TableImpl::connectUpdateIdHint(
    std::function<void(std::vector<std::string>, std::vector<std::string>,
                       std::vector<std::string>)>
        slot) {
  updateSignal.connect(slot);
  return 0;
}
int TableImpl::setItemEditorWidget(
    int columnNum,
    std::function<std::shared_ptr<QWidget>()> editorWidgetCreator) {
  return 0;
}

} // namespace widget
} // namespace bookfiler
