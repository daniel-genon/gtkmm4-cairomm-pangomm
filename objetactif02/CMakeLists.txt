cmake_minimum_required(VERSION 3.5)
project(objetactif02 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#set(CMAKE_BUILD_TYPE Debug)

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

add_executable(objetactif02 ${SOURCE} ${ENTETE})

target_link_libraries(objetactif02 ${GTKMM_LIBRARIES} ${CAIROMM_LIBRARIES} ${PANGOMM_LIBRARIES} )

