#include <iostream>
#include <stack>
#include <queue>
#include <map>

#define MAX 100 // MAX size

using namespace std;

// Graph Class
class Graph {
private:
	int n; // vertex count
	int A[MAX][MAX]; // Adjacency Matrix
	bool visited[MAX]; // DFS or BFS ���� �κп��� vertex�� �湮�ߴ��� �����ϴ� array
	std::map<int,int> vertexMap; // vertex ������ name value�� key value�� �����ϴ� map
public:
	Graph(); // graph ������
	~Graph(); // graph �Ҹ���
	bool isConnected(int, int); // vertex name x�� vertex name y ���̿� ����� edge�� ������ true, ������ false�� return
	void addEdge(int, int); // vertex name x�� vertex name y ���̿� edge�� �߰��ϴ� method
	void DFS(int); // Depth First Search
	void BFS(int); // Breathe First Search
	void push(int, int); // vertex ����(name,key)�� vertexMap�� �ִ� method
};

Graph::Graph() {
	int i,j;
	n = MAX; 
	for (i = 0; i < n; ++i) {
		visited[i] = false;
	}
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			A[i][j] = 0;
}

Graph::~Graph() {
}

bool Graph::isConnected(int x, int y) {
	return (A[x - 1][y - 1] == 1);
}

void Graph::addEdge(int x, int y) {
	A[x - 1][y - 1] = A[y - 1][x - 1] = 1;
}

void Graph::DFS(int x) {
	std::stack<int> s;
	int i;	

	for (i = 0; i < n; i++)
		visited[i] = false;

	s.push(x);
	visited[x-1] = true;

	while (!s.empty()) {
		int k = s.top();
		s.pop();

		/** display the explored vertices */
		cout << vertexMap.find(k)->second << " ";

		for (i = n; i > 0; --i) {
			if (isConnected(k, i) && !visited[i-1]) {
				s.push(i);
				visited[i-1] = true;
			}
		}
	}
	cout << endl;
}

void Graph::BFS(int x) {
	std::queue<int> q;
	int i;

	/** Initailized all vertices as unexplored */
	for (i = 0; i < n; i++)
		visited[i] = false;

	/** Push initial vertex to the queue */
	q.push(x);
	visited[x-1] = true; /** mark it as explored */

	while (!q.empty()) {
		int v = q.front();
		q.pop();

		/** display the explored vertices */
		cout << vertexMap.find(v)->second << " ";

		for (i = 1; i <= n; i++) {
			if (isConnected(v, i) && !visited[i - 1]) {
				q.push(i);
				visited[i - 1] = true;
			}
		}
	}
	cout << endl;
}

void Graph::push(int name, int key) {
	vertexMap.insert(std::pair<int, int>(name, key));
}

int main() {
	Graph graph;
	int vertexCount = 0, edgeCount = 0;
	int minName = 0, minKey = 10000;
	int i, name, key, a, b;
	char c;

	cin >> vertexCount;
	for (i = 0; i < vertexCount; i++) {
		cin >> name >> key;
		graph.push(name, key);
		if (key <= minKey) {
			minKey = key; // �ּ� Ű ���� ������ vertex ������ main �Լ� �󿡼� ������ ���ؼ� �̷��� �Ͽ���.
			minName = name;
		}
	}
	cin >> edgeCount;
	for (i = 0; i < edgeCount; i++) {
		cin >> a >> b;
		if (a != b) graph.addEdge(a, b);
		else {
			i--;
			continue;
		}
	}

	while (1) {
		cin >> c;
		if (c == 'X' || c == 'x') break;
		switch (c) {
		case 'D':
		case 'd':
			graph.DFS(minName);
			break;
		case 'F':
		case 'f':
			graph.BFS(minName);
			break;
		}
	}	
	return 0;
}