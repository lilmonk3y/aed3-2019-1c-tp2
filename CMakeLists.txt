cmake_minimum_required(VERSION 3.12)
project(aed3_2019_1c_tp2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)


set(SOURCE_FILES prueba_integracion_con_gtest/test/factorialTest.cpp prueba_integracion_con_gtest/src/factorial.cpp project/src/entity/core/Graph.h project/src/entity/core/AdjacencyListGraph.h project/src/entity/core/impl/AdjacencyListGraph.cpp project/src/entity/auxiliar/impl/AdjacencyNode.cpp project/src/entity/auxiliar/AdjacencyNode.h project/test/entity/GraphTest.cpp project/src/utils/DefaultDisjoinSet.h project/src/utils/CompressedDisjoinSet.h project/src/utils/DisjoinSet.h project/src/utils/impl/DefaultDisjoinSet.cpp project/src/utils/impl/CompressedDisjoinSet.cpp project/test/utils/DisjoinSetTest.cpp project/src/utils/GetMST.h project/src/utils/impl/GetMST.cpp project/src/entity/core/Edge.h project/src/entity/core/impl/Edge.cpp project/test/utils/GetMSTTest.cpp project/src/entity/core/impl/DirectedTreeGraph.cpp project/src/entity/core/DirectedTreeGraph.h project/src/entity/auxiliar/impl/TreeNode.cpp project/src/entity/auxiliar/TreeNode.h project/src/entity/auxiliar/impl/TreeEdge.cpp project/src/entity/auxiliar/TreeEdge.h project/src/entity/auxiliar/Representation.h project/src/entity/auxiliar/impl/RepresentationNode.cpp project/src/entity/auxiliar/RepresentationNode.h project/src/entity/auxiliar/TreeRepresentation.cpp project/src/entity/auxiliar/TreeRepresentation.h project/src/entity/auxiliar/ArrayRepresentation.cpp project/src/entity/auxiliar/ArrayRepresentation.h)

add_executable(aed3_2019_1c_tp2 main.cpp ${SOURCE_FILES})

target_link_libraries(aed3_2019_1c_tp2 gtest gtest_main)