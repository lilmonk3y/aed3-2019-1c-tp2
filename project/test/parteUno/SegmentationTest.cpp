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
        vector<vector<int> > imagen = {{1}};
        int segmentationScaleDefault = 2;
        int anchoDefault =1;
        int altoDefault =1;
        segmentationAlgorithm = new SegmentationAlgorithm(imagen,segmentationScaleDefault,anchoDefault,altoDefault);
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


    //segmentationScale = 2; // con 1 falla,con 100 anda bien, con 1000 falla
    segmentationAlgorithm->setGrafo(grafo);
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
    segmentationAlgorithm->setScaleProportion(segmentationScale);
    segmentationAlgorithm->setGrafo(grafo);
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

TEST_F(SegmentationAlgorithmTest, segmentacionDeUnaImagenChiquita) {
    vector<vector<int> > imagen =    {
            {0,0,200,0},
            {0,0,0,0},
            {0,0,200,0},
            {0,0,200,0},
            {100,0,200,0},
            {0,0,200,0},
            {0,0,200,0}

    };
    int ancho = 4;
    int alto = 7;
    int scale = 2;
    segmentationAlgorithm = new SegmentationAlgorithm(imagen,scale,ancho,alto); // usar otra configuracion
    vector<vector<int> > imagenSegmentada = segmentationAlgorithm->imageToSegmentation();
    ASSERT_TRUE(segmentationAlgorithm->cantidadDeComponentes(imagenSegmentada, ancho, alto)==4); // el fondo, el puntito arriba, el puntito a la izquirda, y el palito en el medio
}

TEST_F(SegmentationAlgorithmTest, segmentacionDeUnaImagenConUnaCruz) {
    vector<vector<int> > imagen =    {
            {50,0,50},
            {0,50,0},
            {50,0,50}
    };
    int ancho = 3;
    int alto = 3;
    int scale = 2;
    segmentationAlgorithm = new SegmentationAlgorithm(imagen,scale,ancho,alto); // usar otra configuracion
    vector<vector<int> > imagenSegmentada = segmentationAlgorithm->imageToSegmentation();
    ASSERT_TRUE(segmentationAlgorithm->cantidadDeComponentes(imagenSegmentada, ancho, alto)==2);
}

