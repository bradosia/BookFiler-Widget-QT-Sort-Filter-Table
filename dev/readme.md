# Development Summary

I need a QT5 widget written in C++ for a desktop application. The Libraries used are QT, Boost, and sqlite3. I need a custom `QTableView` created that is able to be sorted, filtered, and edited using sqlite3 as the backend. To Sort and filter you need to use SQL queries to reorder the data. The widget should be able to handle at least one thousand rows in the view not including all the child elements.

I already started on the code. See the header I started for how to use each method of the widget [/src/UI/MainWidget.hpp](https://github.com/bradosia/BookFiler-Lib-Sort-Filter-Tree-Widget/blob/main/src/UI/MainWidget.hpp).

## Compiler and compatability

Program must compile on Windows and Linux. For Windows, use MinGW for compiling. For Linux use GCC. Use cmake as the build scipt. Personally, the IDE I use is QT Creator, but any should work as long as you can build with cmake.

## `QTreeView` column dynamic sizing

The `QTreeView` columns must be dynamically created to be the same as the `sqlite3` table passed to the widget. You must use an SQL query to detect the columns in the table and dynamically create a view for it. `sqlite3` table must have the columns `guid` and `guid_parent` (the name of the column can be different, the columns must have the same purpose) so that the tree view children can be built off this. 

For example, I should be able to connect any database that is set up with columns `guid` and `guid_parent`:
```cpp
sqlite3 *dbPtr = nullptr;
sqlite3_open("myDatabase.db", &dbPtr);
// Using shared pointers when possible
std::shared_ptr<sqlite3> database(nullptr);
database.reset(dbPtr, sqlite3_close);
```

Then I should be able to create the tree widget and set the database data.
```cpp
std::shared_ptr<bookfiler::widget::TreeImpl> treeWidget =
      std::make_shared<bookfiler::widget::TreeImpl>();
treeWidget->setData(database, "testTable", "guid", "parent_guid");
// Set the view to show all rows with column "parent_guid"==NULL
treeWidget->setRoot("*"); 
// Update the internal implementation
treeWidget->update();
```

Here is an example of how the `QTreeView` will by dynamically created by the `sqlite3` table:

### Example 1

`sqlite3` table columns: guid, parent_guid, Subject, Important, Attachment, From, Date, Size. Hidden columns: guid, parent_guid.

![Style 1](https://github.com/bradosia/BookFiler-Lib-Sort-Filter-Tree-Widget/blob/main/dev/tree-view-design-1.png?raw=true)

### Example 2

`sqlite3` table columns: guid, parent_guid, Name. Hidden columns: guid, parent_guid.

![Style 2](https://github.com/bradosia/BookFiler-Lib-Sort-Filter-Tree-Widget/blob/main/dev/tree-view-design-2.png?raw=true)

## Sorting and Filtering Implementation

You may use `QSortFilterProxyModel` to help with sorting and filtering. 

## Coding Standards
Always use the standard library when possible. Use `std::shared_ptr` and `std::unique_ptr` instead of raw pointers whenever possible. use `boost` if some method does not exist in standard library. Finally use `QT5` as the last option.

Separate all graphical GUI code into the `/src/UI/` directory. Anything with `QT` should be in the `/src/UI/` directory. All logic and non-GUI code goes into the `/src/core/` directory.

* Use camel case
* Use C++17 best coding practices
* Use the standard library when possible

## Deliverables

* Clean and commented code that follows the general design already provided and discussed here
* A working example [/src_example/example00/main.cpp](https://github.com/bradosia/BookFiler-Lib-Sort-Filter-Tree-Widget/blob/main/src_example/example00/main.cpp).
* cells are selectable and copyable as tab separated values.
* able to paste tab separated values.
* Should be able to click the header column titles to toggle ascending and descending order sort
* Create a search bar to filter results
* Double clicking on a field will make it editable
* Text should be able to be selectable in the view

