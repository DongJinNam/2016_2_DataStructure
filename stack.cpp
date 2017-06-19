#include <iostream>
#include <string>

using namespace std;

// array 기반으로 구성한 stack.
template <typename T>
class ArrayStack {
private:
	T *arr; // stack이 담고 있는 array
	int t; // stack 최상위 원소 인덱스
	int capacity; // stack이 담을 수 있는 최대 사이즈

public:
	// max : stack의 최대용량
	// 생성자에서 memory를 동적으로 할당하도록 한다.
	ArrayStack(int max) : arr(new T[max]), t(-1), capacity(max) {}
	~ArrayStack() {
		// stack이 담고 있는 할당했던 memory를 다시 해제해야 한다.
		if(arr) delete[] arr;
	}

	// stack이 꽉 차 있는 경우에 예외처리를 하도록 한다.
	// 배열 top index에 데이터를 넣고 top index를 1 증가한다.
	void push(const T& e) throw(std::string) {
		if (size() == capacity) throw std::string("Stack is Full.");
		arr[++t] = e;
	}

	// stack이 비어있는 경우에 예외처리를 하도록 한다.
	// top index 에서 1을 뺀다.
	void pop() throw(std::string) {
		if (isEmpty()) throw std::string("Pop from empty stack");
		--t;
	}

	// stack이 비어있는 경우에 예외처리를 하도록 한다.
	// top index에 있는 배열 원소 값을 return 한다.
	T& top() const throw(std::string){ // pop
		if (isEmpty()) throw std::string("Top of empty stack");
		return arr[t];
	}

	// stack이 비어있는지 아닌지 check 한다.
	bool isEmpty() const {
		return t < 0; // t = -1 : empty stack, t >= 0 : not empty stack
	}

	// 현재 stack에 있는 데이터 개수를 출력한다.
	int size() const {
		return t + 1;
	}
	
};

// arr 문자열에 대한 괄호 구조 판별 Algorithm.
// 결과 경우의 수가 3가지가 존재하기 때문에 int return 함수로 선언
int parenMatch(const char *arr, int size); // arr : 입력받은 문자열, size : 문자열의 길이
 
int main() {
	int cnt; // 입력 받을 count [몇개의 연산을 수행할 것인가]
	cin >> cnt;
	for (int i = 0; i < cnt; i++) {
		string input; // 입력받을 string object
		int result; // parentMatch method의 결과값.
		cin >> input;

		//input.c_str() : 입력받은 문자열을 char * 로 type casting, input.length() : 입력받은 문자열의 길이
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

	ArrayStack<char> stack(300); // 최대 300개까지 담을 수 있는 char type array 기반 open symbol stack

	// stack 관련 예외처리를 한다.
	try {
		for (int i = 0; i < size; i++) { // size : arr 배열 길이, arr : 입력받은 string을 const char * 배열로 type casting			
			// ascii code에 있는 괄호 문자들에 대한 value 값과 비교한다.
			if (arr[i] == 0x5B || arr[i] == 0x7B || arr[i] == 0x28) {
				// 0x5B : [, ox7B : {, 0x28 : (
				stack.push(arr[i]); // opening grouping symbol 인 경우에 stack에 push 한다.
			}
			else if (arr[i] == 0x5D || arr[i] == 0x7D || arr[i] == 0x29) { // closing grouping symbol 인 경우 처리방식.
				// 0x5D : ], 0x7D : }, 0x29 : )
				if (stack.isEmpty()) return 0; // stack이 비어있는 상태인데, closing symbol 이 들어간 경우 incorrect이기 때문에 0을 리턴한다.
				if (arr[i] != 0x29) {
					// ], } 일 시에는 [, { 와 ascii code 에 의한 value 값 차이가 2이기 때문에 이와같이 처리하였다.
					if (stack.top() != arr[i] - 2) return 0;
				}
				else {
					// ) 일 시에는 ( 와 ascii code 에 의한 value 값 차이가 1이기 때문에 이와같이 처리하였다.
					if (stack.top() != arr[i] - 1) return 0;
				}
				// 별 문제가 없을 시에는 open symbol stack에 있는 top 원소를 pop 한다.
				stack.pop();
			}
			else return -1; // Open Symbol, Close Symbol 외의 문자가 들어오게 될 시에는 Wrong Input을 출력하기 위해서 -1을 리턴한다.
		}
	}
	catch (std::string &output) {
		// stack 연산에서 문제가 생길 시에, 문자열을 throw하고 catch 문에서 출력하도록 한다.
		cout << output << endl;
		return 0;
	}

	if (stack.isEmpty()) return 1; // stack 이 비어있으면, Correct
	else return 0; // stack이 비어있지 않으면, InCorrect
}