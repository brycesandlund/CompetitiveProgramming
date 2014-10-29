#include<vector>
#include<iostream>
#include<cmath>

#define EP 1e-10

using namespace std;

typedef double T;

struct Pt {
    T x;
    T y;

    Pt(T x, T y) : x(x), y(y) {}
};

Pt operator - ( const Pt &a, const Pt &b ) { return Pt(a.x-b.x, a.y-b.y); }
Pt operator * ( const Pt &a, const T s ) { return Pt(s*a.x, s*a.y); }
Pt operator + ( const Pt &a, const Pt &b ) { return Pt(a.x+b.x, a.y+b.y); }

T cross( const Pt &a, const Pt &b ) { return a.x*b.y - a.y*b.x; }

bool on(Pt a, Pt b, Pt q)
{
    if (q.x <= max(a.x, b.x) + EP && q.x >= min(a.x, b.x) - EP
            && q.y <= max(a.y, b.y) + EP && q.y >= min(a.y, b.y) - EP)
        return true;

    return false;
}

bool intersect(Pt a, Pt b,  Pt c, Pt d) 
{
    Pt b2=b-a, d2=d-c, c2=c-a;

    if (abs(cross(b2,d2)) < EP)
        return false;

    Pt result = a + b2*cross(c2,d2)*(1/cross(b2,d2));

    return on(a, b, result) && on(c, d, result);
}

int main()
{
    int n;
    cin >> n;

    for (int caseNum = 1; caseNum <= n; ++caseNum)
    {
        int xstart, ystart, xend, yend, xleft, ytop, xright, ybottom;
        cin >> xstart >> ystart >> xend >> yend >> xleft >> ytop >> xright >> ybottom;
        
        Pt lineA(xstart, ystart), lineB(xend, yend), topLeft(xleft, ytop), botRight(xright, ybottom), botLeft(xleft, ybottom), topRight(xright, ytop);

        cout << (intersect(lineA, lineB, topLeft, topRight) || intersect(lineA, lineB, topRight, botRight) || intersect(lineA, lineB, botLeft, botRight) || intersect(lineA, lineB, botLeft, topLeft) ? "T" : "F") << endl;
    }
}
