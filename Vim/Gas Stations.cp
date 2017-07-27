#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <climits>
#include <queue>
#include <string.h>
#include <cstring>
#include <time.h>
//#include <windows.h>
//#include <conio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

#define ll long long
#define oo INT_MAX

bool myfunc(pair<ll,ll> p1, pair<ll,ll>p2){
	if(p1.first==p2.first)
		return p1.second>p2.second;
	else if(p1.first<=0 && p2.first<=0)
		return p1.second>p2.second;
	else
		return p1.first<p2.first;
}
bool myfunc2(pair<ll,ll> p1, pair<ll,ll>p2){
		return p1.second>p2.second;
}

int main(){
	for(int l,g;cin>>l>>g && l!=0 && g!=0;){
		vector<pair<ll,ll>>ans;
		vector<pair<ll,ll>>vpii;
		for(int i=0;i<g;i++){
			ll x,r;
			cin>>x>>r;
			vpii.push_back(make_pair(x-r,x+r));
		}
		sort(vpii.begin(),vpii.end());
		/*if(vpii[0].first>0){
			cout<<-1<<endl;
			continue;
		}//doesn't cover beginning
		ll max_dist=vpii[0].second;
		for(int i=1;i<vpii.size();i++){
			if(vpii[i].first>max_dist){
				cout<<-1<<endl;//doesn't cover some middle point
				continue;
			}
			else
				max_dist=max(max_dist,vpii[i].second);
		}
		if(max_dist<l){
			cout<<-1<<endl;//doesn't cover end
			continue;
		}*/
		//ans.push_back(vpii[0]);
		ll fin=0;//furthest point reached so far

		int index=0;

		while(fin<l){
			vector<pair<ll,ll>>mid;
			for(;index<vpii.size();index++){
				if(vpii[index].first<=fin)
					mid.push_back(vpii[index]);
				else break;
				}
			if(mid.empty()){
				cout<<-1<<endl;
				break;
			}
			sort(mid.begin(),mid.end(),myfunc2);
			ans.push_back(mid[0]);
			fin=mid[0].second;
		}
		cout<<g-ans.size()<<endl;
	}
}