cmake_minimum_required(VERSION 3.5)
project(aed3_2019_1c_tp2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)


set(SOURCE_FILES
    prueba_integracion_con_gtest/test/factorialTest.cpp
    prueba_integracion_con_gtest/src/factorial.cpp
    project/src/entity/core/Graph.h
    project/src/entity/core/AdjacencyListGraph.h
    project/src/entity/core/impl/AdjacencyListGraph.cpp
    project/src/entity/auxiliar/impl/AdjacencyNode.cpp
    project/src/entity/auxiliar/AdjacencyNode.h
    project/test/entity/GraphTest.cpp
    project/src/utils/ArrayDisjoinSet.h
    project/src/utils/ArrayCompressedDisjoinSet.h
    project/src/utils/DisjoinSet.h
    project/src/utils/impl/ArrayDisjoinSet.cpp
    project/src/utils/impl/ArrayCompressedDisjoinSet.cpp
    project/test/utils/DisjoinSetTest.cpp
    project/src/utils/GetMST.h
    project/src/utils/impl/GetMST.cpp
    project/src/entity/core/Edge.h
    project/src/entity/core/impl/Edge.cpp
    project/test/utils/GetMSTTest.cpp
    project/src/entity/auxiliar/impl/DirectedTreeGraph.cpp
    project/src/entity/auxiliar/DirectedTreeGraph.h
    project/src/entity/auxiliar/impl/TreeNode.cpp
    project/src/entity/auxiliar/TreeNode.h
    project/src/utils/impl/TreeDisjoinSet.cpp
    project/src/utils/TreeDisjoinSet.h
    project/src/utils/impl/TreeCompressedDisjoinSet.cpp
    project/src/utils/TreeCompressedDisjoinSet.h
    project/src/parteUno/SegmentationAlgorithm.h
    project/src/parteUno/SegmentationAlgorithm.cpp
    project/test/parteUno/SegmentationTest.cpp
    )

add_executable(aed3_2019_1c_tp2 main.cpp ${SOURCE_FILES})

        set(SEGMENTACION_FILES
        project/src/entity/core/Graph.h
        project/src/entity/core/AdjacencyListGraph.h
        project/src/entity/core/impl/AdjacencyListGraph.cpp
        project/src/entity/auxiliar/impl/AdjacencyNode.cpp
        project/src/entity/auxiliar/AdjacencyNode.h
                project/src/utils/DisjoinSet.h
        project/src/utils/ArrayDisjoinSet.h
                project/src/utils/impl/ArrayDisjoinSet.cpp
                project/src/utils/ArrayCompressedDisjoinSet.h
                project/src/utils/impl/ArrayCompressedDisjoinSet.cpp
                project/src/utils/TreeCompressedDisjoinSet.h
                project/src/utils/impl/TreeCompressedDisjoinSet.cpp
                project/src/utils/TreeDisjoinSet.h
                project/src/utils/impl/TreeDisjoinSet.cpp
                project/src/entity/auxiliar/impl/DirectedTreeGraph.cpp
                project/src/entity/auxiliar/DirectedTreeGraph.h
                project/src/entity/auxiliar/impl/TreeNode.cpp
                project/src/entity/auxiliar/TreeNode.h
        project/src/utils/GetMST.h
        project/src/utils/impl/GetMST.cpp
        project/src/entity/core/Edge.h
        project/src/entity/core/impl/Edge.cpp
        project/src/entity/auxiliar/impl/DirectedTreeGraph.cpp
        project/src/entity/auxiliar/DirectedTreeGraph.h
        project/src/entity/auxiliar/impl/TreeNode.cpp
        project/src/entity/auxiliar/TreeNode.h
        project/src/utils/impl/TreeDisjoinSet.cpp
        project/src/utils/TreeDisjoinSet.h
        project/src/utils/impl/TreeCompressedDisjoinSet.cpp
        project/src/utils/TreeCompressedDisjoinSet.h
        project/src/parteUno/SegmentationAlgorithm.h
        project/src/parteUno/SegmentationAlgorithm.cpp
        )

add_executable(runSegmentacion RunSegmentacion.cpp ${SEGMENTACION_FILES})


target_link_libraries(aed3_2019_1c_tp2 gtest gtest_main)


#target_link_libraries(RunSegmentation segLib)
add_executable(ExperimentacionSegmentacion project/src/experiments/segmentacion/experimento-segmentacion-1.cpp ${SEGMENTACION_FILES})

set(SOURCE_FILES_MIN_PATH
    project/src/algorithms/bellman-ford.hpp
    project/src/algorithms/dijkstra-with-fifo-queue.hpp
    project/src/algorithms/dijkstra-with-priority-queue.hpp
    project/src/algorithms/floyd-warshall.hpp
    project/src/algorithms/edge-weighted-graph-bellman-ford.hpp
    project/src/entity/EdgeWeightedGraph.h
    project/src/entity/GasGraph.h
    project/src/entity/impl/EdgeWeightedGraph.cpp
    project/src/entity/impl/GasGraph.cpp)
add_executable(main-min-path main-min-path.cpp ${SOURCE_FILES_MIN_PATH})


#target_link_libraries(aed3_2019_1c_tp2 gtest gtest_main runSegmentacion)
target_link_libraries(aed3_2019_1c_tp2 gtest gtest_main)



add_library( YourLib ${SEGMENTACION_FILES} )

#
#foreach( testsourcefile ${APP_SOURCES} )
#        add_executable( ${testname} ${testsourcefile} )
#        # Make sure YourLib is linked to each app
#        target_link_libraries( ${testname} YourLib )
#endforeach( testsourcefile ${APP_SOURCES} )
add_executable(timer project/src/experiments/timer.cpp ${SOURCE_FILES_MIN_PATH})
