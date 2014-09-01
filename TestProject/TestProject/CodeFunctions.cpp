//============================================================================
// Name        :
// Author      : Bryce Sandlund
// Version     :
// Copyright   :
// Description : Code reference functions/ algorithms
//============================================================================

#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <list>
#include <map>
#include <fstream>
#include <string>
#include <time.h>
#include <queue>
#include <tuple>
#include <functional>
//#include <unordered_set>
//#include <unordered_map>
//#include <ctgmath>

#define INF 1000000000
#define all(c) (c).begin(),(c).end()
#define tr(c,i) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define EP .00001

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

/*******************************************
********************graph*******************
*******************************************/
// Union-Find Disjoint Sets Library written in OOP manner, using both path compression and union by rank heuristics
class UnionFind {                                              // OOP style
private:
  vi p, rank, setSize;                       // remember: vi is vector<int>
  int numSets;
public:
  UnionFind(int N) {
    setSize.assign(N, 1); numSets = N; rank.assign(N, 0);
    p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i; }
  int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
  void unionSet(int i, int j) { 
    if (!isSameSet(i, j)) { numSets--; 
    int x = findSet(i), y = findSet(j);
    // rank is used to keep the tree short
    if (rank[x] > rank[y]) { p[y] = x; setSize[x] += setSize[y]; }
    else                   { p[x] = y; setSize[y] += setSize[x];
                             if (rank[x] == rank[y]) rank[y]++; } } }
  int numDisjointSets() { return numSets; }
  int sizeOfSet(int i) { return setSize[findSet(i)]; }
};

int kruskal(vector< pair<int, ii> > &EdgeList, int V)
{
	sort(EdgeList.begin(), EdgeList.end()); // sort by edge weight O(E log E)
                      // note: pair object has built-in comparison function

	int mst_cost = 0;
	UnionFind UF(V);                     // all V are disjoint sets initially
	for (int i = 0; i < EdgeList.size(); i++) {                      // for each edge, O(E)
	pair<int, ii> front = EdgeList[i];
	if (!UF.isSameSet(front.second.first, front.second.second)) {  // check
		mst_cost += front.first;                // add the weight of e to MST
		UF.unionSet(front.second.first, front.second.second);    // link them
	} }                       // note: the runtime cost of UFDS is very light

	return mst_cost;
}

vi dijkstra(vector<vii> &AdjList, int s)
{
  int V = AdjList.size();

  // Dijkstra routine
  vi dist(V, INF); dist[s] = 0;                    // INF = 1B to avoid overflow
  priority_queue< ii, vector<ii>, greater<ii> > pq; pq.push(ii(0, s));
         // ^to sort the pairs by increasing distance from s
  while (!pq.empty()) {                                             // main loop
    ii front = pq.top(); pq.pop();     // greedy: pick shortest unvisited vertex
    int d = front.first, u = front.second;
    if (d > dist[u]) continue;   // this check is important, see the explanation
    for (int j = 0; j < (int)AdjList[u].size(); j++) {
      ii v = AdjList[u][j];                       // all outgoing edges from u
      if (dist[u] + v.second < dist[v.first]) {
        dist[v.first] = dist[u] + v.second;                 // relax operation
        pq.push(ii(dist[v.first], v.first));
  } } }  // note: this variant can cause duplicate items in the priority queue

  return dist;
}

/*******************************************
***************polynomial stuff*************
*******************************************/

vector<long double> derive(vector<long double> poly)
{
	vector<long double> newPoly(poly.size()-1);
	for (int i = 0; i < poly.size() - 1; ++i)
	{
		newPoly[i] = poly[i+1]*(i+1);
	}
	return newPoly;
}

//multiplies poly1 of size n with poly2 of size m in O(nm) time (better possible with FFT)
vector<long double> multiply(vector<long double> poly1, vector<long double> poly2)
{
	vector<long double> result(poly1.size() + poly2.size() - 1, 0);
	for (int i = 0; i < poly1.size(); ++i)
	{
		for (int j = 0; j < poly2.size(); ++j)
		{
			result[i+j] += poly1[i] * poly2[j];
		}
	}
	return result;
}

