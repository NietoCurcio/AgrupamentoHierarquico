/*  
    Questao 7 (extra) - Grupo: Felipe Curcio, Rodrigo Parracho

    Este codigo implementa o mesmo algoritmo da questao 5 e 6,
    mas neste é possivel inserir valor pra extroversao e idade em cada node,
    também é calculado a distancia euclidiana como peso para cada aresta (ver função insertEdges).
    
    A função "void insertEdges(Graph &G);"
    insere as arestas fazendo a leitura do dataset MQD500.graphml.

    Como os id's são definidos pelo dataset, houveram diversas adaptações no código.
*/ 
#include<iostream> // Biblioteca padrao de entrada e saida
// #include "MyDynamicArrayLk.h" // Essa biblioteca foi implementada por mim no arquivo MyDynamicArrayRealloc.h
#include "MyDynamicArrayRealloc.h" // Essa biblioteca foi implementada por mim no arquivo MyDynamicArrayRealloc.h
#include <fstream> // Essa biblioteca é para leitura e escrita de arquivos
#include <string> // Biblioteca necessaria para leitura de arquivos em c++ (função getline)
#include <cmath> // Usada apenas na função sqrt(), para calcular a distancia euclidiana.

using namespace std;
// using namespace MyDynamicArrayLkSpace;
using namespace MyDynamicArrayReallocSpace;

class Edge {
    public:
        double weight;
        int nodeIdU;
        int nodeIdV;

        void setWeight(double weight) {
            this->weight = weight;
        }

        void setNodeIdU(int idU) {
            nodeIdU = idU;
        }

        void setNodeIdV(int idV) {
            nodeIdV = idV;
        }
};

class Node {
    public:
        int id;

        double idade;
        double extroversao;
        DynamicArray<Edge> edges;

        Node(int id) {
            this->id = id;
        }

        Node(int id, double idade, double extroversao) {
            this->id = id;
            this->idade = idade;
            this->extroversao = extroversao;
        }

        void connect(Node* node, double weight) {
            Edge e;
            e.setWeight(weight);
            e.setNodeIdU(this->id);
            e.setNodeIdV(node->id);
            this->edges.push(e);
        }

        void connect(Node* node, Edge e) {
            int tmp;
            if(this->id == e.nodeIdV) {
                tmp = e.nodeIdU;
                e.setNodeIdU(e.nodeIdV);
                e.setNodeIdV(tmp);
            }
            this->edges.push(e);
        }

        // bool hasEdgeConnectedTo(int nodeIdV) {
        //     DynamicArray<Edge> es = edges;
        //     for(int i = 0; i < es.length; i++) {
        //         Edge e = es[i];
        //         if(e.nodeIdV == nodeIdV) return true;
        //     }
        //     return false;
        // }

        // Edge getEdgeConnectedTo(int nodeIdV) {
        //     Edge e;
        //     for(int i = 0; i < edges.length; i++) {
        //         if(edges[i].nodeIdV == nodeIdV) {
        //              e = edges[i];
        //              break;
        //         }
        //     }
        //     return e;
        // }

        int getEdgeConnectedTo(int nodeIdV) {
            int index = -1;
            for(int i = 0; i < edges.length; i++) {
                if(edges[i].nodeIdV == nodeIdV) {
                     index = i;
                     break;
                }
            }
            return index;
        }
};

class Graph {
    public:
        int nodes_length = 0;
        DynamicArray<Node*> nodes;

        Graph() {}

        Node* getNode(int id) {
            Node* node;
            for(int i = 0; i < nodes.length; i++) {
                if(id == nodes[i]->id) {
                    node = nodes[i];
                    break;
                }
            }
            return node;
        }

        int getNodeIdx(int id) {
            int i = 0;
            while(i < nodes.length) {
                if(id == nodes[i]->id) break;
                i++;
            }
            return i;
        }

        void insertNode(Node* n) {
            nodes.push(n);
            nodes_length++;
        }

        void insertEdge(Node* a, Node* b, double weight) {
            a->connect(b, weight);
        }

        void insertEdge(Node* a, Node* b, Edge e) {
            a->connect(b, e);
        }

        void pushEdge(Edge e, Node* u) {
            u->edges.push(e);
        }

        bool isConnected() {
            DynamicArray<bool> explored(nodes_length, false);
            Node* first = nullptr;

            for(int i = 0; i < nodes.length; i++) {
                 if (nodes[i]->edges.length) {
                     first = nodes[i];
                     break;
                 }
            }

            if(first == nullptr) return false;

            DynamicArray<Node*> nodesToExplore;
            nodesToExplore.push(first);
            while(nodesToExplore.length > 0) {
                Node* n = nodesToExplore.pop();
                int index = this->getNodeIdx(n->id);

                if (explored[index]) continue;
                explored[index] = true;

                DynamicArray<Edge> edges = n->edges;
                for(int i = 0; i < edges.length; i++) {
                    int u = edges[i].nodeIdU;
                    int v = edges[i].nodeIdV;
                    Node* nodeEdge = this->getNode(v);
                    nodesToExplore.push(nodeEdge);
                }
            }

            for(int i = 0; i < explored.length; i++) {
                if(!explored[i]) return false;
                
            }
            // explored.clear(); // only for MyDynamicArrayLk
            return true;
        }

