cmake_minimum_required(VERSION 2.8)
project(MicrosoftTask)

set(CMAKE_AUTOMOC ON)

find_package(Qt4 REQUIRED)
find_package(Boost COMPONENTS system filesystem REQUIRED)

set( HEADERS 
    MainWindow.h  
    preprocessdata.h
)

set( SOURCES 
    main.cpp
    MainWindow.cpp  
    preprocessdata.cpp
)


QT4_WRAP_CPP(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS})

#INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -stdlib=libstdc++" )



add_executable(${PROJECT_NAME} ${SOURCES} ${${PROJECT_NAME}_HEADERS_MOC})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES}  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY} )
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
