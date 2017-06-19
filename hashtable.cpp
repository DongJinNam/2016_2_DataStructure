#include <iostream>
#define CAPACITY 257 // HashMap이 담고 있는 key, value 각각의 배열 사이즈

using namespace std;

//Linear Probing 방식 Hash Table Class
class HashMap {
public:
	// HashMap의 생성자
	HashMap() {
		// key Array, value Array 초기화
		for (int i = 0; i < CAPACITY; i++) {
			key[i] = -1; // key array의 모든 원소를 -1로 초기화
			value[i] = -1; // value array의 모든 원소를 -1로 초기화
		}
		size = 0; // 현재 가지고 있는 데이터 쌍(key,value) 의 개수
	}
	~HashMap() {}
	// key 값을 활용해서 data값을 return 한다.
	int findData(int k) {
		int hash = k % CAPACITY, count = 0; // hash : hash function 적용 값
		while (count < CAPACITY && key[hash] != -1 && key[hash] != k) {
			//key[hash] != -1(데이터가 있거나, Available 인 경우) 그리고 key값이 중복되지 않는 경우에 loop를 계속 진행한다.
			count++; //loop count 증가
			hash = (hash + 1) % CAPACITY; //오른쪽 칸으로 이동
		}
		if (key[hash] == k) // 사용자로부터 입력받은 key가 있다면, data를 return 하도록 한다.
			return value[hash];
		else return -1; // 없을 시에는 -1를 return 하도록 한다.
	}
	// 매개변수 k값이 key 값 배열 안에 있다는 것을 가정하고, 실행하는 함수.
	// k값이 있는 곳의 인덱스를 return 한다.
	int findIndex(int k) {
		int hash = k % CAPACITY, count = 0; // hash : hash function 적용 값
		while (count < CAPACITY && key[hash] != -1 && key[hash] != k) {
			//key[hash] != -1(데이터가 있거나, Available 인 경우) 그리고 key값이 중복되지 않는 경우에 loop를 계속 진행한다.
			count++; //loop count 증가
			hash = (hash + 1) % CAPACITY; //오른쪽 칸으로 이동
		}
		return hash;
	}
	// 사용자로부터 key와 data를 입력받아 HashMap에 넣는다.
	bool insert(int k, int v) {
		int hash = k % CAPACITY, count = 0, temp = 0;
		bool available = false; // 첫 available 위치를 기억하기 위해 사용.
		for (count = 0; count < CAPACITY; count++) {
			if (key[hash] == k) return false; // 사용자가 입력한 key가 HashMap에 이미 존재한 경우 false로 return 한다.
			//if (key[hash] == -1 || key[hash] == -2) break; //key[hash] == -1 || key[hash] == -2(Available)
			if (key[hash] == -1) break; // 사용되지 않은 빈 슬롯을 발생한 경우 break
			if (key[hash] == -2) {						
				if (!available) {
					// linear probing을 하는 과정에서, available 상태 slot을 발견한 경우
					// temp 변수를 통해 위치값을 저장하고, bool type available 변수를 true로 해서 추가로 available 상태 slot을 발견했을 때
					// temp 값을 수정하지 않도록 한다.
					temp = hash; available = true; 
				}
			}
			hash = (hash + 1) % CAPACITY; // hash 값을 업데이트 한다.
		}
		if (available) {
			// linear probing을 하는 과정에서 available slot이 있었을 때 경우
			key[temp] = k; //temp 위치에 key 값을 넣는다.
			value[temp] = v; //temp 위치에 value 값을 넣는다.
		}
		else {
			// linear probing을 하는 과정에서 available slot이 없었을 때 경우
			key[hash] = k; //hash 위치에 key 값을 넣는다.
			value[hash] = v; //hash 위치에 value 값을 넣는다.
		}
		size++;
		return true; // 정상적으로 key, value가 HashMap에 들어간 경우 true로 return 한다.
	}
	//입력으로 받은 key에 해당하는 곳의 key와 data를 삭제한다.	
	bool remove(int k) {
		int index = 0;
		if (findData(k) == -1) { // k값을 가진 key와 data를 못찾는 경우 데이터가 존재하지 않는다. 정상적으로 제거되지 않았으므로 false return
			return false;
		}
		index = findIndex(k); // 입력으로 받은 key에 해당하는 인덱스를 받아온다. (findIndex)
		key[index] = -2; //해당 slot의 상태를 available로 설정한다.
		value[index] = -1; //index에 해당하는 value값은 -1로 초기화한다.
		size--;
		return true;
	}
	// Hash Map의 Status를 출력하는 함수
	void showStatus() {
		int index = 0;
		for (index = 0; index < CAPACITY; index++) {
			if (key[index] < 0) {
				if (key[index] == -1) continue;
				else // key[index] == -2 : Avaliable (사용된 흔적이 있지만 비어있는 상태) 
					cout << "[index : " << index << "]\t[Key : A]" << endl;
			}
			else {
				// key[index]에 key값이 있는 경우, key값과 value값을 출력한다.
				cout << "[index : " << index << "]\t[Key : " << key[index] << "]\t[Data : " << value[index] << "]" << endl;
			}
		}
	}
	int getSize() { return size; } // HashMap에 들어있는 데이터 쌍의 개수
	bool empty() { return size == 0 ? true : false; } // HashMap이 비어있는지 아닌지
private:
	int key[CAPACITY]; // key 배열
	int value[CAPACITY]; // data 배열
	int size; // HashMap에 들어있는 데이터 쌍의 개수
};

int main() {
	HashMap map; // main 함수 내에서 사용할 HashMap
	char ch; 
	int key, data; // 입력받을 key값과 value값
	int value; // find 연산 시 출력할 결과값
	while (1) {
		cin >> ch;
		if (ch == 'X' || ch == 'x') break; // X를 입력하면 프로그램 종료
		switch (ch) {
		case 'I':
		case 'i':
			cin >> key >> data; // key 값, data 값 입력
			if (!map.insert(key, data)) // HashMap에서 insert 연산 수행
				cout << "Duplicate Key" << endl; // insert 연산이 false로 출력되는 것은 입력한 key값을 이미 Map에서 가지고 있다는 것을 의미한다.
			break;
		case 'D':
		case 'd':
			cin >> key; // key 값 입력
			if (!map.remove(key)) // HashMap에서 remove(delete) 연산 수행
				cout << "Not exists" << endl; // remove 연산이 false로 출력되는 것은 입력받은 key에 대한 데이터가 존재하지 않는 것을 의미한다.
			break;
		case 'F':
		case 'f':
			cin >> key; // key 값 입력
			value = map.findData(key); // key 값을 활용해서 데이터를 얻어온다.
			if (value == -1)
				cout << "Not found" << endl; // Data 범위가 0 < value < 2^15 이므로, -1이 return 된 경우 데이터가 없다는 의미.
			else
				cout << value << endl; // 정상적으로 데이터 출력
			break;
		case 'S':
		case 's':
			map.showStatus(); // 현재 Map Status 출력
			break;
		default:
			break;
		}
	}
	return 0;
}