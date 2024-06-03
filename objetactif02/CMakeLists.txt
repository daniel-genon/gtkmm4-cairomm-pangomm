cmake_minimum_required(VERSION 3.5)
project(objetactif02 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-4.0>=4.1 )
if (GTKMM_FOUND)
    include_directories( ${GTKMM_INCLUDE_DIRS} )  
    link_directories( ${GTKMM_LIBRARY_DIRS} )
else ()
  message(FATAL_ERROR "GTKmm introuvable")
endif ()

pkg_check_modules(CAIROMM cairomm-1.16>=1.16.0 )
if (CAIROMM_FOUND)
    include_directories( ${CAIROMM_INCLUDE_DIRS} )  
    link_directories( ${CAIROMM_LIBRARY_DIRS} )
else ()
  message(FATAL_ERROR "Cairomm introuvable")
endif ()

pkg_check_modules(PANGOMM pangomm-2.48>=2.48 )
if (PANGOMM_FOUND)
    include_directories( ${PANGOMM_INCLUDE_DIRS} )  
    link_directories( ${PANGOMM_LIBRARY_DIRS} )
else ()
  message(FATAL_ERROR "Cairomm introuvable")
endif ()

find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources REQUIRED)

set(FICRES_CPP resobjetactif.cpp)
set(FICRES_H resobjetactif.h)
set(FICRES_XML resobjetactif.xml)

add_custom_command(
    OUTPUT ${FICRES_CPP} ${FICRES_H}
    COMMAND ${GLIB_COMPILE_RESOURCES}
    ARGS
        --target=${CMAKE_CURRENT_BINARY_DIR}/${FICRES_CPP}
        --generate-source ${FICRES_XML}
    COMMAND ${GLIB_COMPILE_RESOURCES}
    ARGS
        --target=${CMAKE_CURRENT_SOURCE_DIR}/entete/${FICRES_H}
        --generate-header ${FICRES_XML}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ressource
	VERBATIM
)
set(SOURCE
    source/objetactif02.cpp
    source/fenetre.cpp
    source/airededessin.cpp
    source/elementgraphique.cpp
)
set(ENTETE
    entete/fenetre.h
    entete/airededessin.h
    entete/elementgraphique.h
)
add_executable( objetactif02 ${SOURCE} ${ENTETE} ${CMAKE_CURRENT_BINARY_DIR}/${FICRES_CPP} ${CMAKE_CURRENT_SOURCE_DIR}/entete/${FICRES_H} )
target_link_libraries(objetactif02 ${GTKMM_LIBRARIES} ${CAIROMM_LIBRARIES} ${PANGOMM_LIBRARIES} )

set_source_files_properties(
    ${CMAKE_CURRENT_SOURCE_DIR}/entete/${FICRES_H}
    ${CMAKE_CURRENT_BINARY_DIR}/${FICRES_CPP}
    PROPERTIES GENERATED TRUE
)
