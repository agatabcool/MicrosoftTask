cmake_minimum_required(VERSION 2.8)
project(MicrosoftTask)

set(CMAKE_AUTOMOC ON)

#Adding SVM RANK
SET(SVM_RANK_SRC_DIR "../Libraries/svm_rank")
INCLUDE_DIRECTORIES(${SVM_LIGHT_SRC_DIR})
ADD_LIBRARY(
    svm_rank_lib
    ${SVM_RANK_SRC_DIR}/svm_light/svm_learn.c
    ${SVM_RANK_SRC_DIR}/svm_light/svm_common.c
    ${SVM_RANK_SRC_DIR}/svm_light/svm_hideo.c
    ${SVM_RANK_SRC_DIR}/svm_struct/svm_struct_learn.c
    ${SVM_RANK_SRC_DIR}/svm_struct/svm_struct_common.c
    ${SVM_RANK_SRC_DIR}/svm_struct_api.c
    ${SVM_RANK_SRC_DIR}/svm_struct_learn_custom.c
)

find_package(Qt4 REQUIRED)
find_package(Boost COMPONENTS system filesystem REQUIRED)

set( HEADERS 
    src/MainWindow.h  
    src/preprocessdata.h
    src/processdata.h
    src/qcustomplot.h
)

set( SOURCES 
    src/main.cpp
    src/MainWindow.cpp  
    src/processdata.cpp
    src/preprocessdata.cpp
    src/qcustomplot.cpp
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
target_link_libraries(${PROJECT_NAME} svm_rank_lib)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
