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
    src/application/commands/addstudentcommand.h
    src/application/commands/addsubjectcommand.h
    src/application/commands/editstudentcommand.h
    src/application/commands/removestudentcommand.h
    src/application/commands/removesubjectcommand.h
    src/application/commands/renamesubjectcommand.h
    src/application/commands/updategradecommand.h
    src/application/handlers/addstudenthandler.cpp
    src/application/handlers/addstudenthandler.h
    src/application/handlers/removestudenthandler.cpp
    src/application/handlers/removestudenthandler.h
    src/application/handlers/editstudenthandler.cpp
    src/application/handlers/editstudenthandler.h
    src/application/handlers/addsubjecthandler.cpp
    src/application/handlers/addsubjecthandler.h
    src/application/handlers/removesubjecthandler.cpp
    src/application/handlers/removesubjecthandler.h
    src/application/handlers/renamesubjecthandler.cpp
    src/application/handlers/renamesubjecthandler.h
    src/application/handlers/getallstudentshandler.cpp
    src/application/handlers/getallstudentshandler.h
    src/application/handlers/getallsubjectshandler.cpp
    src/application/handlers/getallsubjectshandler.h
    src/application/handlers/updategradehandler.h
    src/application/queries/getallstudentsquery.h
    src/application/queries/getallsubjectsquery.h
)
target_include_directories(Application PUBLIC "${PROJECT_SRC_DIR}")
target_link_libraries(Application PUBLIC Domain)

# ── Infrastructure ────────────────────────────────────────────────────────────
add_library(Infrastructure STATIC
    src/infrastructure/repositories/sqlitedatabase.cpp
    src/infrastructure/repositories/sqlitedatabase.h
    src/infrastructure/repositories/sqlitestudentrepository.cpp
    src/infrastructure/repositories/sqlitestudentrepository.h
    src/infrastructure/repositories/sqlitesubjectrepository.cpp
    src/infrastructure/repositories/sqlitesubjectrepository.h
    src/domain/entities/student.h
    src/domain/entities/subject.h
    src/domain/repositories/istudentrepository.h
    src/domain/repositories/isubjectrepository.h
    src/domain/value_objects/albumnumber.h
    src/domain/value_objects/subjectname.h
)
target_include_directories(Infrastructure PUBLIC "${PROJECT_SRC_DIR}")
target_link_libraries(Infrastructure PUBLIC Domain Qt6::Core Qt6::Sql)

# ── Presentation ──────────────────────────────────────────────────────────────
add_executable(GradesApp
    src/main.cpp
    src/presentation/models/studenttablemodel.cpp
    src/presentation/models/studenttablemodel.h
    src/presentation/presenters/mainwindowpresenter.cpp
    src/presentation/presenters/mainwindowpresenter.h
    src/presentation/presenters/studentdialogpresenter.cpp
    src/presentation/presenters/studentdialogpresenter.h
    src/presentation/presenters/studenteditdialogpresenter.cpp
    src/presentation/presenters/studenteditdialogpresenter.h
    src/presentation/presenters/subjectmanagerdialogpresenter.cpp
    src/presentation/presenters/subjectmanagerdialogpresenter.h
    src/presentation/windows/mainwindow.cpp
    src/presentation/windows/mainwindow.h
    src/presentation/windows/mainwindow.ui
    src/presentation/dialogs/studentdialog.cpp
    src/presentation/dialogs/studentdialog.h
    src/presentation/dialogs/studentdialog.ui
    src/presentation/dialogs/studenteditdialog.cpp
    src/presentation/dialogs/studenteditdialog.h
    src/presentation/dialogs/studenteditdialog.ui
    src/presentation/dialogs/subjectmanagerdialog.cpp
    src/presentation/dialogs/subjectmanagerdialog.h
    src/presentation/dialogs/subjectmanagerdialog.ui
)
target_include_directories(GradesApp PRIVATE "${PROJECT_SRC_DIR}")
target_link_libraries(GradesApp PRIVATE Application Infrastructure Qt6::Widgets)
if (MSVC)
    target_compile_options(GradesApp PRIVATE /W4)
else()
    target_compile_options(GradesApp PRIVATE -Wall -Wextra)
endif()

# IDE project grouping (Visual Studio / compatible generators)
file(GLOB_RECURSE IDE_SOURCE_FILES CONFIGURE_DEPENDS "${PROJECT_SRC_DIR}/*.cpp")
file(GLOB_RECURSE IDE_HEADER_FILES CONFIGURE_DEPENDS "${PROJECT_SRC_DIR}/*.h" "${PROJECT_SRC_DIR}/*.hpp")
file(GLOB_RECURSE IDE_FORM_FILES CONFIGURE_DEPENDS "${PROJECT_SRC_DIR}/*.ui")

source_group("Source Files" FILES ${IDE_SOURCE_FILES})
source_group("Header Files" FILES ${IDE_HEADER_FILES})
source_group("Forms" FILES ${IDE_FORM_FILES})
