#include <iostream>
#include <climits>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <string>
#include <algorithm>
#include <cmath>

#define oo INT_MAX

using namespace std;

double cross(double x1,double y1,double x2,double y2){
	return x1*y2-x2*y1;
}
double dot(double x1,double y1,double x2,double y2){
	return x1*x2+y1*y2;
}

int main(){
	for(int traps=0,cases=1;cin>>traps && traps!=0;cases++){
		vector<double>x;
		vector<double>y;
		for(int i=0;i<traps;i++){
			double x1,y1;
			cin>>x1>>y1;
			x.push_back(x1);
			y.push_back(y1);
		}
		int p=0; //present point
		bool* used=new bool[traps];
		memset(used,false,sizeof(used));
		for(int i=0;i<x.size();i++){
			if(x[i]<x[p])
				p=i;
		}
		int start=p;
		double perimeter=0;
		
        if (cases > 0)
            cout << endl;
        
        cout<<"Region #"<<cases<<":"<<endl;
		printf("(%.1f,%.1f)",x[p],y[p]);
		do{
			int n=-1;
			int dist=oo;
			for(int i=0;i<x.size();i++){
				if(i==p)
					continue;
				if(used[i])
					continue;
				if(n==-1) {
					n=i;
                    continue;
                }
				double ipx=x[i]-x[p];
				double ipy=y[i]-y[p];
				double npx=x[n]-x[p];
				double npy=y[n]-y[p];
				double cr=cross(ipx,ipy,npx,npy);

				double d=dot(ipx,ipy,ipx,ipy);
				if(cr<0){
					n=i;
					dist=d;
				}
				else if(cr==0){
					if(d<dist){
						dist=d;
						n=i;
					}
				}
			}
			double npx=x[n]-x[p];
			double npy=y[n]-y[p];
			perimeter+=sqrt(dot(npx,npy,npx,npy));
			p=n;
			used[p]=true;
			printf("-(%.1f,%.1f)",x[p],y[p]);
		}while(start!=p);
		cout<<endl;
        printf("Perimeter length = %.2lf\n", perimeter);
	}
}
