//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <complex>
#include <set>

using namespace std;
#define Foreach(i, c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define For(i,a,b) for(int (i)=(a);(i) < (b); ++(i))
#define rof(i,a,b) for(int (i)=(a);(i) > (b); --(i))
#define rep(i, c)  for(auto &(i) : (c))
#define x     first
#define y     second
#define pb  push_back
#define PB  pop_back()
#define iOS  ios_base::sync_with_stdio(false)
#define sqr(a)  (((a) * (a)))
#define all(a)  a.begin() , a.end()
#define error(x) cerr << #x << " = " << (x) <<endl
#define Error(a,b) cerr<<"( "<<#a<<" , "<<#b<<" ) = ( "<<(a)<<" , "<<(b)<<" )\n";
#define errop(a) cerr<<#a<<" = ( "<<((a).x)<<" , "<<((a).y)<<" )\n";
#define coud(a,b) cout<<fixed << setprecision((b)) << (a)
#define L(x)  ((x)<<1)
#define R(x)  (((x)<<1)+1)
#define umap  unordered_map
//#define max(x,y)  ((x) > (y) ? (x) : (y))
#define double long double
typedef long long ll;
typedef pair<int,int>pii;
typedef vector<int> vi;
typedef complex<double> point;
inline vi prefix(string p){
	vi pi;
	int m = p.size();
	For(i,0,m)
		pi.pb(-1);
	int k = -1;
	For(i,1,m){
		while(k != -1 && p[k+1] != p[i])
			k = pi[k];
		if(p[k+1] == p[i])
			k++;
		pi[i] = k;
	}
	return pi;
}
set<int> s;
inline void shift(string p){
	vector<int> pi = prefix(p);
	int m = p.size();
	int k = pi[m-1];
	while(k!=-1){
		s.insert(m-k);
        cerr << m-k << " ";
		k = pi[k];
	}
    cerr << endl;
}
int main(){
    iOS;
	ll n,m;
	cin >> n >> m;
	string p;
	cin >> p;
	vi pi = prefix(p);

    for (ll i = 0; i < pi.size(); ++i) {
        cerr << pi[i] << " ";
    }
    cerr << endl;

	shift(p);
	vi v;
	For(i,0,m){
		int a;
		cin >> a;
		v.pb(a);
	}
	bool ok = true;
	For(i,1,v.size()){
		ll r = v[i] , l=v[i-1];
		if(r<(l+p.size()) && s.find((r-l+1))==s.end()){
				cout << 0 << endl;
				ok = false;
				break;
		}
		if((p.size()+r-1)>n && ok){
				cout<< 0 <<endl;
				ok = false;
				break;
		}
	}
	ll x = n;
	if(ok){
		v.pb(2000000000);
		For(i,0,v.size()-1)
			x -= min((int)p.size(),v[i+1]-v[i]);

	}
	ll ans=1;
	if(x < 0 && ok){
				cout<< 0 <<endl;
				ok = false;
	}
	For(i,0,x)
		ans = (ans*(ll)26) % 1000000007;
	if(ok)
		cout<< ans <<endl;
}


