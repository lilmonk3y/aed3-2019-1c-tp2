cmake_minimum_required(VERSION 3.12)
project(aed3_2019_1c_tp2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)


set(SOURCE_FILES prueba_integracion_con_gtest/test/factorialTest.cpp prueba_integracion_con_gtest/src/factorial.cpp project/src/entity/Graph.h project/src/entity/AdjacencyListGraph.h project/src/entity/impl/AdjacencyListGraph.cpp project/src/entity/impl/AdjacencyNode.cpp project/src/entity/AdjacencyNode.h project/test/entity/GraphTest.cpp project/src/utils/DefaultDisjoinSet.h project/src/utils/CompressedDisjoinSet.h project/src/utils/DisjoinSet.h project/src/utils/impl/DefaultDisjoinSet.cpp project/src/utils/impl/CompressedDisjoinSet.cpp project/test/utils/DisjoinSetTest.cpp project/src/utils/GetMST.h project/src/utils/impl/GetMST.cpp project/src/entity/Edge.h project/src/entity/impl/Edge.cpp project/test/utils/GetMSTTest.cpp)

add_executable(aed3_2019_1c_tp2 main.cpp ${SOURCE_FILES})
add_executable(main2 main2.cpp)

target_link_libraries(aed3_2019_1c_tp2 gtest gtest_main)