TEST_F(SegmentationAlgorithmTest, imagenGrandeAGrafo){
    vector<vector<int> > imagen = {{248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,189,103,34,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,189,103,34,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,232,121,36,0,0,0,248,248,248,248,248,248,248,248,248,248,248,248,248,232,121,36,0,0,0,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,232,110,17,0,0,0,0,0,248,248,248,248,248,248,248,248,248,248,248,232,110,17,0,0,0,0,0,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,147,19,0,0,0,0,0,0,0,248,248,248,248,248,248,248,248,248,248,147,19,0,0,0,0,0,0,0,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,227,65,0,0,0,0,0,0,12,87,189,248,248,248,248,248,248,248,248,227,65,0,0,0,0,0,0,12,87,189,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,195,28,0,0,0,0,0,0,72,215,248,248,248,248,248,248,248,248,248,195,28,0,0,0,0,0,0,72,215,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,195,17,0,0,0,0,0,6,137,248,248,248,248,248,248,248,248,248,248,195,17,0,0,0,0,0,6,137,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,207,19,0,0,0,0,0,6,159,248,248,248,248,248,248,248,248,248,248,207,19,0,0,0,0,0,6,159,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,238,43,0,0,0,0,0,0,121,248,248,248,248,248,248,248,248,248,248,238,43,0,0,0,0,0,0,121,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,110,0,0,0,0,0,0,36,242,248,248,248,248,248,248,248,248,248,248,110,0,0,0,0,0,0,36,242,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,215,6,0,0,0,0,0,0,137,248,248,248,248,248,248,248,248,248,248,215,6,0,0,0,0,0,0,137,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,94,0,0,0,0,0,0,0,215,248,248,248,248,248,248,248,248,248,248,94,0,0,0,0,0,0,0,215,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,238,17,0,0,0,0,0,0,0,238,248,248,248,248,248,248,248,248,248,238,17,0,0,0,0,0,0,0,238,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,177,0,0,0,0,0,0,0,0,177,248,248,248,248,248,248,248,248,248,177,0,0,0,0,0,0,0,0,177,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,113,0,0,0,0,0,0,0,0,24,195,248,248,248,248,248,248,248,248,113,0,0,0,0,0,0,0,0,24,195,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,58,0,0,0,0,0,0,0,0,0,6,113,242,248,248,248,248,248,248,58,0,0,0,0,0,0,0,0,0,6,113,242,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,36,0,0,0,0,0,0,0,0,0,0,0,43,215,248,248,248,248,248,36,0,0,0,0,0,0,0,0,0,0,0,43,215,248,248,248,248,248,248},
                                   {248,248,248,248,248,19,0,0,0,0,0,0,0,0,0,0,0,0,36,238,248,248,248,248,19,0,0,0,0,0,0,0,0,0,0,0,0,36,238,248,248,248,248,248},
                                   {248,248,248,248,248,6,0,0,0,0,0,0,0,0,0,0,0,0,0,121,248,248,248,248,6,0,0,0,0,0,0,0,0,0,0,0,0,0,121,248,248,248,248,248},
                                   {248,248,248,248,248,19,0,0,0,0,0,0,0,0,0,0,0,0,0,43,248,248,248,248,19,0,0,0,0,0,0,0,0,0,0,0,0,0,43,248,248,248,248,248},
                                   {248,248,248,248,248,43,0,0,0,0,0,0,0,0,0,0,0,0,0,17,248,248,248,248,43,0,0,0,0,0,0,0,0,0,0,0,0,0,17,248,248,248,248,248},
                                   {248,248,248,248,248,110,0,0,0,0,0,0,0,0,0,0,0,0,0,12,248,248,248,248,110,0,0,0,0,0,0,0,0,0,0,0,0,0,12,248,248,248,248,248},
                                   {248,248,248,248,248,207,6,0,0,0,0,0,0,0,0,0,0,0,0,36,248,248,248,248,207,6,0,0,0,0,0,0,0,0,0,0,0,0,36,248,248,248,248,248},
                                   {248,248,248,248,248,248,103,0,0,0,0,0,0,0,0,0,0,0,0,113,248,248,248,248,248,103,0,0,0,0,0,0,0,0,0,0,0,0,113,248,248,248,248,248},
                                   {248,248,248,248,248,248,242,65,0,0,0,0,0,0,0,0,0,0,28,232,248,248,248,248,248,242,65,0,0,0,0,0,0,0,0,0,0,28,232,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,242,103,6,0,0,0,0,0,0,0,36,207,248,248,248,248,248,248,248,242,103,6,0,0,0,0,0,0,0,36,207,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,215,103,43,17,6,24,65,147,242,248,248,248,248,248,248,248,248,248,248,215,103,43,17,6,24,65,147,242,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248}};


    int ancho = 44;
    int alto = 33;

    AdjacencyListGraph* imageGraph = segmentationAlgorithm->imageToGraph(&imagen,ancho,alto);

    ASSERT_TRUE(imageGraph->getEdges()->size()==5579);
    ASSERT_TRUE(imageGraph->getVertex()==44*33);
    ASSERT_TRUE(imageGraph->getNeighbors(440+32).size() ==8);// nodo cualquiera de por el medio
    ASSERT_TRUE(imageGraph->getNeighbors(44*6+11).size() ==8);// nodo cualquiera de por el medio
    ASSERT_TRUE(imageGraph->getNeighbors(44*23+27).size() ==8);// nodo cualquiera de por el medio
    ASSERT_TRUE(imageGraph->getNeighbors(44*(alto-1)+0).size() ==3);// nodo esquina inferior izquierda
    ASSERT_TRUE(imageGraph->getNeighbors(44*(alto-1)+14).size() ==5);// nodo cualquier ultima fila
}