//computes the polynomial of size n to the power p in O(pn) time
vector<long double> toThePower(vector<long double> poly, int power)
{
	vector<long double> result(poly);
	for (int i = 1; i < power; ++i)
	{
		result = multiply(result, poly);
	}
	return result;
}

//finds where x where ax^2 + bx + c = 0 or returns the empty vector. Works for a == 0. If b == 0 or discriminant = 0, returns empty vector.
vector<long double> qFormula(long double a, long double b, long double c)
{
	vector<long double> ans;
	if (a == 0)
	{
		if (b == 0)
		{
			return ans;
		}
		ans.push_back(-1 * c / b);
	}
	long double discriminant = b*b-4*a*c;
	if (discriminant < 0)
		return ans;
	ans.push_back((-b+sqrt(discriminant))/(2*a));
	ans.push_back((-b-sqrt(discriminant))/(2*a));
	return ans;
}

//evaluates the polynomial at position x
long double polyAt(vector<long double> poly, long double x)
{
	long double ans = 0;
	for (int i = 0; i < poly.size(); ++i)
	{
		ans += pow(x, i)*poly[i];
	}
	return ans;
}

/*******************************************
***************vector geometry**************
*******************************************/

long double dotProd(vector<long double> one, vector<long double> two)
{
	long double sum = 0;
	for (int i = 0; i < one.size(); ++i)
	{
		sum += one[i] * two[i];
	}
	return sum;
}

vector<long double> crossProd(vector<long double> first, vector<long double> second)
{
	vector<long double> result(3);
	result[0] = first[1] * second[2] - first[2] * second[1];
	result[1] = -1 * (first[0] * second[2] - first[2] * second[0]);
	result[2] = first[0] * second[1] - first[1] * second[0];
	return result;
}

vector<long double> vMinus(vector<long double> x1, vector<long double> x2)
{
	vector<long double> result(x1.size());
	for (int i = 0; i < result.size(); ++i)
	{
		result[i] = x1[i] - x2[i];
	}
	return result;
}

long double magnitude(vector<long double> x)
{
	long double sum = 0;
	for (int i = 0; i < x.size(); ++i)
	{
		sum += x[i] * x[i];
	}
	return sqrt(sum);
}

//returns the value of t where the 3-dimensional line from x1 to x2 has shortest distance to point x0
//note: for this to work, x1 should be the point where t = 0 and x2 where t = 1
long double time(vector<long double> x0, vector<long double> x1, vector<long double> x2)
{
	return -1 * dotProd(vMinus(x1, x0), vMinus(x2, x1)) / pow(magnitude(vMinus(x2, x1)), 2);
}

/*******************************************
********************debug*******************
*******************************************/
//print container
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

//print container of containers
template
    < typename T
    , template<typename ELEM, typename ALLOC=std::allocator<ELEM> > class Container
    , template<typename ELEM, typename ALLOC=std::allocator<ELEM> > class Container2
    >
std::ostream& operator<< (std::ostream& o, const Container<Container2<T> >& container)
{
	typename Container<Container2<T> >::const_iterator beg = container.begin();
	o << "[";
	if (beg != container.end())
	{
		o << *beg;
		++beg;
		if (beg != container.end())
			o << endl;
	}
	for (; beg != container.end()-1 && beg != container.end(); ++beg)
	{
		o << " ";
		o << *beg;
		o << endl;
	}
	if (beg != container.end())
	{
		cout << " ";
		o << *beg;
	}
	cout << "]";
	return o;
}

