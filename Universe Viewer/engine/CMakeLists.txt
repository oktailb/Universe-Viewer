cmake_minimum_required(VERSION 2.6)

#Configuration du projet
project(UniverseViewerEngine)
set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

#Inclusion des en-têtes publics
include_directories(include)

#Configuration de la bibliothèque
file(
        GLOB_RECURSE
        source_files
        src/*
        include/*
)

add_library(
        uvEngine
        SHARED
        ${source_files}
)

