/*
   2  Problem link
   3  Type: Data structure - segment tree
   4  Algorithm:
   5      Segment tree:
   6          For problems having range queries, segment tree is
   7          one good data structures to kill them!
   8
   9          For a segment tree, a node of the tree controls
   10          a specific range from our array. For example:
   11          We have 6 elements in our array, node[1] will
   12          control range [0..5], its children node[1*2] and
   13          node[1*2+1] will control range [0..2] and [3..5]
   14          and so on.
   15
   16      In this problem, at first we build the tree (st_build)
   17      by traversing down to each leaf nodes to calculate their
   18      value, the value of a non-leaf node will be the sum of
   19      its children. I will explain later why we need to save
   20      the cast type of the magician for each node (start with -1
   21      means no cast type) this take O(n)
   22
   23      Usually for this type of problem, on the update queries
   24      (change 0..3 to 1 for example), we think of traversing down
   25      to 0 1 2 3 to change the value and go up again. This will take
   26      O(n) for each queries in the worst case and is not effective.
   27
   28      The solution for this called "lazy - update", that is, we will
   29      update once the range of the current node is in the range of the
   30      update query, not to the leaf nodes.
   31
   32      The function <change> will change the value of the node that fits
   33      inside the range of the query AND UPDATE THE CAST TYPE OF ITS
   34      CHILDREN. This step is important because if later there is a
   35      question query that ask for a range lower than the current range
   36      we've just updated, we need to traverse down and base on
   37      the cast type information, update the nodes as well.
   38      For example: array has 6 elements: [0..5] = 0
   39          Change [0..2] to 1: we stop at node 2:
   40              node[2].value = 3, node[2].utype = F
   41              Update its children utype:
   42              node[2*2].value = 0 // not updated,
   43              node[2*2].utype = F // Like father like son
   44              node[2*2+1].value = 0 // not updated,
   45              node[2*2+1].utype = F // Like father like son
   46              node[2].utype = NULL // We are not gonna update it again
   47          Answer [0]:
   48              Traverse to node[4]: [0..1]:
   49                  Its utype is F -> change its value to 2
   50                  Change its children utype
   51              Go down to node[8]: [0]:
   52                  Its utype is F -> Change its value to 1
   53                  --> This is the answer
   54      A little different on the I type, you should see the code below
   55  */
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;
typedef vector<int> vi;
const int maxn = 1024010;
class node {
public:
    int value, len;
    char utype;
};
node tree[5*maxn];
vi a;

void st_build(node tree[], int vertex, int l, int r);
void change(int i);
void set_utype(int vertex, char type);
void update(int vertex, int l, int r, int i, int j, char type);
int answer(int vertex, int l, int r, int i, int j);
int main()
{
    char ch;
    int n,t,ntest,q,u,v;
    string str;
    cin >> ntest;
    for (int test=1; test<=ntest; test++)
    {
        a.clear();
        printf("Case %d:\n",test);
        cin >> n;
        for (int i=1; i<=n; i++)
        {
            cin >> t;
            getline(cin,str);
            getline(cin,str);
            for (int j=1; j<=t; j++)
                for (unsigned int k=0; k<str.length(); k++) a.push_back(int(str[k])-48);
        }
        st_build(tree,1,0,a.size()-1);
        int cnt = 0;
        cin >> q;
        for (int i=1; i<=q; i++)
        {
            cin >> ch >> u >> v;
            if (ch!='S') update(1,0,a.size()-1,u,v,ch);
            else
            {
                cnt++;
                cout << "Q" << cnt << ": " << answer(1,0,a.size()-1,u,v) << endl;
            }
        }
    }
}

void st_build(node tree[], int vertex, int l, int r) {
    if (l==r)                       //If it's a leaf node, set its value to a[l] or a[r]
    {
        tree[vertex].value = a[l];
        tree[vertex].utype = -1;
        tree[vertex].len = 1;
    }
    else
    {
        int mid = (l+r)/2;
        st_build(tree, vertex*2, l, mid);       //Calculate its children
        st_build(tree, vertex*2+1, mid+1, r);
        tree[vertex].value = tree[vertex*2].value + tree[vertex*2+1].value; //Calculate its value
        tree[vertex].utype = -1;
        tree[vertex].len = r-l+1;
    }
}                

void change(int i) {            //Apply the appropriate cast
    switch(tree[i].utype)
    {
        case 'F': tree[i].value = tree[i].len; break;
        case 'E': tree[i].value = 0; break;
        case 'I': tree[i].value = tree[i].len-tree[i].value; break;
        default: return;
    }
    set_utype(i*2,tree[i].utype);   //After applying, push down the cast type to its childrend
    set_utype(i*2+1,tree[i].utype);
    tree[i].utype = -1;             //Its cast type is now NULL
}

void set_utype(int vertex, char type) {
    if (type=='I')                  //Special case
    {
        switch(tree[vertex].utype)
        {
            case 'F': tree[vertex].utype = 'E'; break;
            case 'E': tree[vertex].utype = 'F'; break;
            case 'I': tree[vertex].utype = -1; break;
            case -1: tree[vertex].utype = 'I'; break;
            default: break;
        }
    }
    else tree[vertex].utype = type;
}
                
void update(int vertex, int l, int r, int i, int j, char type) {
    int mid = (l+r)/2;
    if (l>=i && r<=j) set_utype(vertex,type);   //If it fits in the interval, set it cast type
    change(vertex);                             //Do the cast type
    if (l>=i && r<=j) return;
    else
    if (l>j || r<i) return;                     //If it's out then quit
    else
    {
        update(vertex*2,l,mid,i,j,type);
        update(vertex*2+1,mid+1,r,i,j,type);
        tree[vertex].value = tree[vertex*2].value+tree[vertex*2+1].value;
    }
}

int answer(int vertex, int l, int r, int i, int j) {
    int mid = (l+r)/2;
    change(vertex);             //As traversing down, update the cast type of current index
    if (l>=i && r<=j) return(tree[vertex].value);
    if (l>j || r<i) return(0);
    int p1 = answer(vertex*2,l,mid,i,j);
    int p2 = answer(vertex*2+1,mid+1,r,i,j);
    tree[vertex].value = tree[vertex*2].value+tree[vertex*2+1].value;
    return(p1+p2);
}