        int getHeavierEdge(bool N[], DynamicArray<Edge> &edges) {
            int index;
            int greater = -1;
            int uId = -1;
            int vId = -1;
            for(int i = 0; i < edges.length; i++) {
                if (edges[i].weight > greater && !N[i]) {
                    greater = edges[i].weight;
                    index = i;
                }
            }
            return index;
        }

        void printConnected() {
            bool printed[500][500] = {{false}};
            bool explored[500] = {false};
            Node* first = nullptr;

            for(int i = 0; i < nodes.length; i++) {
                 if (nodes[i]->edges.length) {
                     first = nodes[i];
                     break;
                 }
            }

            DynamicArray<Node*> nodesToExplore;

            nodesToExplore.push(first);

            // cout << "Componentes conexas de G:" << endl;
            ofstream WriteFile("outputFromDataset.csv");
            while(nodesToExplore.length > 0) {
                Node* n = nodesToExplore.pop();

                int index = this->getNodeIdx(n->id);
                if (explored[index]) continue;
                explored[index] = true;

                DynamicArray<Edge> edges = n->edges;
                for(int i = 0; i < edges.length; i++) {
                    int uIndex = index;
                    int vIndex = getNodeIdx(edges[i].nodeIdV);

                    if(!printed[uIndex][vIndex]) {
                        // cout << u << "-->" << v << " ";
                        // cout << "felipe12" << endl;

                        WriteFile << uIndex << "-->" << vIndex << ",";
                        printed[uIndex][vIndex] = true;
                        printed[vIndex][uIndex] = true;
                    }
                    Node* nodeV = this->getNode(edges[i].nodeIdV);
                    nodesToExplore.push(nodeV);
                }
            }
            // cout << endl;
            WriteFile.close();
        }

        DynamicArray<DynamicArray<double>> getWeightMatrix() {
            DynamicArray<DynamicArray<double>> n(nodes_length, DynamicArray<double>(nodes_length, 0.0));
            for(int i = 0; i < nodes_length; i++) {
                int k = 0;
                Node *node = this->nodes[i];
                for(int j = 0; j < nodes_length; j++) {
                    int edgeIndex = node->getEdgeConnectedTo(nodes[j]->id);
                    if(edgeIndex != -1) {
                        Edge e = node->edges[edgeIndex];
                        n[i][j] = e.weight;
                        // if(n[i][j] == 0) n[i][j] = 0.0001;
                        // visto que entrei no "if", há a aresta, mas o peso é 0 
                        // por ser a distancia euclidiana, significa que sao dois vértices próximos
                        // então coloco um valor próximo de 0, para que o código em python
                        // entenda que a aresta existe.
                        k++;
                    }
                    if(k == node->edges.length) break;
                }
            }
            return n;
        }

        DynamicArray<Edge> clearEdges() {
            DynamicArray<Edge> edges;
            for(int i = 0; i < nodes.length; i++) {
                int edgesLength = nodes[i]->edges.length;
                for(int j = 0; j < edgesLength; j++) {
                    Edge e = nodes[i]->edges.pop();
                    edges.push(e);
                }
            }
            return edges;
        }

        void printState() {
            for(int i = 0; i < nodes_length; i++) {
                Node* n = nodes[i];
                cout << "Id: " << n->id << endl;
                cout << "Edges length: " << n->edges.length << endl;
                for(int j = 0; j < n->edges.length; j++) {
                    printf(
                        "%d --%f-> %d | ",
                        n->edges[j].nodeIdU,
                        n->edges[j].weight,
                        n->edges[j].nodeIdV
                        );
                }
                cout << endl;
            }
        }
};

int getNodeIdFromDataset(string row) {
    string increment="";
    for(int i = 0; i < row.length(); i++) {
        if(row[i] == '"') {
            int j = i + 2; // ignores '"' and 'u'
            while(row[j] != '"') {
                increment += row[j];
                j++;
            }
            break;
        }
    }
    return stoi(increment); // stoi = string to int
}

double getNodeDataFromDataset(string row) {
    string increment="";
    for(int i = 0; i < row.length(); i++) {
        if(row[i] == '>') {
            int j = i + 1; // ignores '>'
            while(row[j] != '<') {
                increment += row[j];
                j++;
            }
            break;
        }
    }
    return stod(increment); // stod = string to double
}
int getNodeUIdFromDataset(string row) {
    string increment="";
    for(int i = 0; i < row.length(); i++) {
        if(row[i] == '"') {
            int j = i + 2; // ignores '"' and 'u'
            while(row[j] != '"') {
                increment += row[j];
                j++;
            }
            break;
        }
    }
    return stoi(increment);
}

