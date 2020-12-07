// Nombre: Guillermo Salvador Calderon Lopez
// Matricula: A00827549

#ifndef Graph_h
#define Graph_h

template<class T>
struct Edge {
	T target;
	int weight;
};

template<class T>
class Graph {
	std::vector< std::vector< Edge<T> > > adj;
	HashT vertices;
	int size;

	// O(n)
	int findVertex(const T &vertex) {
		int it = vertices.find(vertex);
		return it;
	}

public:
	// O(n^2)
	Graph(std::vector< std::vector<T> > list) {
		int source = 0, target = 1;
		vertices = HashT((int) list.size());

		for (auto edge : list) {
			T aux = edge[source];
			int pos = findVertex(aux);
			if (pos<0) {
				vertices.insert(aux);
			}
			aux = edge[target];
			pos = findVertex(aux);
			if (pos<0) {
				vertices.insert(aux);
			}
		}
		size = list.size();
		adj = std::vector< std::vector< Edge<T> > >(size);
		for (auto path : list) {
			int pos = findVertex(path[source]);
			Edge<T> edge;
			edge.target = path[target];
			edge.weight = 1;
			adj[pos].push_back(edge);
		}
	}

	// O(n)
	void print(const T &value) {
		int it = vertices.find(value);
		if (it == -1) {
			std::cout << "IP no valido" << std::endl;
			return;
		}
		for (int i = 0; i < (int) adj[it].size(); ++i) {
			std::cout << adj[it][i].target << std::endl;
		}
	}
};

#endif /* Graph_h */