// QUESTAO 5 PROJETO FINAL
// GRUPO - Felipe Curcio, Rodrigo Parracho
#include<iostream> // Biblioteca padrao de entrada e saida
#include "MyDynamicArrayRealloc.h" // Essa biblioteca foi implementada por mim no arquivo MyDynamicArrayRealloc.h
#include <fstream> // Essa biblioteca é apenas para leitura e escrita de arquivos

using namespace std;
using namespace MyDynamicArrayReallocSpace;

class Edge {
    public:
        int weight;
        int nodeIdU;
        int nodeIdV;

        void setWeight(int weight) {
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
        DynamicArray<Edge> edges;

        Node(int id) {
            this->id = id;
        }

        void connect(Node* node, int weight) {
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

        bool hasEdgeConnectedTo(int nodeIdV) {
            DynamicArray<Edge> es = edges;
            for(int i = 0; i < edges.length; i++) {
                Edge e = es[i];
                if(e.nodeIdV == nodeIdV) return true;
            }
            return false;
        }

        Edge getEdgeConnectedTo(int nodeIdV) {
            Edge e;
            for(int i = 0; i < edges.length; i++) {
                if(edges[i].nodeIdV == nodeIdV) {
                     e = edges[i];
                     break;
                }
            }
            return e;
        }
};

class Graph {
    public:
        int nodes_length;
        DynamicArray<Node*> nodes;

        Graph(int n_length) : nodes_length(n_length) {}

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

        void insertNode(Node* n) {
            nodes.push(n);
        }

        void insertEdge(Node* a, Node* b, int weight) {
            a->connect(b, weight);
        }

        void insertEdge(Node* a, Node* b, Edge e) {
            a->connect(b, e);
        }

        bool isConnected() {
            DynamicArray<bool> explored(nodes_length, false);
            Node* first = nullptr;

            // start with a node that has at least one edge
            for(int i = 0; i < nodes.length; i++) {
                 if (nodes[i]->edges.length) {
                     first = nodes[i];
                     break;
                 }
            }

            if(first == nullptr) return false;

            // dfs
            DynamicArray<Node*> nodesToExplore;
            nodesToExplore.push(first);

            while(nodesToExplore.length > 0) {
                Node* n = nodesToExplore.pop();

                if (explored[n->id]) {
                    continue;
                }
                explored[n->id] = true;

                DynamicArray<Edge> edges = n->edges;

                for(int i = 0; i < edges.length; i++) {
                    Node* nodeEdge = this->getNode(edges[i].nodeIdV);
                    nodesToExplore.push(nodeEdge);
                }
            }
            for(int i = 0; i < explored.length; i++) {
                if(!explored[i]) return false;
                // for test only, commented
                // if(explored[i]) printf("true\n");
                // else printf("false\n");
            }
            // explored.clear(); only for MyDynamicArrayLk
            return true;
        }

        Edge getHeavierEdge(DynamicArray<DynamicArray<bool>> &N, DynamicArray<DynamicArray<int>> &matrix) {
            Edge e;
            int greater = -1;
            int uId = -1;
            int vId = -1;
            for(int i = 0; i < matrix.length; i++) {
                for(int j = 0; j < matrix.length; j++) {
                    if (matrix[i][j] > greater && !N[i][j] && i != j) {
                        greater = matrix[i][j];
                        uId = i;
                        vId = j;
                    } 
                }
            }
            e.setWeight(greater);
            e.setNodeIdU(uId);
            e.setNodeIdV(vId);
            return e;
        }

        Edge getLighterEdge(DynamicArray<DynamicArray<bool>> &N, DynamicArray<DynamicArray<int>> &matrix) {
            Edge e;
            int smaller = getHeavierEdge(N, matrix).weight;
            int uId = -1;
            int vId = -1;
            for(int i = 0; i < matrix.length; i++) {
                for(int j = 0; j < matrix.length; j++) {
                    if (matrix[i][j] <= smaller && !N[i][j] && i != j) {
                        smaller = matrix[i][j];
                        uId = i;
                        vId = j;
                    } 
                }
            }
            e.setWeight(smaller);
            e.setNodeIdU(uId);
            e.setNodeIdV(vId);
            return e;
        }

        void printConnected() {
            DynamicArray<bool> explored(nodes_length, false);
            DynamicArray<DynamicArray<bool>> printed(nodes_length, DynamicArray<bool>(nodes_length, false));
            Node* first = nullptr;

            for(int i = 0; i < nodes.length; i++) {
                 if (nodes[i]->edges.length) {
                     first = nodes[i];
                     break;
                 }
            }

            DynamicArray<Node*> nodesToExplore;
            nodesToExplore.push(first);
            cout << "Componentes conexas de G:" << endl;
            ofstream WriteFile("output.csv");
            while(nodesToExplore.length > 0) {
                Node* n = nodesToExplore.pop();

                if (explored[n->id]) continue;
                explored[n->id] = true;

                DynamicArray<Edge> edges = n->edges;
                for(int i = 0; i < edges.length; i++) {
                    int u = edges[i].nodeIdU;
                    int v = edges[i].nodeIdV;
                    if(!printed[u][v]) {
                        cout << u << "-->" << v << " ";
                        WriteFile << u << "-->" << v << ",";
                        printed[u][v] = true;
                        printed[v][u] = true;
                        // simetria por ser nao direcionado
                    }                    
                    Node* nodeV = this->getNode(v);
                    nodesToExplore.push(nodeV);
                }
            }
            cout << endl;
            WriteFile.close();
        }

        DynamicArray<DynamicArray<int>> getWeightMatrix() {
            DynamicArray<DynamicArray<int>> n(nodes_length, DynamicArray<int>(nodes_length, 0));
            for(int i = 0; i < nodes_length; i++) {
                int k = 0;
                Node* node = this->nodes[i];
                for(int j = 0; j < nodes_length; j++) {
                    if(node->hasEdgeConnectedTo(j)) {
                        Edge e = node->getEdgeConnectedTo(j);
                        int w = e.weight;
                        n[i][j] = w;
                        k++;
                    }
                    if(k == node->edges.length) break; // found all edges of this node
                }
            }
            return n;
        }

        void clearEdges() {
            for(int i = 0; i < nodes.length; i++) {
                int edgesLength = nodes[i]->edges.length;
                for(int j = 0; j < edgesLength; j++) {
                    nodes[i]->edges.pop();
                }
            }
        }

        void printState() {
            for(int i = 0; i < nodes_length; i++) {
                Node* n = nodes[i];
                cout << "Id: " << n->id << endl;
                cout << "Edges length: " << n->edges.length << endl;
                for(int j = 0; j < n->edges.length; j++) {
                    printf(
                        "%d --%d-> %d | ",
                        n->edges[j].nodeIdU,
                        n->edges[j].weight,
                        n->edges[j].nodeIdV
                        );
                }
                cout << endl;
            }
        }
};

void insertEdges(Graph &G) {
    G.insertEdge(G.getNode(0), G.getNode(1), 10);
    G.insertEdge(G.getNode(0), G.getNode(2), 18);
    G.insertEdge(G.getNode(0), G.getNode(3), 12);

    G.insertEdge(G.getNode(1), G.getNode(0), 10);
    G.insertEdge(G.getNode(1), G.getNode(2), 19);
    G.insertEdge(G.getNode(1), G.getNode(4), 39);

    G.insertEdge(G.getNode(2), G.getNode(0), 18);
    G.insertEdge(G.getNode(2), G.getNode(1), 19);
    G.insertEdge(G.getNode(2), G.getNode(3), 20);
    G.insertEdge(G.getNode(2), G.getNode(5), 4);
    G.insertEdge(G.getNode(2), G.getNode(6), 1);
    G.insertEdge(G.getNode(2), G.getNode(7), 2);

    G.insertEdge(G.getNode(3), G.getNode(0), 12);
    G.insertEdge(G.getNode(3), G.getNode(2), 20);
    G.insertEdge(G.getNode(3), G.getNode(8), 8);

    G.insertEdge(G.getNode(4), G.getNode(1), 39);
    G.insertEdge(G.getNode(4), G.getNode(5), 10);
    G.insertEdge(G.getNode(4), G.getNode(9), 12);

    G.insertEdge(G.getNode(5), G.getNode(4), 10);
    G.insertEdge(G.getNode(5), G.getNode(2), 4);
    G.insertEdge(G.getNode(5), G.getNode(10), 3);
    G.insertEdge(G.getNode(5), G.getNode(6), 1);
    
    G.insertEdge(G.getNode(6), G.getNode(2), 1);
    G.insertEdge(G.getNode(6), G.getNode(5), 1);
    G.insertEdge(G.getNode(6), G.getNode(10), 1);
    G.insertEdge(G.getNode(6), G.getNode(7), 7);

    G.insertEdge(G.getNode(7), G.getNode(6), 7);
    G.insertEdge(G.getNode(7), G.getNode(2), 2);
    G.insertEdge(G.getNode(7), G.getNode(10), 2);
    G.insertEdge(G.getNode(7), G.getNode(8), 7);

    G.insertEdge(G.getNode(8), G.getNode(3), 8);
    G.insertEdge(G.getNode(8), G.getNode(7), 7);
    G.insertEdge(G.getNode(8), G.getNode(11), 20);

    G.insertEdge(G.getNode(9), G.getNode(4), 12);
    G.insertEdge(G.getNode(9), G.getNode(12), 13);
    G.insertEdge(G.getNode(9), G.getNode(10), 9);

    G.insertEdge(G.getNode(10), G.getNode(6), 1);
    G.insertEdge(G.getNode(10), G.getNode(5), 3);
    G.insertEdge(G.getNode(10), G.getNode(9), 9);
    G.insertEdge(G.getNode(10), G.getNode(12), 15);
    G.insertEdge(G.getNode(10), G.getNode(11), 10);
    G.insertEdge(G.getNode(10), G.getNode(7), 2);

    G.insertEdge(G.getNode(11), G.getNode(8), 20);
    G.insertEdge(G.getNode(11), G.getNode(10), 10);
    G.insertEdge(G.getNode(11), G.getNode(12), 14);

    G.insertEdge(G.getNode(12), G.getNode(9), 13);
    G.insertEdge(G.getNode(12), G.getNode(10), 15);
    G.insertEdge(G.getNode(12), G.getNode(11), 14);
}

int main(int argc, char* argv[]) {
    int nodes_length = 13;

    Graph G(13);
    for(int i = 0; i < G.nodes_length; i++) {
        Node* n = new Node(i);
        G.insertNode(n);
    }

    insertEdges(G);

    // for debugging, print state
    // G.printState();

    ofstream MyFile("weightsMatrix.csv");

    DynamicArray<DynamicArray<int>> matrix = G.getWeightMatrix();
    cout << "Weights Matrix:" << endl;
    for(int i = 0; i < G.nodes.length; i++) {
        for(int j = 0; j < G.nodes.length; j++) {
            cout << matrix[i][j] << " ";
            if (j == G.nodes.length - 1) {
                MyFile << matrix[i][j] << "\n";
            } else {
                MyFile << matrix[i][j] << ",";
            }
        }
        cout << "\n";
    }
    MyFile.close();
    cout << "Weights Matrix generated" << endl;

    G.clearEdges();
    // G.printState();

    string m = "M";
    if(argc == 2) m = argv[1];

    DynamicArray<DynamicArray<bool>> N(nodes_length, DynamicArray<bool>(nodes_length, false));
    cout << "Starting algorithm..." << endl;
    while(!G.isConnected()) {
        Edge e;
        if(m.compare("M") == 0) e = G.getHeavierEdge(N, matrix); // pega maior peso não utilizado
        else if(m.compare("m") == 0) e = G.getLighterEdge(N, matrix); // pega menor peso não utilizado
        G.insertEdge(G.getNode(e.nodeIdU), G.getNode(e.nodeIdV), e);
        G.insertEdge(G.getNode(e.nodeIdV), G.getNode(e.nodeIdU), e);
        N[e.nodeIdU][e.nodeIdV] = true;
        N[e.nodeIdV][e.nodeIdU] = true;
        G.printConnected();
        // printa sem repetir por ser nao direcionado, ou seja:
        // se do node 0 eu vou pro 2, portanto do 2 para 0, mas apenas escreve 0-->2 ou 2-->0 (dependendo de onde começou)
    }
    return 0;
}