int getNodeVIdFromDataset(string row) {
// <edge source="u1340" target="u3352"/>
    string increment="";
    int k = 0;
    for(int i = 0; i < row.length(); i++) {
        if(row[i] == '"') {
            k++;
            int j = i + 2; // ignores '"' and 'u'
            while(row[j] != '"' && k == 3) {
                increment += row[j];
                j++;
            }
            if(k == 3) break;
        }
    }
    return stoi(increment);
}

string getTag(string row) {
    string tag = "";
    int i = 1;
    while(i < 5) {
        tag += row[i];
        i++;
    } 
    return tag;
}

void insertEdges(Graph &G) {
    string row;
    ifstream dataset("./MQD500.graphml");
    // skip first 7 lines
    for(int i = 0; i < 7; i++) getline(dataset, row);
    while (getline(dataset, row)) {
        string tag = getTag(row);
        // cout << tag << endl;
        if (tag.compare("node") == 0) {
            int id = getNodeIdFromDataset(row);
            getline(dataset, row);
            double idade = getNodeDataFromDataset(row);
            getline(dataset, row);
            double extroversao = getNodeDataFromDataset(row);
            getline(dataset, row); // end tag </node>
            Node* node = new Node(id, idade, extroversao);
            G.insertNode(node);
        }
        if (tag.compare("edge") == 0) {   
            int uId = getNodeUIdFromDataset(row);
            int vId = getNodeVIdFromDataset(row);
            // "Observe que os pesos para as arestas podem ser calculados de maneira aleatória"
            // Professor, decidi fazer o peso sendo a distancia euclidiana entre um node e outro
            // ou seja, distancia entre dois vetores bidimensionais (idade e extroversao)
            // Dessa forma, faço uso da informação idade e extroversão
            Node* nodeu = G.getNode(uId);
            Node* nodev = G.getNode(vId);
            double idadeDif = (nodeu->idade - nodev->idade);
            double extroversaoDif = (nodeu->extroversao - nodev->extroversao);
            idadeDif *= idadeDif;
            extroversaoDif *= extroversaoDif;
            double euclideanDistance = sqrt(idadeDif + extroversaoDif);
            // coloco como peso o inverso da distancia euclidiana, pois, se os nodes
            // são próximos sua distancia é zero, e pelo algoritmo de agrupamento hierarquico
            // eu preciso pegar a aresta de o maior peso (relação mais forte). Da mesma forma,
            // se a distancia é um grande valor, seu inverso é um valor menor, que indica
            // uma relação fraca.
            if(euclideanDistance == 0) euclideanDistance = 1 / 0.0001;
            else euclideanDistance = 1 / euclideanDistance;
            // Se for 0, normalizo como 0.0001, para calcular seu inverso
            G.insertEdge(nodeu, nodev, euclideanDistance);
            G.insertEdge(nodev, nodeu, euclideanDistance);
        }
    }
    dataset.close();
    cout << G.nodes_length << " Nodes inserted" << endl;
}

int main(int argc, char* argv[]) {
    int nodes_length = 13;
    Graph G;

    insertEdges(G);

    // G.printState();

    ofstream MyFile("weightsMatrixFromDataset.csv");

    DynamicArray<DynamicArray<double>> matrix = G.getWeightMatrix();
    for(int i = 0; i < G.nodes.length; i++) {
        for(int j = 0; j < G.nodes.length; j++) {
            // cout << matrix[i][j] << " ";
            if (j == G.nodes.length - 1) {
                MyFile << matrix[i][j] << "\n";
            } else {
                MyFile << matrix[i][j] << ",";
            }
        }
        // cout << "\n";
    }
    MyFile.close();
    // matrix.clear(); //only for MyDynamicArrayLk
    cout << "Weights Matrix generated" << endl;

    DynamicArray<Edge> edges = G.clearEdges();
    cout << edges.length << " Total edges (a->b and b->a counts as 2)" << endl;

    // G.printState();

    bool* N = new bool[edges.length]{};
    cout << "Running algorithm..." << endl;
    int z = 0;
    while(!G.isConnected()) {
        // no questao5e6_v2.cpp, os id's são iguais a seus indices,
        // o node de id 0, esta na posicao 0 de G.nodes, neste aqui o id não tem esse comportamento
        // portanto, alterei as funções "isConnected", "getHeavierEdge", "printConnected" e "clearEdges"
        int edgeIndex = G.getHeavierEdge(N, edges);
        Edge e = edges[edgeIndex];
        G.insertEdge(G.getNode(e.nodeIdU), G.getNode(e.nodeIdV), e);
        G.insertEdge(G.getNode(e.nodeIdV), G.getNode(e.nodeIdU), e);
        N[edgeIndex] = true;
        z++;
        cout << z << endl;
    }
    G.printConnected();

    cout << "Output generated" << endl;
    // G.printState();
    delete[] N;
    return 0;
}