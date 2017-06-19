#include <cstdlib> // EXIT_SUCCESS 제공
#include <iostream> // I/O 정의
#include <vector> // vector 제공
#include <algorithm> // sort, random shuffle 제공

using namespace std; // std namespace 사용

int main() {
	int a[] = { 17, 12, 33, 15, 62, 45 };
	vector<int> v(a, a + 6); // v: 17 12 33 15 62 45
	char b[] = { 'b', 'r', 'a', 'v', 'o' };
	vector<char> w(b, b + 5); // w: b r a v o

	cout << v.size() << endl; // 6

	v.pop_back(); // v: 17 12 33 15 62
	cout << v.size() << endl; // 5

	v.push_back(19); // v: 17 12 33 15 62 19
	cout << v.front() << " " << v.back() << endl; // 17 19

	sort(v.begin(), v.begin() + 4); // v: (12 15 17 33) 62 19
	v.erase(v.end() - 4, v.end() - 2); // v: 12 15 62 19
	cout << v.size() << endl; // outputs: 4
		
	random_shuffle(w.begin(), w.end()); // b r a v o 5개의 문자열이 순서대로 섞임.
	w.insert(w.begin(), 's'); // w vector 맨앞에 s 문자를 삽입

	for (vector<char>::iterator p = w.begin(); p != w.end(); ++p)
		cout << *p << " "; // position 기준으로 순서대로 출력
	cout << endl;
	return EXIT_SUCCESS;
}