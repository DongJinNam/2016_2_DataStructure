#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main()
{
	list<int> mylist;
	list<int>::iterator it;

	// 1 2 3 4 5 ������� �ʱ�ȭ
	for (int i = 1; i <= 5; ++i)
		mylist.push_back(i); // 1 2 3 4 5

	it = mylist.begin();
	++it; // ���� 2�� ����Ų��.

	mylist.insert(it, 10); // 1 10 2 3 4 5

	// "it" �� ������ 2�� ����Ų��.
	mylist.insert(it, 2, 20); // 1 10 20 20 2 3 4 5

	--it; // it�� ���� 2 �տ� �ִ� 20�� ����Ų��.

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