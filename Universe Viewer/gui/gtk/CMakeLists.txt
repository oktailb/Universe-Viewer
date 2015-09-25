cmake_minimum_required(VERSION 2.6)

#Configuration du projet
project(UniverseViewerGTK2)

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

#Inclusion des en-têtes publics
include_directories(include)

#Génération de la liste des fichiers sources
file(
        GLOB_RECURSE
        source_files
        src/*
        include/*
        ui/*
)

#Déclaration de l'exécutable
add_executable(
        uvGtk2
        ${source_files}
)