//print set
template < typename T>
std::ostream& operator<< (std::ostream& o, const set<T> container)
{
	typename set<T>::const_iterator beg = container.begin();
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

//print pair
template < typename T, typename V>
std::ostream& operator<< (std::ostream& o, const pair<T, V> p)
{
	o << "(" << p.first << ", " << p.second << ")";
	return o;
}

//print map
template < typename T, typename V>
std::ostream& operator<< (std::ostream& o, const map<T, V> mp)
{
	typename map<T, V>::const_iterator beg = mp.begin();
	o << "[";
	if (beg != mp.end())
	{
		o << *beg;
		++beg;
	}
	for (; beg != mp.end(); ++beg)
	{
		o << ", " << *beg;
	}
	o << "]";
	return o;
}

/*******************************************
****************combinatorics***************
*******************************************/
//naively computes nCr
long long nCr(int n, int r)
{
	if (r > n || n < 0 || r < 0)
	{
		return 0;
	}
	long long total = 1;
	for (int num = n-r+1, den = 1; den <= r; ++num, ++den)
	{
		total *= num;
		if (total < 0)
			cerr << "overflow in nCr" << endl;
		total /= den;
	}
	return total;
}

long long nPr(int n, int r)
{
	if (r > n)
	{
		return 0;
	}
	long long total = 1;
	for (int i = n; n-i < r; --i)
	{
		total *= i;
	}
	return total;
}

long long nPowr(int n, int r)
{
	long long total = 1;
	for (int i = 0; i < r; ++i)
	{
		total *= n;
	}
	return total;
}

long long factorial(int n)
{
	long long cur = 1;
	for (int i = 1; i <= n; ++i)
	{
		cur *= i;
		if (cur < 0)
		{
			cerr << "overflow in factorial" << endl;
		}
	}
	return cur;
}

#define SIZE 100
vector<vector<long long> > nCrMemo(SIZE, vector<long long>(SIZE, -1));

long long nCr(int n, int r, long long q)
{
	if (n < 0 || r < 0 || r > n)
	{
		return 0;
	}
	if (n > SIZE || r > SIZE)
	{
		cerr << "Error, n or r too large" << endl;
		return -1;
	}
	if (nCrMemo[n][r] != -1)
	{
		return nCrMemo[n][r];
	}
	if (n == r || r == 0)
	{
		return 1;
	}
	long long ans = (nCr(n-1, r-1, q) + nCr(n-1, r, q)) % q;
	nCrMemo[n][r] = ans;
	return ans;
}

long double binomial(int success, int attempts, long double pSuccess)
{
	vector<long double> nCrs;
	for (int num = attempts, den = success; den > 0; --num, --den)
	{
		nCrs.push_back(num / (long double)den);
	}
	vector<long double> ps(attempts);
	for (int i = 0; i < attempts; ++i)
	{
		if (i < success)
		{
			ps[i] = pSuccess;
		}
		else
		{
			ps[i] = 1 - pSuccess;
		}
	}

	long double prob = 1;
	int ns = 0;
	for (int i = 0; i < nCrs.size(); ++i)
	{
		prob *= nCrs[i];
		while (prob > 1)
		{
			prob *= ps[ns++];
		}
	}
	for (; ns < attempts; ++ns)
	{
		prob *= ps[ns];
	}
	return prob;
}

long double probOccurence(int total, int favorable, int selection, int needed)
{
	return nCr(favorable, needed) * nCr(total - favorable, selection - needed) / (long double)nCr(total, selection);
}

/*******************************************
****************miscellaneous***************
*******************************************/
//convert to base from decimal
vector<int> convertTo(int num, int base)
{
	vector<int> numB;
	while (num != 0)
	{
		numB.push_back(num % base);
		num /= base;
	}
	vector<int> numB2(numB.rbegin(), numB.rend());
	return numB2;
}

//convert from base to decimal
int convertFrom(vector<int> num, int base)
{
	int sum = 0;
	int power = 1;
	for (int i = num.size()-1; i >= 0; --i)
	{
		sum += power * num[i];
		power *= base;
	}
	return sum;
}


//binary indexed tree - taken from Stanford ACM
#define LOGSZ 17

int ft[(1<<LOGSZ)+1];
int N = (1<<LOGSZ);

// add v to value at x
void adjust(int x, int v) {
  while(x <= N) {
    ft[x] += v;
    x += (x & -x);
  }
}

// get cumulative sum up to and including x
int rsq(int x) {
  int res = 0;
  while(x) {
    res += ft[x];
    x -= (x & -x);
  }
  return res;
}

// get largest value with cumulative sum less than or equal to x;
// for smallest, pass x-1 and add 1 to result
int getind(int x) {
  int idx = 0, mask = N;
  while(mask && idx < N) {
    int t = idx + mask;
    if(x >= ft[t]) {
      idx = t;
      x -= ft[t];
    }
    mask >>= 1;
  }
  return idx;
}

//trie
typedef struct trienode
{
	bool word;
	trienode *children[26];
	bool present[26];
} trienode;

trienode *root;

void init (trienode* node)
{
	for (int i = 0; i < 26; ++i)
	{
		node->present[i] = false;
	}
	node->word = false;
}

int charToInt(char c)
{
	return c - 97;
}

void add(string word)
{
	trienode *cur = root;
	for (int i = 0; i < word.size(); ++i)
	{
		int letter = charToInt(word[i]);
		if (cur->present[letter])
		{
			cur = cur->children[letter];
		}
		else
		{
			trienode* newNode = (trienode*) malloc(sizeof(trienode));
			init(newNode);
			cur->present[letter] = true;
			cur->children[letter] = newNode;
			cur = cur->children[letter];
		}
		if (i == word.size() - 1)
		{
			cur->word = true;
		}
	}
}

template < typename T>
void min_max(T &first, T &second)
{
	T tmp = first;
	first = min(first, second);
	second = max(tmp, second);
}

/*******************************************
******************geometry******************
*******************************************/
//this function is incomplete
bool intersects(ii l1s, ii l1e, ii l2s, ii l2e)
{
	int dx1 = l1s.first - l1e.first;
	int dy1 = l1s.second - l1e.second;
	int dx2 = l2s.first - l2e.first;
	int dy2 = l2s.second - l2e.second;
	if (dx1 == dx2)
	{
		min_max(l1s.second, l1e.second);
		min_max(l2s.second, l2e.second);
		return l1e.second <= l2s.second || l2e.second <= l1s.second;
	}
	else if (dy1 == dy2)
	{
		min_max(l1s.first, l1e.first);
		min_max(l2s.first, l2e.first);
		return l1e.first <= l2s.first || l2e.first <= l1s.first;
	}
}

double intersectPt(double m1, double b1, double m2, double b2)
{
	if (m1 == m2)
	{
		cerr << "parallel lines in intersectPt" << endl;
	}
	return (b2-b1)/(m1-m2);
}

/*TODO: -number theory
			-sum of arithmetic sequence
			-sum of geometric sequence
			-sum of squares
			-sum of cubes
			-chinese remainder theorem
			-gcd, egcd

*/

bool isPrime(int n)
{
	for (int i = 2; i < sqrt(n); ++i)
	{
		if (n % i == 0)
		{
			return false;
		}
	}
	return true;
}

vector<int> primesToN(int n)
{
	vector<bool> sieve(n, true);
	vector<int> numbers;
	for (int i = 2; i <= sqrt(n)+EP; ++i)
	{
		if (sieve[i])
		{
			for (int j = i+i; j < n; j += i)
			{
				sieve[j] = false;
			}
		}
	}

	for (int i = 2; i < n; ++i)
	{
		if (sieve[i])
		{
			numbers.push_back(i);
		}
	}

	return numbers;
}



vector<int> primeFactorization(int n, vector<int> &primes)
{
	vector<int> factors;
	for (int i = 0; i <= sqrt(n)+EP; ++i)
	{
		while (n % primes[i] == 0)
		{
			factors.push_back(primes[i]);
			n /= primes[i];
		}
	}

	if (n != 1)
	{
		factors.push_back(n);
	}
	return factors;
}

int main() {
	adjust(4, 4);
	adjust(8, 10);
	adjust(5, 3);

	cout << rsq(5) << endl;

	int asdf;
	cin >> asdf;
	return 0;
}
