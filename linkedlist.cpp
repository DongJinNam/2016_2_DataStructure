#include <iostream>

using namespace std;

//template�� ������ singly node
template <typename T>
class SNode {
private:
	T elem; // node�� element
	SNode<T> *next; // next node pointer
public:
	SNode<T>() : next(NULL) {}
	SNode<T>(const T& e) : elem(e), next(NULL) {}
	const T& getElem() const { return elem; } // elem�� private���� ����Ǿ� �ֱ� ������ get �Լ��� Ȱ���Ѵ�.
	SNode<T> *getNext() const { return next; } // next�� private���� ����Ǿ� �ֱ� ������ get �Լ��� Ȱ���Ѵ�.
	void setElem(const T& e) { elem = e; } // ���������� set �Լ��� Ȱ���� �����͸� ������ �� �ִ�.
	void setNext(SNode<T> *node) { next = node; } // ���������� set �Լ��� Ȱ���� �����͸� ������ �� �ִ�.
};

//template�� ������ singly linked list
template <typename T>
class SLinkedList {
private:
	SNode<T> *head; // linkedlist�� head node pointer
public:
	SLinkedList<T>() : head(NULL) {}
	~SLinkedList<T>() { while (!empty()) { removeFront(); } }
	bool empty() const { return head == NULL; }
	const T& front() const { return head->getElem(); }
	// Linked List �տ� Node�� �߰��ϴ� �޼ҵ�
	void addFront(const T& e) {
		SNode<T> *node = new SNode<T>(e);
		// Empty list�� Node�� �߰��ϴ� ��쿡�� Next pointer�� Null�� �Ѵ�.
		if (head == NULL) node->setNext(NULL);
		else node->setNext(head);
		head = node;
	}
	// Head Node�� �����ϴ� �޼ҵ�
	void removeFront() {
		// head�� null�� ���, �����͸� ������ �� ���� ������ ����ó���� ���ش�.
		if (head == NULL) cout << "Invalid Remove" << endl;
		else {
			SNode<T> *node = head->getNext();
			if (head) {
				delete head;
				if (node != NULL) head = node;
				else head = NULL;
			}
		}
	}
	// Traverse Linked List �޼ҵ�
	void traverse() {
		SNode<T> *node = head;
		// head�� null�� ���� list�� ����ֱ� ������ Empty List�� ����Ѵ�.
		if (node == NULL) cout << "Empty List" << endl;
		else {
			// �ӽ� node�� null�� �ƴ� ������ element �� ��� ����Ѵ�.
			while (node != NULL) {
				cout << node->getElem() << " ";
				node = node->getNext();
			}
			cout << endl;
		}
	}
};

int main() {	
	//int �� Linked List�� �������� �����Ѵ�.
	SLinkedList<int> *list1 = new SLinkedList<int>;
	unsigned char input; // �Էµ� input character��
	int num = 0; // node insert�� �� ���� �Ǵ� ������
	while (1) {
		cin >> input;
		// X�� �ԷµǾ��ٸ� ���α׷��� �����ϵ��� �Ѵ�.
		if (input == 'X') break;
		switch (input) {
		case 'I': 
			cin >> num;
			list1->addFront(num); // Front�� elem�� num�� node�� �߰��Ѵ�.
			break;
		case 'R':
			list1->removeFront(); // Front Node�� �����Ѵ�.
			break;
		case 'E':
			// ����Ʈ�� ����ִٸ� "T", ������� �ʴٸ� "F" �� ����Ѵ�.
			if (list1->empty()) std::cout << "T" << endl;
			else std::cout << "F" << endl;
			break;
		case 'H':
			// ����Ʈ�� ����ִ��� üũ�ϰ�, ��������� Empty List�� ��������ν� ����ó���� �Ѵ�.
			if (list1->empty()) std::cout << "Empty List" << endl;
			else std::cout << list1->front() << endl;
			break;
		case 'T':
			// Linked List�� ��ȸ�ϸ鼭 Element�� �ϳ��� ������ ����Ѵ�.
			list1->traverse();
			break;
		default:
			std::cout << "Wrong Input" << endl;
			break;
		}
	}
	//�������� ������ linked list�� �޸𸮿��� �����Ѵ�.
	if (list1) delete list1;
	return 0;
}