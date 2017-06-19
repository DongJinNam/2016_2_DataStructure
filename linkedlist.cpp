#include <iostream>

using namespace std;

//template을 적용한 singly node
template <typename T>
class SNode {
private:
	T elem; // node의 element
	SNode<T> *next; // next node pointer
public:
	SNode<T>() : next(NULL) {}
	SNode<T>(const T& e) : elem(e), next(NULL) {}
	const T& getElem() const { return elem; } // elem이 private으로 선언되어 있기 때문에 get 함수를 활용한다.
	SNode<T> *getNext() const { return next; } // next가 private으로 선언되어 있기 때문에 get 함수를 활용한다.
	void setElem(const T& e) { elem = e; } // 마찬가지로 set 함수를 활용해 데이터를 설정할 수 있다.
	void setNext(SNode<T> *node) { next = node; } // 마찬가지로 set 함수를 활용해 데이터를 설정할 수 있다.
};

//template을 적용한 singly linked list
template <typename T>
class SLinkedList {
private:
	SNode<T> *head; // linkedlist의 head node pointer
public:
	SLinkedList<T>() : head(NULL) {}
	~SLinkedList<T>() { while (!empty()) { removeFront(); } }
	bool empty() const { return head == NULL; }
	const T& front() const { return head->getElem(); }
	// Linked List 앞에 Node를 추가하는 메소드
	void addFront(const T& e) {
		SNode<T> *node = new SNode<T>(e);
		// Empty list에 Node를 추가하는 경우에는 Next pointer를 Null로 한다.
		if (head == NULL) node->setNext(NULL);
		else node->setNext(head);
		head = node;
	}
	// Head Node를 삭제하는 메소드
	void removeFront() {
		// head가 null인 경우, 데이터를 제거할 수 없기 때문에 예외처리를 해준다.
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
	// Traverse Linked List 메소드
	void traverse() {
		SNode<T> *node = head;
		// head가 null인 경우는 list가 비어있기 때문에 Empty List로 출력한다.
		if (node == NULL) cout << "Empty List" << endl;
		else {
			// 임시 node가 null이 아닐 때까지 element 를 계속 출력한다.
			while (node != NULL) {
				cout << node->getElem() << " ";
				node = node->getNext();
			}
			cout << endl;
		}
	}
};

int main() {	
	//int 형 Linked List를 동적으로 구성한다.
	SLinkedList<int> *list1 = new SLinkedList<int>;
	unsigned char input; // 입력될 input character값
	int num = 0; // node insert할 때 들어가게 되는 정수값
	while (1) {
		cin >> input;
		// X가 입력되었다면 프로그램을 종료하도록 한다.
		if (input == 'X') break;
		switch (input) {
		case 'I': 
			cin >> num;
			list1->addFront(num); // Front에 elem이 num인 node를 추가한다.
			break;
		case 'R':
			list1->removeFront(); // Front Node를 제거한다.
			break;
		case 'E':
			// 리스트가 비어있다면 "T", 비어있지 않다면 "F" 로 출력한다.
			if (list1->empty()) std::cout << "T" << endl;
			else std::cout << "F" << endl;
			break;
		case 'H':
			// 리스트가 비어있는지 체크하고, 비어있으면 Empty List를 출력함으로써 예외처리를 한다.
			if (list1->empty()) std::cout << "Empty List" << endl;
			else std::cout << list1->front() << endl;
			break;
		case 'T':
			// Linked List를 순회하면서 Element를 하나씩 끝까지 출력한다.
			list1->traverse();
			break;
		default:
			std::cout << "Wrong Input" << endl;
			break;
		}
	}
	//동적으로 구성된 linked list를 메모리에서 제거한다.
	if (list1) delete list1;
	return 0;
}