cmake_minimum_required(VERSION 3.12)
project(aed3_2019_1c_tp2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)


set(SOURCE_FILES prueba_integracion_con_gtest/test/factorialTest.cpp prueba_integracion_con_gtest/src/factorial.cpp project/src/entity/core/Graph.h project/src/entity/core/AdjacencyListGraph.h project/src/entity/core/impl/AdjacencyListGraph.cpp project/src/entity/auxiliar/impl/AdjacencyNode.cpp project/src/entity/auxiliar/AdjacencyNode.h project/test/entity/GraphTest.cpp project/src/utils/ArrayDisjoinSet.h project/src/utils/ArrayCompressedDisjoinSet.h project/src/utils/DisjoinSet.h project/src/utils/impl/ArrayDisjoinSet.cpp project/src/utils/impl/ArrayCompressedDisjoinSet.cpp project/test/utils/DisjoinSetTest.cpp project/src/utils/GetMST.h project/src/utils/impl/GetMST.cpp project/src/entity/core/Edge.h project/src/entity/core/impl/Edge.cpp project/test/utils/GetMSTTest.cpp project/src/entity/auxiliar/impl/DirectedTreeGraph.cpp project/src/entity/auxiliar/DirectedTreeGraph.h project/src/entity/auxiliar/impl/TreeNode.cpp project/src/entity/auxiliar/TreeNode.h project/src/utils/impl/TreeDisjoinSet.cpp project/src/utils/TreeDisjoinSet.h project/src/utils/impl/TreeCompressedDisjoinSet.cpp project/src/utils/TreeCompressedDisjoinSet.h)

add_executable(aed3_2019_1c_tp2 main.cpp ${SOURCE_FILES})

target_link_libraries(aed3_2019_1c_tp2 gtest gtest_main)