TEST_F(SegmentationAlgorithmTest, segmentacionImagenComillas){
    vector<vector<int> > imagen = {{248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,189,103,34,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,189,103,34,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,232,121,36,0,0,0,248,248,248,248,248,248,248,248,248,248,248,248,248,232,121,36,0,0,0,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,232,110,17,0,0,0,0,0,248,248,248,248,248,248,248,248,248,248,248,232,110,17,0,0,0,0,0,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,147,19,0,0,0,0,0,0,0,248,248,248,248,248,248,248,248,248,248,147,19,0,0,0,0,0,0,0,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,227,65,0,0,0,0,0,0,12,87,189,248,248,248,248,248,248,248,248,227,65,0,0,0,0,0,0,12,87,189,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,195,28,0,0,0,0,0,0,72,215,248,248,248,248,248,248,248,248,248,195,28,0,0,0,0,0,0,72,215,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,195,17,0,0,0,0,0,6,137,248,248,248,248,248,248,248,248,248,248,195,17,0,0,0,0,0,6,137,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,207,19,0,0,0,0,0,6,159,248,248,248,248,248,248,248,248,248,248,207,19,0,0,0,0,0,6,159,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,238,43,0,0,0,0,0,0,121,248,248,248,248,248,248,248,248,248,248,238,43,0,0,0,0,0,0,121,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,110,0,0,0,0,0,0,36,242,248,248,248,248,248,248,248,248,248,248,110,0,0,0,0,0,0,36,242,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,215,6,0,0,0,0,0,0,137,248,248,248,248,248,248,248,248,248,248,215,6,0,0,0,0,0,0,137,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,94,0,0,0,0,0,0,0,215,248,248,248,248,248,248,248,248,248,248,94,0,0,0,0,0,0,0,215,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,238,17,0,0,0,0,0,0,0,238,248,248,248,248,248,248,248,248,248,238,17,0,0,0,0,0,0,0,238,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,177,0,0,0,0,0,0,0,0,177,248,248,248,248,248,248,248,248,248,177,0,0,0,0,0,0,0,0,177,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,113,0,0,0,0,0,0,0,0,24,195,248,248,248,248,248,248,248,248,113,0,0,0,0,0,0,0,0,24,195,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,58,0,0,0,0,0,0,0,0,0,6,113,242,248,248,248,248,248,248,58,0,0,0,0,0,0,0,0,0,6,113,242,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,36,0,0,0,0,0,0,0,0,0,0,0,43,215,248,248,248,248,248,36,0,0,0,0,0,0,0,0,0,0,0,43,215,248,248,248,248,248,248},
                                   {248,248,248,248,248,19,0,0,0,0,0,0,0,0,0,0,0,0,36,238,248,248,248,248,19,0,0,0,0,0,0,0,0,0,0,0,0,36,238,248,248,248,248,248},
                                   {248,248,248,248,248,6,0,0,0,0,0,0,0,0,0,0,0,0,0,121,248,248,248,248,6,0,0,0,0,0,0,0,0,0,0,0,0,0,121,248,248,248,248,248},
                                   {248,248,248,248,248,19,0,0,0,0,0,0,0,0,0,0,0,0,0,43,248,248,248,248,19,0,0,0,0,0,0,0,0,0,0,0,0,0,43,248,248,248,248,248},
                                   {248,248,248,248,248,43,0,0,0,0,0,0,0,0,0,0,0,0,0,17,248,248,248,248,43,0,0,0,0,0,0,0,0,0,0,0,0,0,17,248,248,248,248,248},
                                   {248,248,248,248,248,110,0,0,0,0,0,0,0,0,0,0,0,0,0,12,248,248,248,248,110,0,0,0,0,0,0,0,0,0,0,0,0,0,12,248,248,248,248,248},
                                   {248,248,248,248,248,207,6,0,0,0,0,0,0,0,0,0,0,0,0,36,248,248,248,248,207,6,0,0,0,0,0,0,0,0,0,0,0,0,36,248,248,248,248,248},
                                   {248,248,248,248,248,248,103,0,0,0,0,0,0,0,0,0,0,0,0,113,248,248,248,248,248,103,0,0,0,0,0,0,0,0,0,0,0,0,113,248,248,248,248,248},
                                   {248,248,248,248,248,248,242,65,0,0,0,0,0,0,0,0,0,0,28,232,248,248,248,248,248,242,65,0,0,0,0,0,0,0,0,0,0,28,232,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,242,103,6,0,0,0,0,0,0,0,36,207,248,248,248,248,248,248,248,242,103,6,0,0,0,0,0,0,0,36,207,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,215,103,43,17,6,24,65,147,242,248,248,248,248,248,248,248,248,248,248,215,103,43,17,6,24,65,147,242,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248}};

    int ancho = 44;
    int alto = 33;
    int segmentationScale = 200; // con 150 hay 43 componentes
    // union del disjoint set tiene costo N

    segmentationAlgorithm = new SegmentationAlgorithm(imagen, segmentationScale, ancho, alto);
    vector<vector<int> > imagenSegmentada = segmentationAlgorithm->imageToSegmentation();
    cout << "cantidad componentes: " << endl ;
    cout << segmentationAlgorithm->cantidadDeComponentes(imagenSegmentada, ancho, alto) << endl;
    cout << "--------" << endl ;
    ASSERT_TRUE(segmentationAlgorithm->cantidadDeComponentes(imagenSegmentada, ancho, alto)==3);
}