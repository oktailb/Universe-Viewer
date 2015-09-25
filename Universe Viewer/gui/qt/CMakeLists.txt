cmake_minimum_required(VERSION 2.6)

#Configuration du projet
project(UniverseViewerQT)
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

#find QT libraries
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

#Inclusion des en-têtes publics
include_directories(
    include
    ../../build/gui/qt
)


#Génération de la liste des fichiers sources
file(
        GLOB_RECURSE
        source_files
        src/*
        include/*
        ui/*
)

QT5_WRAP_UI(UIS_HDRS
    ui/mainwindow.ui
)

ADD_DEFINITIONS(${QT_DEFINITIONS})

#Déclaration de l'exécutable
add_executable(
    uvQt
    ${source_files}
    ${UIS_HDRS}
)


# Use the Widgets module from Qt 5.
target_link_libraries(uvQt Qt5::Widgets)
