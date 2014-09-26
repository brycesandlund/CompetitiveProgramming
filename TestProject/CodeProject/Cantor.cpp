#include <vector>
#include <iostream>
#include <cmath>
#include <unordered_set>
#include <sstream>
#include <string>

#define EP .00000001

using namespace std;

template
	< typename T
	, template<typename ELEM, typename ALLOC=std::allocator<ELEM> > class Container
	>
	std::ostream& operator<< (std::ostream& o, const Container<T>& container)
{
	typename Container<T>::const_iterator beg = container.begin();
	o << "[";
	if (beg != container.end())
	{
		o << *beg;
		++beg;
	}
	for (; beg != container.end(); ++beg)
	{
		o << ", " << *beg;
	}
	o << "]";
	return o;
}

int main()
{
	cout.precision(20);

	while (true)
	{
		string str;
		cin >> str;
		if (str == "END")
			break;

		stringstream ss;
		ss << str;
		double num;
		ss >> num;

		vector<int> base3;
		int i = 1;
		bool success = true;
		double calcNum = num;
		while (fabs(calcNum) > EP)
		{
			int term = calcNum / (pow(3, -i));

			if (term == 1)
			{
				success = false;
			}

			base3.push_back(term);
			calcNum -= term * pow(3, -i);
			++i;
		}

		cout << (success ? "MEMBER" : "NON-MEMBER") << endl;
	}
}