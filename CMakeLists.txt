cmake_minimum_required(VERSION 3.16)
project(GradesApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(PROJECT_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(CMAKE_AUTOUIC_SEARCH_PATHS
    "${PROJECT_SRC_DIR}/presentation/windows"
    "${PROJECT_SRC_DIR}/presentation/dialogs"
)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

# Enforce lowercase file names under src/.
file(GLOB_RECURSE PROJECT_SOURCE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*")
foreach(PROJECT_FILE IN LISTS PROJECT_SOURCE_FILES)
    get_filename_component(PROJECT_FILE_NAME "${PROJECT_FILE}" NAME)
    string(TOLOWER "${PROJECT_FILE_NAME}" PROJECT_FILE_NAME_LOWER)
    if(NOT PROJECT_FILE_NAME STREQUAL PROJECT_FILE_NAME_LOWER)
        message(FATAL_ERROR "File names in src/ must be lowercase: ${PROJECT_FILE}")
    endif()
endforeach()

# ── Domain ────────────────────────────────────────────────────────────────────
add_library(Domain INTERFACE)
target_include_directories(Domain INTERFACE "${PROJECT_SRC_DIR}")
target_link_libraries(Domain INTERFACE Qt6::Core)

# ── Application ───────────────────────────────────────────────────────────────
add_library(Application STATIC
    src/application/handlers/addstudenthandler.cpp
    src/application/handlers/removestudenthandler.cpp
    src/application/handlers/editstudenthandler.cpp
    src/application/handlers/addsubjecthandler.cpp
    src/application/handlers/removesubjecthandler.cpp
    src/application/handlers/renamesubjecthandler.cpp
    src/application/handlers/getallstudentshandler.cpp
    src/application/handlers/getallsubjectshandler.cpp
)
target_include_directories(Application PUBLIC "${PROJECT_SRC_DIR}")
target_link_libraries(Application PUBLIC Domain)

# ── Infrastructure ────────────────────────────────────────────────────────────
add_library(Infrastructure STATIC
    src/infrastructure/repositories/sqlitedatabase.cpp
    src/infrastructure/repositories/sqlitestudentrepository.cpp
    src/infrastructure/repositories/sqlitesubjectrepository.cpp
)
target_include_directories(Infrastructure PUBLIC "${PROJECT_SRC_DIR}")
target_link_libraries(Infrastructure PUBLIC Domain Qt6::Core Qt6::Sql)

# ── Presentation ──────────────────────────────────────────────────────────────
add_executable(GradesApp
    src/main.cpp
    src/presentation/models/studenttablemodel.cpp
    src/presentation/windows/mainwindow.cpp
    src/presentation/dialogs/studentdialog.cpp
    src/presentation/dialogs/studenteditdialog.cpp
    src/presentation/dialogs/subjectmanagerdialog.cpp
)
target_include_directories(GradesApp PRIVATE "${PROJECT_SRC_DIR}")
target_link_libraries(GradesApp PRIVATE Application Infrastructure Qt6::Widgets)
if (MSVC)
    target_compile_options(GradesApp PRIVATE /W4)
else()
    target_compile_options(GradesApp PRIVATE -Wall -Wextra)
endif()
