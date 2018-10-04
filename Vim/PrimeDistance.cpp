#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <utility>
#include <cmath>
#include <limits>
#include <climits>

#define oo INT_MAX

using namespace std;

typedef long long ll;

vector<bool> sieve(ll L,ll U){
	ll m=(ll)ceil(sqrt(U))+1;
    /*
	bool* sqrt_prime=new bool[(ll)ceil(sqrt(U))+1];
	for(ll i=0;i<m;i++)
		sqrt_prime[i]=true;
	sqrt_prime[0]=false;
	sqrt_prime[1]=false;
	for(ll i=2;i<m;i++){
		if(sqrt_prime[i]){
			for(ll k=i+i; k<m;k+=i){
				sqrt_prime[k]=false;
			}
		}
	}*/
	vector<bool> prime(U-L+1,true);
	if (L == 1) prime[0] = false;
	for(ll i=2;i<=m;i++){
		ll start=i*((L+i-1)/i);
        if (start == i) start += i;
		for(ll j=start-L;j<prime.size();j+=i){
			prime[j]=false;
		}
	}
	return prime;	
}

int main(){
	for(ll L,U;cin>>L>>U;){
		vector<bool> prime=sieve(L,U);
        ll mind = oo, maxd = 0;
        ll mind_1, mind_2, maxd_1, maxd_2;
		ll last_prime=-1;
		for(ll i=0;i<prime.size();i++){
			if(prime[i]){
				last_prime=i;
				break;
			}
		}
		for(ll i=last_prime+1;i<prime.size();i++){
			if(prime[i]){
                ll diff = i - last_prime;
            
                if (diff < mind) {
                    mind_1 = last_prime+L;
                    mind_2 = i+L;
                }
                if (diff > maxd) {
                    maxd_1 = last_prime+L;
                    maxd_2 = i+L;
                }
                mind = min(mind, diff);
                maxd = max(maxd, diff);   
                last_prime = i;
			}
		}
		if (mind == oo)
        cout<<"There are no adjacent primes."<<endl;
		else
		cout<<mind_1<<","<<mind_2<<" are closest, "<<maxd_1<<","<<maxd_2<<" are most distant."<<endl;
	
    }
}
