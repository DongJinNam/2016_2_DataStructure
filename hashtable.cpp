#include <iostream>
#define CAPACITY 257 // HashMap�� ��� �ִ� key, value ������ �迭 ������

using namespace std;

//Linear Probing ��� Hash Table Class
class HashMap {
public:
	// HashMap�� ������
	HashMap() {
		// key Array, value Array �ʱ�ȭ
		for (int i = 0; i < CAPACITY; i++) {
			key[i] = -1; // key array�� ��� ���Ҹ� -1�� �ʱ�ȭ
			value[i] = -1; // value array�� ��� ���Ҹ� -1�� �ʱ�ȭ
		}
		size = 0; // ���� ������ �ִ� ������ ��(key,value) �� ����
	}
	~HashMap() {}
	// key ���� Ȱ���ؼ� data���� return �Ѵ�.
	int findData(int k) {
		int hash = k % CAPACITY, count = 0; // hash : hash function ���� ��
		while (count < CAPACITY && key[hash] != -1 && key[hash] != k) {
			//key[hash] != -1(�����Ͱ� �ְų�, Available �� ���) �׸��� key���� �ߺ����� �ʴ� ��쿡 loop�� ��� �����Ѵ�.
			count++; //loop count ����
			hash = (hash + 1) % CAPACITY; //������ ĭ���� �̵�
		}
		if (key[hash] == k) // ����ڷκ��� �Է¹��� key�� �ִٸ�, data�� return �ϵ��� �Ѵ�.
			return value[hash];
		else return -1; // ���� �ÿ��� -1�� return �ϵ��� �Ѵ�.
	}
	// �Ű����� k���� key �� �迭 �ȿ� �ִٴ� ���� �����ϰ�, �����ϴ� �Լ�.
	// k���� �ִ� ���� �ε����� return �Ѵ�.
	int findIndex(int k) {
		int hash = k % CAPACITY, count = 0; // hash : hash function ���� ��
		while (count < CAPACITY && key[hash] != -1 && key[hash] != k) {
			//key[hash] != -1(�����Ͱ� �ְų�, Available �� ���) �׸��� key���� �ߺ����� �ʴ� ��쿡 loop�� ��� �����Ѵ�.
			count++; //loop count ����
			hash = (hash + 1) % CAPACITY; //������ ĭ���� �̵�
		}
		return hash;
	}
	// ����ڷκ��� key�� data�� �Է¹޾� HashMap�� �ִ´�.
	bool insert(int k, int v) {
		int hash = k % CAPACITY, count = 0, temp = 0;
		bool available = false; // ù available ��ġ�� ����ϱ� ���� ���.
		for (count = 0; count < CAPACITY; count++) {
			if (key[hash] == k) return false; // ����ڰ� �Է��� key�� HashMap�� �̹� ������ ��� false�� return �Ѵ�.
			//if (key[hash] == -1 || key[hash] == -2) break; //key[hash] == -1 || key[hash] == -2(Available)
			if (key[hash] == -1) break; // ������ ���� �� ������ �߻��� ��� break
			if (key[hash] == -2) {						
				if (!available) {
					// linear probing�� �ϴ� ��������, available ���� slot�� �߰��� ���
					// temp ������ ���� ��ġ���� �����ϰ�, bool type available ������ true�� �ؼ� �߰��� available ���� slot�� �߰����� ��
					// temp ���� �������� �ʵ��� �Ѵ�.
					temp = hash; available = true; 
				}
			}
			hash = (hash + 1) % CAPACITY; // hash ���� ������Ʈ �Ѵ�.
		}
		if (available) {
			// linear probing�� �ϴ� �������� available slot�� �־��� �� ���
			key[temp] = k; //temp ��ġ�� key ���� �ִ´�.
			value[temp] = v; //temp ��ġ�� value ���� �ִ´�.
		}
		else {
			// linear probing�� �ϴ� �������� available slot�� ������ �� ���
			key[hash] = k; //hash ��ġ�� key ���� �ִ´�.
			value[hash] = v; //hash ��ġ�� value ���� �ִ´�.
		}
		size++;
		return true; // ���������� key, value�� HashMap�� �� ��� true�� return �Ѵ�.
	}
	//�Է����� ���� key�� �ش��ϴ� ���� key�� data�� �����Ѵ�.	
	bool remove(int k) {
		int index = 0;
		if (findData(k) == -1) { // k���� ���� key�� data�� ��ã�� ��� �����Ͱ� �������� �ʴ´�. ���������� ���ŵ��� �ʾ����Ƿ� false return
			return false;
		}
		index = findIndex(k); // �Է����� ���� key�� �ش��ϴ� �ε����� �޾ƿ´�. (findIndex)
		key[index] = -2; //�ش� slot�� ���¸� available�� �����Ѵ�.
		value[index] = -1; //index�� �ش��ϴ� value���� -1�� �ʱ�ȭ�Ѵ�.
		size--;
		return true;
	}
	// Hash Map�� Status�� ����ϴ� �Լ�
	void showStatus() {
		int index = 0;
		for (index = 0; index < CAPACITY; index++) {
			if (key[index] < 0) {
				if (key[index] == -1) continue;
				else // key[index] == -2 : Avaliable (���� ������ ������ ����ִ� ����) 
					cout << "[index : " << index << "]\t[Key : A]" << endl;
			}
			else {
				// key[index]�� key���� �ִ� ���, key���� value���� ����Ѵ�.
				cout << "[index : " << index << "]\t[Key : " << key[index] << "]\t[Data : " << value[index] << "]" << endl;
			}
		}
	}
	int getSize() { return size; } // HashMap�� ����ִ� ������ ���� ����
	bool empty() { return size == 0 ? true : false; } // HashMap�� ����ִ��� �ƴ���
private:
	int key[CAPACITY]; // key �迭
	int value[CAPACITY]; // data �迭
	int size; // HashMap�� ����ִ� ������ ���� ����
};

int main() {
	HashMap map; // main �Լ� ������ ����� HashMap
	char ch; 
	int key, data; // �Է¹��� key���� value��
	int value; // find ���� �� ����� �����
	while (1) {
		cin >> ch;
		if (ch == 'X' || ch == 'x') break; // X�� �Է��ϸ� ���α׷� ����
		switch (ch) {
		case 'I':
		case 'i':
			cin >> key >> data; // key ��, data �� �Է�
			if (!map.insert(key, data)) // HashMap���� insert ���� ����
				cout << "Duplicate Key" << endl; // insert ������ false�� ��µǴ� ���� �Է��� key���� �̹� Map���� ������ �ִٴ� ���� �ǹ��Ѵ�.
			break;
		case 'D':
		case 'd':
			cin >> key; // key �� �Է�
			if (!map.remove(key)) // HashMap���� remove(delete) ���� ����
				cout << "Not exists" << endl; // remove ������ false�� ��µǴ� ���� �Է¹��� key�� ���� �����Ͱ� �������� �ʴ� ���� �ǹ��Ѵ�.
			break;
		case 'F':
		case 'f':
			cin >> key; // key �� �Է�
			value = map.findData(key); // key ���� Ȱ���ؼ� �����͸� ���´�.
			if (value == -1)
				cout << "Not found" << endl; // Data ������ 0 < value < 2^15 �̹Ƿ�, -1�� return �� ��� �����Ͱ� ���ٴ� �ǹ�.
			else
				cout << value << endl; // ���������� ������ ���
			break;
		case 'S':
		case 's':
			map.showStatus(); // ���� Map Status ���
			break;
		default:
			break;
		}
	}
	return 0;
}