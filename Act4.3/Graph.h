// Nombre: Guillermo Salvador Calderon Lopez
// Matricula: A00827549

#ifndef Graph_h
#define Graph_h

#include <queue>
#include <stack>
#include "Heap.h"

template <class T>
struct Data {
    T target;
    int times;
};

template <class T>
class Graph {
    public:
        Graph(std::vector<std::string> list, std::vector<std::string> vertex);
        void print();
        void DFS(T vertex);
        void BFS(T vertex);
        void shortestPath(T vertex);
        void topologicalSort();
        bool bipartiteGraph();
        void addWeight(std::vector<T> num);
        void repMax();
    private:
        std::vector<std::vector<T>> adjList;
        std::vector<T> vertices;
        int findVertex(T vertex);
        void DFSR(T vertex, std::vector<bool> &status);
        int minWeight(std::vector<int> weight, std::vector<bool> status);
        void topS(int num, std::vector<bool> &visit, std::stack<T> &s);
};

template <class T>
Graph<T>::Graph(std::vector<std::string> list, std::vector<std::string> vertex) {
    vertices = list;
    sort(vertices.begin(),vertices.end());

    for(auto vertex: vertices) {
        std::vector<T> aux;
        aux.push_back(vertex);
        adjList.push_back(aux);
    }

    for(auto path: vertex) {
        int start;

        std::string aux, org, target;
        std::stringstream ss(path);

        for(int i=0; i<4; i++) {
            getline(ss,aux,' ');
        }
        org = aux.substr(0,aux.find(":"));
        getline(ss,aux,' ');
        target = aux.substr(0,aux.find(":"));

        int pos = findVertex(org);
        adjList[pos].push_back(target);
    }
}

template <class T>
int Graph<T>::findVertex(T vertex) {
    typename std::vector<T>::iterator it;
    it = find(vertices.begin(), vertices.end(), vertex);
    if(it != vertices.end()) {
        return it - vertices.begin();
    } else {
        return -1;
    }
}

template <class T>
void Graph<T>::print() {
    for(int i=0; i<vertices.size(); ++i) {
        std::cout << vertices[i] << "--> ";
        for(int j=1; j<adjList[i].size(); ++j) {
            std::cout << "[" << adjList[i][j] << "] ";
        }
        std::cout << std::endl;
    }
}

template <class T>
void Graph<T>::BFS(T vertex) {
    std::queue<int> q;
    std::vector<bool> status(vertices.size(),false);

    q.push(vertex);
    status[vertex] = true;

    while(!q.empty()) {
        status = q.front();
        for(int adj=0; adj<adjList[vertex].size(); ++adj) {
            int posAdj = findVertex(adjList[vertex][adj].vertex);
            if(!status[posAdj]) {
                q.push(posAdj);
                status[posAdj] = true;
            }
        }
        std::cout << vertices[vertex] << " ";
        q.pop();
    }
    std::cout << std::endl;
}

template <class T>
void Graph<T>::DFS(T vertex) {
    std::vector<bool> status(vertices.size(), false);
    DFSR(vertices[vertex], status);
    std::cout << std::endl;
}

template <class T>
void Graph<T>::DFSR(T vertex, std::vector<bool> &status) {
    int pos = findVertex(vertex);
    if(!status[pos]) {
        std::cout << vertex << " ";
        status[pos] = true;
        for(auto adj : adjList[pos]) {
            int posAdj = findVertex(adj.vertex);
            if(!status[posAdj]) {
                DFSR(adj.vertex, status);
            }
        }
    }
}

template <class T>
void Graph<T>::topologicalSort() {
    std::stack<T> s;
    std::vector<bool> visit(vertices.size(),false);

    for(int i=0; i<vertices.size(); ++i) {
        if(visit[i] == false) {
            topS(i,visit,s);
            s.push(adjList[i][0].vertex);
        }
    }

    while(!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
}

template <class T>
void Graph<T>::topS(int num, std::vector<bool> &visit, std::stack<T> &s) {
    visit[num] = true;
    for(auto i: adjList[num]) {
        int pos = findVertex(i.vertex);
        if(!visit[pos]) {
            topS(pos,visit,s);
            s.push(i.vertex);
        }
    }
}

template <class T>
int Graph<T>::minWeight(std::vector<int> weight, std::vector<bool> status) {
    int minWeight = INT_MAX;
    int minVertex = -1;
    for(int i=0; i<vertices.size(); ++i) {
        if(!status[i]) {
            if(minWeight > weight[i]) {
                minWeight = weight[i];
                minVertex = i;
            }
        }
    }
    return minVertex;
}

template <class T>
void Graph<T>::shortestPath(T target) {
    int pos = findVertex(target);
    if(pos >= 0) {
        std::vector<bool> status(vertices.size(),false);
        std::vector<int> weight(vertices.size(),INT_MAX);
        std::vector<int> path(vertices.size(),-1);
        weight[pos] = 0;
        int next = pos;
        while(next >= 0) {
            status[next] = true;
            for(int j=0; j<adjList[next].size(); ++j) {
                int posAdj = findVertex(adjList[next][j].vertex);
                if(!status[posAdj]) {
                    if(weight[posAdj] > weight[next] + adjList[next][j].weight) {
                        weight[posAdj] = weight[next] + adjList[next][j].weight;
                        path[posAdj] = next;
                    } 
                }
            }
            next = minWeight(weight,status);
        }
        for(int k=0; k<vertices.size(); ++k) {
            std::stack<int> sp;
            sp.push(k);
            int p = path[k];
            while(p >= 0) {
                sp.push(p);
                p = path[p];
            }
            while(!sp.empty()) {
                std::cout << sp.top() << " ";
                sp.pop();
            }
            std::cout <<  "\tweight: " << weight[k] << std::endl;
        }
    }
}

template <class T>
bool Graph<T>::bipartiteGraph() {
    std::vector<int> status(vertices.size(),-1);
    std::queue<int> q;
    
    int pos = 0;
    status[pos] = 1;
    q.push(pos);

    while(!q.empty()) {
        int u = q.front();
        q.pop();

        if(adjList[u][u].vertex == 1) {
            return false;
        }
        for(int v=1; v<adjList[u].size(); ++v){
            if(status[adjList[u][v].vertex] == -1) {
                status[adjList[u][v].vertex] = 1-status[u];
                q.push(adjList[u][v].vertex);
            }
            else if(status[adjList[u][v].vertex] == status[u]) {
                return false;
            }
        }
    }
    return true;
}

template <class T>
void Graph<T>::repMax() {
    int time;
    Data<std::string> aux;
    std::vector<Data<std::string>> auxList;
    std::vector<Data<std::string>> answer;

    for(int i=0; i<vertices.size(); ++i) {
        time = adjList[i].size();
        aux.times = time;
        aux.target = vertices[i];
        auxList.push_back(aux);
    }

    Heap<Data<std::string>> heap(auxList);
    answer = heap.sort();
    std::cout << answer[1].target << std::endl << std::endl;
    std::cout << "Numero de adyacencias" << std::endl << adjList[findVertex(answer[1].target)].size()-1 << std::endl;
}

#endif