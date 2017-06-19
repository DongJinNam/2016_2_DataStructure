#include <iostream>

using namespace std;

// 입력할 노드의 개수가 최대 100000이기 때문에, BTree가 가지고 있는 배열 사이즈는 100001로 설정한다.
int arrOfBTree[100001] = { 0 };

// Binary Tree class -> BTree
class BTree {
public:
	// parameter가 없는 생성자는 유효하지 않다고 가정한다.
	BTree() : arr(NULL) {}
	// array pointer를 활용해서 Binary Tree의 배열로 사용한다.
	// BTree class 내에 동적 배열을 선언해서 활용하려 했으나, 
	// 메모리 관리에 문제가 생겨서 전역 array를 참조하는 방식으로 했습니다.
	BTree(int *ptArr) : arr(ptArr) {}
	// DeConstructor of BTree
	~BTree() {}
	//arr 배열 해당 index에 data 값을 넣는다.
	void setValue(int index, int data) {
		arr[index] = data;
	}
	//preOrder Traversal(전위 순회 : 자기 자신 - 왼쪽 자식 - 오른쪽 자식)
	//재귀함수로 구성한다.
	void preOrder(int index) {
		//값이 0이면 트리가 없다고 가정하기 때문에 return 하도록 한다.
		if (arr[index] == 0) return;
		cout << arr[index] << " ";
		preOrder(index*2);
		preOrder(index*2+1);
	}
	//inOrder Traversal(중위 순회 : 왼쪽 자식 - 자기 자신 - 오른쪽 자신)
	//재귀함수로 구성한다.
	void inOrder(int index) {
		//값이 0이면 트리가 없다고 가정하기 때문에 return 하도록 한다.
		if (arr[index] == 0) return;
		inOrder(index * 2);
		cout << arr[index] << " ";
		inOrder(index * 2 + 1);
	}
	//postOrder Traversal(후위 순회 : 왼쪽 자식 - 오른쪽 자식 - 자기 자신)
	//재귀함수로 구성한다.
	void postOrder(int index) {
		//값이 0이면 트리가 없다고 가정하기 때문에 return 하도록 한다.
		if (arr[index] == 0) return;
		postOrder(index * 2);
		postOrder(index * 2 + 1);
		cout << arr[index] << " ";
	}
	// type -  1 : preOrder, 2 : inOrder, 3 : postOrder
	// type 변수를 받아서 어떤 traversal(순회)를 할 것인지 정하고 순회하도록 한다.
	void traverse(int type) {
		// preOrder, inOrder, postOrder 모두 root 노드부터 탐색을 해야 되기 때문에
		// index = 1로 초기 설정 한다.
		switch (type) {
		case 1: // preOrder
			preOrder(1);
			break;
		case 2: // inOrder
			inOrder(1);
			break;
		case 3: // postOrder
			postOrder(1);
			break;
		}
		printf("\n");
	}
	//입력으로 받은 위치와 값을 이용해서 트리에 삽입.
	void insert(int index, int data) {
		if (arr[index / 2] == 0) return; // 부모 노드가 없는 위치에 데이터를 삽입하려는 경우 입력을 하지 않는다. (예외처리)
		
		//index 위치에 노드가 있는 경우 사용함.
		int emptyIndex = 0;

		// insert 하는 위치에 노드가 없는 경우,
		if (arr[index] == 0)
			arr[index] = data;
		else {
			// insert 하는 위치에 노드가 있는 경우 비어있는 위치를 찾아서 넣는다.
			emptyIndex = findEmpty(index);
			arr[emptyIndex] = data;			
		}	
		//if (arr[index / 2] == 0) return; // 부모 노드가 없는 위치에 데이터를 삽입하려는 경우 입력을 하지 않는다. (예외처리)
		//arr[index] = data;
		cout << "inserted" << endl;
	}
	//입력으로 받은 위치의 노드 삭제
	void remove(int index) {
		// 배열 index에 해당하는 value 값을 0 으로 초기화한다.
		if (arr[index * 2] != 0 || arr[index * 2 + 1] != 0) return; // 자식이 있는 노드를 삭제하려는 경우 입력을 하지 않는다. (예외처리)
		arr[index] = 0;
		cout << "deleted" << endl;
	}
	//입력으로 받은 위치와 값을 이용해서 트리 내 노드 값을 변경한다.
	void replace(int index, int data) {
		if (arr[index] == 0) return; // 값이 존재하지 않는 노드에 대해 값을 변경하지 않는다. (예외처리)
		arr[index] = data;
		cout << "replaced" << endl;
	}
	// index로 부터 시작해서 자식 노드들로 부터 빈노드 인덱스 최소값을 가진 위치를 찾는다.(재귀함수로 구성)
	int findEmpty(int index) {
		int left, right;
		if (arr[index] == 0)
			return index;
		left = findEmpty(index * 2);
		right = findEmpty(index * 2 + 1);
		return left > right ? right : left;
	}
private:
	int *arr; // Binary Tree가 참조하고 있는 int 형 array
};

int main(int argc, char *argv[])
{
	// data : 입력받을 데이터, index : 입력받을 인덱스
	int count = 0, i = 0, data = 0, type = 0, index = 0;
	char ch;	
	BTree btree(arrOfBTree);

	// almost complete tree의 연산을 하기 전에 입력할 노드의 개수를 입력한다.
	cin >> count;

	//순서대로 트리 원소 값을 설정한다.
	for (i = 1; i <= count; i++) {
		cin >> data;
		btree.setValue(i, data); // arr[i] = data;
	}

	while (1) {
		cin >> ch;
		// 'x' or 'X' 는 프로그램 종료를 의미하므로 break 하도록 한다.
		if (ch == 'x' || ch == 'X') break;
		switch (ch) {		 
		case 'i': // 입력으로 받은 위치와 값을 이용해서 트리에 삽입한다.
		case 'I':
			cin >> index >> data;
			btree.insert(index, data);
			break;
		case 'd': // 입력으로 받은 위치의 노드를 삭제
		case 'D':
			cin >> index;
			btree.remove(index);
			break;
		case 'r': // 입력으로 받은 위치와 값을 이용해서 트리 내 노드 값을 변경한다.
		case 'R':
			cin >> index >> data;
			btree.replace(index, data);
			break;
		case 't':
		case 'T':
			// type - 1 : preOrder, 2 : inOrder, 3 : postOrder
			cin >> type;
			btree.traverse(type);			
			break;
		default:
			break;
		}
	}
	return 0;
}