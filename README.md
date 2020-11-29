# BookFiler Widget w/ QT: Sort Filter Tree Widget
This is a QT5 widget that creates a `QTreeView` with sorting, filtering, and item selection functionality with a `sqlite3` backend.

# Usage Instructions

Connect to your database:
```cpp
sqlite3 *dbPtr = nullptr;
sqlite3_open("myDatabase.db", &dbPtr);
// Using shared pointers when possible
std::shared_ptr<sqlite3> database(nullptr);
database.reset(dbPtr, sqlite3_close);
```

Create the tree widget and set the database data
```cpp
std::shared_ptr<bookfiler::widget::TableImpl> tableWidget =
      std::make_shared<bookfiler::widget::TableImpl>();
tableWidget->setData(database, "testTable", "guid");
tableWidget->update();
```

## Table format

This widget will work with any sqlite3 table as long as there is a `guid` column. The  `guid` is a unique id for the row.

# Build Instructions

## Windows - MinGW-w64
Install MSYS2<BR>
Then, install GCC, cmake, git and dependencies. Confirmed working with Windows 10 as of 11/19/2020.
```shell
pacman -Syu
pacman -S mingw-w64-x86_64-gcc git make mingw-w64-x86_64-cmake
pacman -Rns cmake
# restart MSYS2 so that we use the mingw cmake
pacman -S mingw-w64-x86_64-boost mingw-w64-x86_64-sqlite3
```
Build:
```shell
git clone https://github.com/bradosia/BookFiler-Lib-Sort-Filter-Tree-Widget
cd BookFiler-Module-HTTP
mkdir build
cd build
cmake -G "MSYS Makefiles" ../
make
```

## Linux Ubuntu
Install GCC, cmake, git and dependencies. Confirmed working with Ubuntu 20.04 as of 11/8/2020.
```shell
sudo apt-get update
sudo apt install build-essential gcc-multilib g++-multilib cmake git
sudo apt install libboost-all-dev mingw-w64-x86_64-sqlite3
```
Build:
```shell
git clone https://github.com/bradosia/BookFiler-Lib-Sort-Filter-Tree-Widget
cd BookFiler-Module-HTTP
mkdir build
cd build
cmake ../
make
```

# Developers

[Developer Notes](/dev/readme.md)

