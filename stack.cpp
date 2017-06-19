#include <iostream>
#include <string>

using namespace std;

// array ������� ������ stack.
template <typename T>
class ArrayStack {
private:
	T *arr; // stack�� ��� �ִ� array
	int t; // stack �ֻ��� ���� �ε���
	int capacity; // stack�� ���� �� �ִ� �ִ� ������

public:
	// max : stack�� �ִ�뷮
	// �����ڿ��� memory�� �������� �Ҵ��ϵ��� �Ѵ�.
	ArrayStack(int max) : arr(new T[max]), t(-1), capacity(max) {}
	~ArrayStack() {
		// stack�� ��� �ִ� �Ҵ��ߴ� memory�� �ٽ� �����ؾ� �Ѵ�.
		if(arr) delete[] arr;
	}

	// stack�� �� �� �ִ� ��쿡 ����ó���� �ϵ��� �Ѵ�.
	// �迭 top index�� �����͸� �ְ� top index�� 1 �����Ѵ�.
	void push(const T& e) throw(std::string) {
		if (size() == capacity) throw std::string("Stack is Full.");
		arr[++t] = e;
	}

	// stack�� ����ִ� ��쿡 ����ó���� �ϵ��� �Ѵ�.
	// top index ���� 1�� ����.
	void pop() throw(std::string) {
		if (isEmpty()) throw std::string("Pop from empty stack");
		--t;
	}

	// stack�� ����ִ� ��쿡 ����ó���� �ϵ��� �Ѵ�.
	// top index�� �ִ� �迭 ���� ���� return �Ѵ�.
	T& top() const throw(std::string){ // pop
		if (isEmpty()) throw std::string("Top of empty stack");
		return arr[t];
	}

	// stack�� ����ִ��� �ƴ��� check �Ѵ�.
	bool isEmpty() const {
		return t < 0; // t = -1 : empty stack, t >= 0 : not empty stack
	}

	// ���� stack�� �ִ� ������ ������ ����Ѵ�.
	int size() const {
		return t + 1;
	}
	
};

// arr ���ڿ��� ���� ��ȣ ���� �Ǻ� Algorithm.
// ��� ����� ���� 3������ �����ϱ� ������ int return �Լ��� ����
int parenMatch(const char *arr, int size); // arr : �Է¹��� ���ڿ�, size : ���ڿ��� ����
 
int main() {
	int cnt; // �Է� ���� count [��� ������ ������ ���ΰ�]
	cin >> cnt;
	for (int i = 0; i < cnt; i++) {
		string input; // �Է¹��� string object
		int result; // parentMatch method�� �����.
		cin >> input;

		//input.c_str() : �Է¹��� ���ڿ��� char * �� type casting, input.length() : �Է¹��� ���ڿ��� ����
		result = parenMatch(input.c_str(), input.length());

		if (result > 0) // Correct
			cout << "Correct" << endl;
		else if (result == 0) // InCorrect
			cout << "Incorrect" << endl;
		else // Wrong input
			cout << "Wrong input" << endl;
	}
	return 0;
}

// 1 : corrent, 0 : incorrect, -1 : wrong input
int parenMatch(const char *arr, int size) {

	ArrayStack<char> stack(300); // �ִ� 300������ ���� �� �ִ� char type array ��� open symbol stack

	// stack ���� ����ó���� �Ѵ�.
	try {
		for (int i = 0; i < size; i++) { // size : arr �迭 ����, arr : �Է¹��� string�� const char * �迭�� type casting			
			// ascii code�� �ִ� ��ȣ ���ڵ鿡 ���� value ���� ���Ѵ�.
			if (arr[i] == 0x5B || arr[i] == 0x7B || arr[i] == 0x28) {
				// 0x5B : [, ox7B : {, 0x28 : (
				stack.push(arr[i]); // opening grouping symbol �� ��쿡 stack�� push �Ѵ�.
			}
			else if (arr[i] == 0x5D || arr[i] == 0x7D || arr[i] == 0x29) { // closing grouping symbol �� ��� ó�����.
				// 0x5D : ], 0x7D : }, 0x29 : )
				if (stack.isEmpty()) return 0; // stack�� ����ִ� �����ε�, closing symbol �� �� ��� incorrect�̱� ������ 0�� �����Ѵ�.
				if (arr[i] != 0x29) {
					// ], } �� �ÿ��� [, { �� ascii code �� ���� value �� ���̰� 2�̱� ������ �̿Ͱ��� ó���Ͽ���.
					if (stack.top() != arr[i] - 2) return 0;
				}
				else {
					// ) �� �ÿ��� ( �� ascii code �� ���� value �� ���̰� 1�̱� ������ �̿Ͱ��� ó���Ͽ���.
					if (stack.top() != arr[i] - 1) return 0;
				}
				// �� ������ ���� �ÿ��� open symbol stack�� �ִ� top ���Ҹ� pop �Ѵ�.
				stack.pop();
			}
			else return -1; // Open Symbol, Close Symbol ���� ���ڰ� ������ �� �ÿ��� Wrong Input�� ����ϱ� ���ؼ� -1�� �����Ѵ�.
		}
	}
	catch (std::string &output) {
		// stack ���꿡�� ������ ���� �ÿ�, ���ڿ��� throw�ϰ� catch ������ ����ϵ��� �Ѵ�.
		cout << output << endl;
		return 0;
	}

	if (stack.isEmpty()) return 1; // stack �� ���������, Correct
	else return 0; // stack�� ������� ������, InCorrect
}