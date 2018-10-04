#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>
#include <string.h>
#include <stdlib.h>

#define oo INT_MAX

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<bool> VB;

bool FindMatch(int i, const VVI &adj_list, VI &mr, VI &mc, VB &seen) {
  for (int j = 0; j < adj_list[i].size(); j++) {
    int item = adj_list[i][j];
    if (!seen[item]) {
      seen[item] = true;
      if (mc[item] < 0 || FindMatch(mc[item], adj_list, mr, mc, seen)) {
        mr[i] = item;
        mc[item] = i;
        return true;
      }
    }
  }
  return false;
}

// mr should be a vector of size number of row items, initialized to -1
// mc should be a vector of size number of column items, initialized to -1
int BipartiteMatching(const VVI &adj_list, VI &mr, VI &mc) {
  int ct = 0;
  for (int i = 0; i < adj_list.size(); i++) {
    VB seen(mc.size(), false);
    if (FindMatch(i, adj_list, mr, mc, seen)) ct++;
  }
  return ct;
}

double dist(pair<double,double> p1, pair<double,double> p2){
	return sqrt((p1.first-p2.first)*(p1.first-p2.first) + (p1.second-p2.second)*(p1.second-p2.second));
}

int main(){
	for(int L,cases=1;cin>>L;cases++){
		int n,m;
		cin>>n>>m;
		vector<pair<double,double> > human;
		vector<pair<double,double> > dog;
		for(int i=0;i<n;i++){
			double x,y;
			cin>>x>>y;
			human.push_back(make_pair(x,y));
		}
		vector<pair<double,double> > inter_places;
		for(int i=0;i<m;i++){
			double x,y;
			cin>>x>>y;
			inter_places.push_back(make_pair(x,y));
		}
		vector<vector<int> >vvi(n);
		for(int i=0;(i+1)<human.size();i++){
			double d1=dist(human[i],human[i+1]);
			//cerr<<"points: "<<i<<" "<<i+1<<" d1: "<<d1<<endl;
			for(int j=0;j<inter_places.size();j++){
				double dog_dist=dist(human[i],inter_places[j]);
				double dog_dist2=dist(inter_places[j],human[i+1]);
				//cerr<<"\tdog dist: "<<dog_dist+dog_dist2<<endl;
				if((dog_dist+dog_dist2)<=2*d1){
					vvi[i].push_back(j);
					//cerr<<"i: "<<i<<" j: "<<j<<endl;
				}
			}
		}
		VI mr(n,-1);
		VI mc(n,-1);
		cout<<n+BipartiteMatching(vvi,mr,mc)<<endl;
		for(int i=0;i<n-1;i++){
			if(mr[i]!=-1)
				cout<<human[i].first<<" "<<human[i].second<<" "<<inter_places[mr[i]].first<<" "<<inter_places[mr[i]].second<<" ";
			else cout<<human[i].first<<" "<<human[i].second<<" ";
		}
		cout<<human[n-1].first<<" "<<human[n-1].second<<endl;
		if(cases!=L)
		cout<<endl;
	}
}
