#include "gtest/gtest.h"
#include "../../src/parteUno/SegmentationAlgorithm.h"
#include "../../src/utils/DisjoinSet.h"
#include "../../src/utils/ArrayDisjoinSet.h"
#include "../../src/utils/GetMST.h"
#include <set>
#include <map>
using namespace std;


struct SegmentationAlgorithmTest : testing::Test{
    SegmentationAlgorithm* segmentationAlgorithm;

    SegmentationAlgorithmTest(){
        AdjacencyListGraph* grafo =  new AdjacencyListGraph(1);
        int segmentationScale = 2;
        segmentationAlgorithm = new SegmentationAlgorithm(grafo,segmentationScale);
    }

    ~SegmentationAlgorithmTest(){
        delete segmentationAlgorithm;
    }
};


TEST_F(SegmentationAlgorithmTest, simpleSegmentationWorks){
    AdjacencyListGraph* grafo =  new AdjacencyListGraph(4);
    grafo->addEdge(0, 1, 2);
    grafo->addEdge(1, 2, 180);
    grafo->addEdge(2, 3, 160);
    grafo->addEdge(3, 1, 200);


    int segmentationScale = 2; // con 1 falla,con 100 anda bien, con 1000 falla
    segmentationAlgorithm = new SegmentationAlgorithm(grafo,segmentationScale);
    DisjoinSet* disjointSet = segmentationAlgorithm->graphSementationIntoSets();

    ASSERT_TRUE(disjointSet->find(0) == disjointSet->find(1) );
    ASSERT_TRUE(disjointSet->find(1) != disjointSet->find(2) &&  disjointSet->find(2) != disjointSet->find(3));
}

TEST_F(SegmentationAlgorithmTest, image3x3pixelsWith3Areas){
    AdjacencyListGraph* grafo =  new AdjacencyListGraph(9);


    // 20 aristas:

    //0:
    grafo->addEdge(0, 1, 174);
    grafo->addEdge(0, 3, 5);
    grafo->addEdge(0, 4, 189);

    //1:
    grafo->addEdge(1, 2, 4 );
    grafo->addEdge(1, 4, 220);
    grafo->addEdge(1, 5, 150);

    //2:
    grafo->addEdge(2, 5, 100 );
    grafo->addEdge(2, 4, 170 );

    //3:
    grafo->addEdge(3, 4, 210 );
    grafo->addEdge(3, 6, 195 );
    grafo->addEdge(3, 1, 199 );
    grafo->addEdge(3, 7, 159 );

    //5:
    grafo->addEdge(5,4 ,200  );
    grafo->addEdge(5,8 , 4 );

    //6:
    grafo->addEdge(6,4 , 4  );
    grafo->addEdge(6,7 , 2 );

    //7:
    grafo->addEdge(7,4 , 0  );
    grafo->addEdge(7,8 , 180  );
    grafo->addEdge(7,5 , 177  );

    //8:
    grafo->addEdge(8,4 , 160);

    int segmentationScale = 50; // esto es la diferencia minima entre componentes para diferenciarse 50 anda bien
    // 199 se rompe
    segmentationAlgorithm = new SegmentationAlgorithm(grafo,segmentationScale);
    DisjoinSet* disjointSet = segmentationAlgorithm->graphSementationIntoSets();

    ASSERT_TRUE(disjointSet->find(0) == disjointSet->find(3) );

    ASSERT_TRUE(disjointSet->find(1) == disjointSet->find(2) );

    ASSERT_TRUE(disjointSet->find(4) == disjointSet->find(6) );
    ASSERT_TRUE(disjointSet->find(6) == disjointSet->find(7) );

    ASSERT_TRUE(disjointSet->find(5) == disjointSet->find(8) );

    ASSERT_TRUE(disjointSet->find(0) != disjointSet->find(1) );
    ASSERT_TRUE(disjointSet->find(2) != disjointSet->find(5) );
    ASSERT_TRUE(disjointSet->find(8) != disjointSet->find(7) );
    ASSERT_TRUE(disjointSet->find(3) != disjointSet->find(6) );
    ASSERT_TRUE(disjointSet->find(4) != disjointSet->find(1) );
}


TEST_F(SegmentationAlgorithmTest, matrizImagenAGrafo){
    vector<vector<int> > imagen;

    vector<int> fila0 = {0,0,0};
    vector<int> fila1 = {0,0,0};
    vector<int> fila2 = {0,0,0};
    vector<int> fila3 = {0,0,0};
    imagen = {fila0,fila1,fila2,fila3};
    int ancho =3;
    int alto =4;

    AdjacencyListGraph* imageGraph = segmentationAlgorithm->imageToGraph(&imagen,ancho,alto);

    ASSERT_TRUE(imageGraph->getVertex()==12); // cantidad de vertices
    ASSERT_TRUE(imageGraph->getTotalCost()==0);
    ASSERT_TRUE(imageGraph->getEdges()->size()==29); // todos los ejes que hay
}

TEST_F(SegmentationAlgorithmTest, matrizImagenAGrafoPesosTest){
    vector<vector<int> > imagen;

    vector<int> fila0 = {0,0,30};
    vector<int> fila1 = {0,100,0};
    vector<int> fila2 = {0,50,0};
    vector<int> fila3 = {0,0,0};
    imagen = {fila0,fila1,fila2,fila3};
    int ancho =3;
    int alto =4;

    AdjacencyListGraph* imageGraph = segmentationAlgorithm->imageToGraph(&imagen,ancho,alto);
    ASSERT_TRUE(imageGraph->getVertex()==12);
    cout << imageGraph->getTotalCost() << endl;
    int sumValues = 100+100+70+100+100+100+50+100; // vertex 100
    sumValues = sumValues + 30+30; // vertex 30 (70 ya esta en la linea anterior)
    sumValues = sumValues + 50+50+50+50+50+50+50; // valores asociado al vertice 50

    ASSERT_TRUE(imageGraph->getTotalCost()==sumValues); // no sabe que estoy agregando el mismo eje muchas veces
}

TEST_F(SegmentationAlgorithmTest, sumaDePesosCorrecta){
    vector<vector<int> > imagen;

    vector<int> fila0 = {0,0,0};
    vector<int> fila1 = {0,1,0};
    vector<int> fila2 = {0,0,0};
    vector<int> fila3 = {0,0,0};
    imagen = {fila0,fila1,fila2,fila3};
    int ancho =3;
    int alto =4;

    AdjacencyListGraph* imageGraph = segmentationAlgorithm->imageToGraph(&imagen,ancho,alto);

    ASSERT_TRUE(imageGraph->getVertex()==12); // cantidad de vertices
    ASSERT_TRUE(imageGraph->getTotalCost()==8);
    ASSERT_TRUE(imageGraph->getEdges()->size()==29); // todos los ejes que hay
}

TEST_F(SegmentationAlgorithmTest, sumaDePesosCorrectaOtroTest){
    vector<vector<int> > imagen;

    vector<int> fila0 = {0,0,0};
    vector<int> fila1 = {0,1,0};
    vector<int> fila2 = {0,0,2};
    imagen = {fila0,fila1,fila2};
    int ancho =3;
    int alto =3;

    AdjacencyListGraph* imageGraph = segmentationAlgorithm->imageToGraph(&imagen,ancho,alto);

    ASSERT_TRUE(imageGraph->getVertex()==9); // cantidad de vertices
    ASSERT_TRUE(imageGraph->getTotalCost()==7+1+2+2);
    ASSERT_TRUE(imageGraph->getEdges()->size()==20); // todos los ejes que hay
}