#include "stdafx.h"
#include <cmath>
#include <cstdio>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
using namespace std;

struct vertex {
	int key;
	vector<int> adj;
	vertex(int k):key(k) {}

};

struct graph {
	int cnt;
	vector<vertex*> vertices;

	graph(int n) {
		cnt = n;
		for (int i = 0; i < n; i++) {
			vertices.push_back(new vertex(i));
		}
	}

	void addEdge(int v, int u) {
		vertices[v]->adj.push_back(u);
		vertices[u]->adj.push_back(v);
	}

	void dfsAux(int v, vector<bool>& visited) {
		visited[v] = true;
		cout << "Vertex " << vertices[v]->key <<" ";
		int sz = vertices[v]->adj.size();
		for (int i = 0; i < sz; i++) {
			int nextV = vertices[v]->adj[i];
			if (!visited[nextV])
				dfsAux(nextV, visited);
		}
	}

	void dfs(int v) {
		cout << "DFS: ";
		vector<bool> visited(vertices.size(), false);
		dfsAux(v, visited);
		cout << endl;
	}

	void bfs(int s) {
		cout << "BFS: ";
		vector<bool> visited(cnt, false);
		vector<int> dist(cnt, -1);
		list<vertex*> queue;

		visited[s] = true;
		dist[s] = 0;
		queue.push_back(vertices[s]);
		
		while (!queue.empty()) {
			// Dequeue a vertex from queue and print it
			vertex* v = queue.front();
			queue.pop_front();
			cout << "Vertex " << v->key << " ";

			// If an adjacent has not been visited, then mark it visited
			// and enqueue it
			int size = v->adj.size();
		
			for (int i = 0; i < size; i++) {
				int curr = v->adj[i];
				if (!visited[curr]) {
					visited[curr] = true;
					dist[curr] = dist[v->key] + 6;
					queue.push_back(vertices[curr]);
				}
			}
		}
		/*for (int i = 0; i < cnt; i++) {
			if (i != s - 1) {
				cout << dist[i] << " ";
			}
		}*/
		cout << endl;
	}
};

int main() {
	int gn;
	cin >> gn;
    vector<graph> graphs;
	vector<int> starts;
	for (int i = 0; i<gn; i++) {
		int n, m;
		cin >> n >> m;
		graph g(n);

		for (int j = 0; j < m; j++) {
			int v, u;
			cin >> v >> u;
			g.addEdge(v, u);
		}
		graphs.push_back(g);
		int s;
		cin >> s;
		starts.push_back(s);
		
	}
	for (int i = 0; i < gn; i++) {
		graphs[i].bfs(starts[i]);
		graphs[i].dfs(starts[i]);
	}
	return 0;
}

