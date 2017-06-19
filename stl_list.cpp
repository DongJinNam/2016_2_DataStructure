#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main()
{
	list<int> mylist;
	list<int>::iterator it;

	// 1 2 3 4 5 순서대로 초기화
	for (int i = 1; i <= 5; ++i)
		mylist.push_back(i); // 1 2 3 4 5

	it = mylist.begin();
	++it; // 이제 2를 가리킨다.

	mylist.insert(it, 10); // 1 10 2 3 4 5

	// "it" 은 여전히 2를 가리킨다.
	mylist.insert(it, 2, 20); // 1 10 20 20 2 3 4 5

	--it; // it은 이제 2 앞에 있는 20을 가리킨다.

	vector<int> myvector(2, 30);
	mylist.insert(it, myvector.begin(), myvector.end());
	// 1 10 20 30 30 20 2 3 4 5
	//               ^
	cout << "mylist contains:";
	for (it = mylist.begin(); it != mylist.end(); ++it)
		cout << ' ' << *it;
	cout << '\n';

	return 0;
}