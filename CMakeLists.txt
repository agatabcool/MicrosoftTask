#rm CMakeCache.txt; cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_ECLIPSE_VERSION=4.4 -DLIBLINEAR_DIR=/usr/local/Cellar/liblinear/1.9.4
#rm CMakeCache.txt; cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_ECLIPSE_VERSION=4.4 -DLIBLINEAR_SRC_DIR=../Libraries/liblinear_1_96

cmake_minimum_required(VERSION 2.8)
project(MicrosoftTask)

#set(CMAKE_CXX_FLAGS "-mmacosx-version-min=10.7")
#SET(CMAKE_CXX_FLAGS  "-arch x86_64")
SET(CFLAGS="-arch i386 -arch x86_64")
#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  -std=c++11" )
#MACOSX_DEPLOYMENT_TARGET='10.9'

set(CMAKE_AUTOMOC ON)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

#Adding SVM RANK
SET(SVM_RANK_SRC_DIR "../Libraries/svm_rank")
#SET(LIBLINEAR_SRC_DIR "../Libraries/liblinear_1_96")

INCLUDE_DIRECTORIES(${SVM_LIGHT_SRC_DIR})
INCLUDE_DIRECTORIES(${LIBLINEAR_SRC_DIR})

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

ADD_LIBRARY(
    liblinear_lib STATIC
    ${LIBLINEAR_SRC_DIR}/predict.c
    ${LIBLINEAR_SRC_DIR}/linear.cpp
    ${LIBLINEAR_SRC_DIR}/train.c
    ${LIBLINEAR_SRC_DIR}/tron.cpp
)

MESSAGE(liblinear_lib)

#find_library(LIBLINEAR_LIBRARIES NAMES liblinear.dylib PATHS ${LIBLINEAR_DIR}/lib)
#MESSAGE(${LIBLINEAR_LIBRARIES})

find_package(Qt4 REQUIRED)

FIND_PACKAGE(Eigen3)
include_directories( ${EIGEN3_INCLUDE_DIRS} )

find_package(Boost COMPONENTS system filesystem REQUIRED)

set( HEADERS 
    src/MainWindow.h  
    src/preprocessdata.h
    src/processdata.h
    src/qcustomplot.h
    src/logregression.h
    src/svmrankanalysis.h
    src/logreg.h
)

set( SOURCES 
    src/main.cpp
    src/MainWindow.cpp  
    src/processdata.cpp
    src/preprocessdata.cpp
    src/qcustomplot.cpp
    src/logregression.cpp
    src/svmrankanalysis.cpp
    src/logreg.cpp
)


QT4_WRAP_CPP(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS})

#INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -stdlib=libstdc++" )

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})


add_executable(${PROJECT_NAME} ${SOURCES} ${${PROJECT_NAME}_HEADERS_MOC})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES}  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY} )
target_link_libraries(${PROJECT_NAME} svm_rank_lib)
#target_link_libraries(${PROJECT_NAME} ${LIBLINEAR_LIBRARIES})
target_link_libraries(${PROJECT_NAME} liblinear_lib)

