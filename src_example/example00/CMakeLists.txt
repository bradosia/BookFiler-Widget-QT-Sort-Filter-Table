set(EXENAME example00)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

set(SOURCES
    main.cpp
)

set(HEADERS
)

include_directories(
    ../../include
)

link_directories(
)

add_executable(${EXENAME} ${SOURCES})

set(LIBRARIES
    # QT5
    Qt5::Widgets

    # Boost
    Boost::system
    Boost::filesystem

    # sqlite3
    sqlite3

    BookFiler-Lib-Sort-Filter-Table-Widget-LibShared
)

if(WIN32)
    set(LIBRARIES ${LIBRARIES}
        # Windows Libraries

    )
elseif(UNIX)
    set(LIBRARIES ${LIBRARIES}
        # Unix Libraries
        dl
    )
endif()

target_link_libraries(${EXENAME} ${LIBRARIES})
