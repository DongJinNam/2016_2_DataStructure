#include <iostream>

using namespace std;

// �Է��� ����� ������ �ִ� 100000�̱� ������, BTree�� ������ �ִ� �迭 ������� 100001�� �����Ѵ�.
int arrOfBTree[100001] = { 0 };

// Binary Tree class -> BTree
class BTree {
public:
	// parameter�� ���� �����ڴ� ��ȿ���� �ʴٰ� �����Ѵ�.
	BTree() : arr(NULL) {}
	// array pointer�� Ȱ���ؼ� Binary Tree�� �迭�� ����Ѵ�.
	// BTree class ���� ���� �迭�� �����ؼ� Ȱ���Ϸ� ������, 
	// �޸� ������ ������ ���ܼ� ���� array�� �����ϴ� ������� �߽��ϴ�.
	BTree(int *ptArr) : arr(ptArr) {}
	// DeConstructor of BTree
	~BTree() {}
	//arr �迭 �ش� index�� data ���� �ִ´�.
	void setValue(int index, int data) {
		arr[index] = data;
	}
	//preOrder Traversal(���� ��ȸ : �ڱ� �ڽ� - ���� �ڽ� - ������ �ڽ�)
	//����Լ��� �����Ѵ�.
	void preOrder(int index) {
		//���� 0�̸� Ʈ���� ���ٰ� �����ϱ� ������ return �ϵ��� �Ѵ�.
		if (arr[index] == 0) return;
		cout << arr[index] << " ";
		preOrder(index*2);
		preOrder(index*2+1);
	}
	//inOrder Traversal(���� ��ȸ : ���� �ڽ� - �ڱ� �ڽ� - ������ �ڽ�)
	//����Լ��� �����Ѵ�.
	void inOrder(int index) {
		//���� 0�̸� Ʈ���� ���ٰ� �����ϱ� ������ return �ϵ��� �Ѵ�.
		if (arr[index] == 0) return;
		inOrder(index * 2);
		cout << arr[index] << " ";
		inOrder(index * 2 + 1);
	}
	//postOrder Traversal(���� ��ȸ : ���� �ڽ� - ������ �ڽ� - �ڱ� �ڽ�)
	//����Լ��� �����Ѵ�.
	void postOrder(int index) {
		//���� 0�̸� Ʈ���� ���ٰ� �����ϱ� ������ return �ϵ��� �Ѵ�.
		if (arr[index] == 0) return;
		postOrder(index * 2);
		postOrder(index * 2 + 1);
		cout << arr[index] << " ";
	}
	// type -  1 : preOrder, 2 : inOrder, 3 : postOrder
	// type ������ �޾Ƽ� � traversal(��ȸ)�� �� ������ ���ϰ� ��ȸ�ϵ��� �Ѵ�.
	void traverse(int type) {
		// preOrder, inOrder, postOrder ��� root ������ Ž���� �ؾ� �Ǳ� ������
		// index = 1�� �ʱ� ���� �Ѵ�.
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
	//�Է����� ���� ��ġ�� ���� �̿��ؼ� Ʈ���� ����.
	void insert(int index, int data) {
		if (arr[index / 2] == 0) return; // �θ� ��尡 ���� ��ġ�� �����͸� �����Ϸ��� ��� �Է��� ���� �ʴ´�. (����ó��)
		
		//index ��ġ�� ��尡 �ִ� ��� �����.
		int emptyIndex = 0;

		// insert �ϴ� ��ġ�� ��尡 ���� ���,
		if (arr[index] == 0)
			arr[index] = data;
		else {
			// insert �ϴ� ��ġ�� ��尡 �ִ� ��� ����ִ� ��ġ�� ã�Ƽ� �ִ´�.
			emptyIndex = findEmpty(index);
			arr[emptyIndex] = data;			
		}	
		//if (arr[index / 2] == 0) return; // �θ� ��尡 ���� ��ġ�� �����͸� �����Ϸ��� ��� �Է��� ���� �ʴ´�. (����ó��)
		//arr[index] = data;
		cout << "inserted" << endl;
	}
	//�Է����� ���� ��ġ�� ��� ����
	void remove(int index) {
		// �迭 index�� �ش��ϴ� value ���� 0 ���� �ʱ�ȭ�Ѵ�.
		if (arr[index * 2] != 0 || arr[index * 2 + 1] != 0) return; // �ڽ��� �ִ� ��带 �����Ϸ��� ��� �Է��� ���� �ʴ´�. (����ó��)
		arr[index] = 0;
		cout << "deleted" << endl;
	}
	//�Է����� ���� ��ġ�� ���� �̿��ؼ� Ʈ�� �� ��� ���� �����Ѵ�.
	void replace(int index, int data) {
		if (arr[index] == 0) return; // ���� �������� �ʴ� ��忡 ���� ���� �������� �ʴ´�. (����ó��)
		arr[index] = data;
		cout << "replaced" << endl;
	}
	// index�� ���� �����ؼ� �ڽ� ����� ���� ���� �ε��� �ּҰ��� ���� ��ġ�� ã�´�.(����Լ��� ����)
	int findEmpty(int index) {
		int left, right;
		if (arr[index] == 0)
			return index;
		left = findEmpty(index * 2);
		right = findEmpty(index * 2 + 1);
		return left > right ? right : left;
	}
private:
	int *arr; // Binary Tree�� �����ϰ� �ִ� int �� array
};

int main(int argc, char *argv[])
{
	// data : �Է¹��� ������, index : �Է¹��� �ε���
	int count = 0, i = 0, data = 0, type = 0, index = 0;
	char ch;	
	BTree btree(arrOfBTree);

	// almost complete tree�� ������ �ϱ� ���� �Է��� ����� ������ �Է��Ѵ�.
	cin >> count;

	//������� Ʈ�� ���� ���� �����Ѵ�.
	for (i = 1; i <= count; i++) {
		cin >> data;
		btree.setValue(i, data); // arr[i] = data;
	}

	while (1) {
		cin >> ch;
		// 'x' or 'X' �� ���α׷� ���Ḧ �ǹ��ϹǷ� break �ϵ��� �Ѵ�.
		if (ch == 'x' || ch == 'X') break;
		switch (ch) {		 
		case 'i': // �Է����� ���� ��ġ�� ���� �̿��ؼ� Ʈ���� �����Ѵ�.
		case 'I':
			cin >> index >> data;
			btree.insert(index, data);
			break;
		case 'd': // �Է����� ���� ��ġ�� ��带 ����
		case 'D':
			cin >> index;
			btree.remove(index);
			break;
		case 'r': // �Է����� ���� ��ġ�� ���� �̿��ؼ� Ʈ�� �� ��� ���� �����Ѵ�.
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