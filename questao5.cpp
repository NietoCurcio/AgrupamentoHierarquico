// QUESTAO 5 PROJETO FINAL
// GRUPO - Felipe Curcio, Rodrigo Parracho
#include<iostream>
#include<vector>
#include <fstream>

using namespace std;

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
        vector<Edge> edges;

        // Node() {}

        Node(int id) {
            this->id = id;
        }

        void connect(Node* node, int weight) {
            Edge e;
            e.setWeight(weight);
            e.setNodeIdU(this->id);
            e.setNodeIdV(node->id);
            this->edges.push_back(e);
        }

        bool isEdgeConnectedTo(int nodeIdV) {
            for(int i = 0; i < edges.size(); i++) {
                if(edges[i].nodeIdV == nodeIdV) return true;
            }
            return false;
        }

        Edge getEdgeConnectedTo(int nodeIdV) {
            Edge e;
            for(int i = 0; i < edges.size(); i++) {
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
        vector<Node*> nodes;

        Graph(int n_length) : nodes_length(n_length) {}

        Node* getNode(int id) {
            Node* node;
            for(int i = 0; i < nodes.size(); i++) {
                if(id == nodes[i]->id) {
                    node = nodes[i];
                    break;
                }
            }
            return node;
        }

        void insertNode(Node* n) {
            nodes.push_back(n);
        }

        void insertEdge(Node* a, Node* b, int weight) {
            a->connect(b, weight);
        }

        bool isConnected() {
            vector<bool> explored(nodes_length, false);
            Node* first;

            // start with a node that has at least one edge
            for(int i = 0; i < nodes.size(); i++) {
                 if (nodes[i]->edges.size()) {
                     first = nodes[i];
                     break;
                 }
            }

            // dfs
            vector<Node*> nodesToExplore = {first};
            while(!nodesToExplore.empty()) {
                Node* n = nodesToExplore.back();
                nodesToExplore.pop_back();

                if (explored[n->id]) continue;

                explored[n->id] = true;

                vector<Edge> edges = n->edges;
                for(int i = 0; i < edges.size(); i++) {
                    Node* nodeEdge = this->getNode(edges[i].nodeIdV);
                    nodesToExplore.push_back(nodeEdge);
                }
            }

            for(int i = 0; i < explored.size(); i++) {
                if(!explored[i]) return false;
                // for test only, commented
                // if(explored[i]) printf("true\n");
                // else printf("false\n");
            }
            return true;
        }

        Edge getHeavierEdge(vector<vector<bool>> &N, vector<vector<int>> &matrix) {
            Edge e;
            int greater = -1;
            int uId = -1;
            int vId = -1;
            for(int i = 0; i < matrix.size(); i++) {
                for(int j = 0; j < matrix.size(); j++) {
                    if (matrix[i][j] > greater) {
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

        void printConnected() {

        }

        vector<vector<int>> getWeightMatrix() {
            vector<vector<int>> n(nodes_length, vector<int>(nodes_length, 0));
            for(int i = 0; i < 13; i++) {
                Node* node = this->getNode(i);
                for(int j = 0; j < 13; j++) {
                    if(node->isEdgeConnectedTo(j)) {
                        Edge e = node->getEdgeConnectedTo(j);
                        int w = e.weight;
                        n[i][j] = w;
                    }
                }
            }
            return n;
        }

        void clearEdges() {
        // to do
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

    ofstream MyFile("filename.csv");

    cout << "matrix\n";
    vector<vector<int>> matrix = G.getWeightMatrix();
    for(int i = 0; i < G.nodes.size(); i++) {
        for(int j = 0; j < G.nodes.size(); j++) {
            cout << matrix[i][j] << " ";
            if (j == G.nodes.size() - 1) {
                MyFile << matrix[i][j] << "\n";
            } else {
                MyFile << matrix[i][j] << ",";
            }
        }
        cout << "\n";
    }
    MyFile.close();

    G.clearEdges();
    vector<vector<bool>> N(nodes_length, vector<bool>(nodes_length, false));
    while(!G.isConnected()) {
        Edge e = G.getHeavierEdge(N, matrix);
        Node* u = G.getNode(e.nodeIdU);
        Node* v = G.getNode(e.nodeIdV);
        G.insertEdge(u, v, e.weight);
        N[e.nodeIdU][e.nodeIdV] = true;
        G.printConnected();
    }
    return 0;
}