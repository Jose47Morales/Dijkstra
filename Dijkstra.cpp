#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

// Estructura para representar una arista
struct Edge {
    int destination;
    int weight;
};

// Estructura para representar el grafo
class Graph {
public:
    int V; // Número de vértices
    vector<vector<Edge>> adjList; // Lista de adyacencia

    Graph(int V) {
        this->V = V;
        adjList.resize(V);
    }

    void addEdge(int u, int v, int w) {
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w}); // Si el grafo es no dirigido
    }
    
    void mostrarGrafo(){
    	for(int i = 0; i < V; i++){
    		cout<<"Nodo "<<i<<" -> ";
    		for(auto& edge : adjList[i]){
    			cout<<"("<<edge.destination<<", "<<edge.weight<<") ";	
			}
			cout<<endl;
		}
	}
};

// Función de Dijkstra
void dijkstra(Graph& graph, int source) {
    vector<int> dist(graph.V, INT_MAX); // Inicializar distancias a infinito
    vector<int> parent(graph.V, -1);    // Inicializar padres a NULL (-1)
    dist[source] = 0;

    // Cola de prioridad para seleccionar el nodo con la distancia mínima
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // Recorrer los nodos adyacentes de u
        for (auto& edge : graph.adjList[u]) {
            int v = edge.destination;
            int weight = edge.weight;

            // Relajación (relaxation)
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    // Imprimir las distancias mínimas y los padres
    for (int i = 0; i < graph.V; ++i) {
        cout << "Distancia del nodo " << source << " al nodo " << i << " es: " << dist[i] << "\n";
        if (parent[i] != -1)
            cout << "Padre de " << i << " es: " << parent[i] << "\n";
        else
            cout << i << " es el nodo fuente\n";
    }
}

int main() {
    int V = 5; // Número de vértices
    Graph graph(V);

    // Agregar las aristas del grafo
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 4, 3);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 4, 4);
    graph.addEdge(2, 3, 9);
    graph.addEdge(3, 2, 7);
    graph.addEdge(4, 1, 1);
    graph.addEdge(4, 2, 8);
    graph.addEdge(4, 3, 2);

    int source = 0; // Nodo fuente
    dijkstra(graph, source);
    
    //Mostramos el grafo
    cout<<"\n=== GRAFO ===\n";
	graph.mostrarGrafo();
    return 0;
}
