#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

const double EPS_ABS    = 1e-10;  // for values near 0.0. Keep small.
const double EPS_REL    = 1e-8;   // for values NOT near 0.0. Balance.

bool feq( double a, double b ) {
	double d = fabs(b-a);
	if( d <= EPS_ABS ) return true;
	if( d <= max(fabs(a),fabs(b))*EPS_REL ) return true;
	return false;
}

bool flt( double a, double b ) {
	return !feq(a,b) && a < b;
}

typedef double T;

struct Pt {
	T x, y;
	Pt() {}
	Pt( T x, T y ) : x(x), y(y) {}
	Pt( const Pt &h ) : x(h.x), y(h.y) {}
};

Pt operator + ( const Pt &a, const Pt &b ) { return Pt(a.x+b.x, a.y+b.y); }
Pt operator - ( const Pt &a, const Pt &b ) { return Pt(a.x-b.x, a.y-b.y); }
Pt operator * ( const T s, const Pt &a )   { return Pt(s*a.x, s*a.y); }
Pt operator * ( const Pt &a, const T s )   { return s*a; }
Pt operator / ( const Pt &a, const T s )   { return Pt(a.x/s,a.y/s); }
// Note the kind of division that occurs when using integer types.
// Use rationals if you want this to work right.
bool operator == ( const Pt &a, const Pt &b ) {
	return feq(a.x,b.x) && feq(a.y,b.y);
}
bool operator != ( const Pt &a, const Pt &b ) { return !(a == b); }

T dot( const Pt &a, const Pt &b )   { return a.x*b.x + a.y*b.y; }
T cross( const Pt &a, const Pt &b ) { return a.x*b.y - a.y*b.x; }

int isLeft(Pt a, Pt b, Pt c) {
    T z = cross(b-a,c-a);
    if (feq(z, 0)) return 0;
    else if (z > 0) return 1;
    else            return -1;
}

// Decide if lines ab and cd are parallel.
// If a=b or c=d, then this will return true.
bool LinesParallel( Pt a, Pt b, Pt c, Pt d ) {
	return feq( cross(b-a,c-d), 0 );
}
// Decide if lines ab and cd are the same line
// If a=b and c=d, then this will return true.
// If a=b xor c=d, (wlog a=b), then this is true iff a is on cd.
bool LinesColinear( Pt a, Pt b, Pt c, Pt d ) {
	return LinesParallel(a,b, c,d)
	    && isLeft(a,b, c) == 0
	    && isLeft(c,d, a) == 0; // to make a=b, c=d cases symmetric
}
// Determine if the segment ab intersects with segment cd
// Use line-line intersection (below) to find it.
// This *will* do the right thing if a=b, c=d, or both!
bool SegmentsIntersect( Pt a, Pt b,   Pt c, Pt d ) {
	if(  LinesColinear(a,b, c,d)  ) {
		if( a==c || a==d || b==c || b==d ) return true;
		if( dot(a-c,b-c) > 0 && dot(a-d,b-d) > 0 && dot(c-b,d-b) > 0 )
			return false;
		return true;
	}
	if( isLeft(a,b, d) * isLeft(a,b, c) > 0 ) return false;
	if( isLeft(c,d, a) * isLeft(c,d, b) > 0 ) return false;
	return true;
}

// Compute the intersection of lines ab and cd.
// ab and cd are assumed to be *NOT* parallel
Pt ComputeLineIntersection( Pt a, Pt b,   Pt c, Pt d ) {
	b=b-a; d=d-c; c=c-a; // translate to a, set b,d to directions
	return a + b*cross(c,d)/cross(b,d); // solve s*b = c + t*d by Cramer
}

#define FOR(v,l,u) for( size_t v = l; v < u; ++v )
typedef vector<Pt> VP;

// These generalize to higher-dimensional polyhedra, provided you represent
// them as a collection of facets
// Just replace "cross" with the suitable determinant, and adjust any scaling
// factors.
T ComputeSignedArea( const VP &p ) {
	T area = 0;
	for( size_t i = 0; i < p.size(); i++ ) {
		size_t z = (i + 1) % p.size();
		area += cross( p[i], p[z] );
	}
	return area / 2.0;
}

T ComputeArea( const VP &p ) {
    return fabs(ComputeSignedArea(p));
}

// Implementation of Sutherland-Hodgman algorithm:
// https://en.wikipedia.org/wiki/Sutherland-Hodgman_algorithm
// Computes the intersection of polygon subject and polygon clip.
// Polygons points must be given in clockwise order. Clip must be convex.
// If intersection is a point, will return that point repeated three times.
// If intersection is a line, will return each endpoint twice.
// If no intersection occurs, will return an empty vector.
// Undefined behavior if intersection consists of multiple polygons.
VP ConvexClipPolygon( const VP &subject, const VP &clip ) {
    VP output = subject;
    for (size_t i = 0; i < clip.size(); ++i) {
        size_t ip1 = (i+1)%clip.size();
        Pt EdgeStart = clip[i];
        Pt EdgeEnd = clip[ip1];
        VP input = output;
        output.clear();
        Pt S = input.back();
        for (size_t j = 0; j < input.size(); ++j) {
            Pt E = input[j];
            if (isLeft(EdgeStart, EdgeEnd, E) <= 0) {
                if (isLeft(EdgeStart, EdgeEnd, S) > 0) {
                    output.push_back(ComputeLineIntersection(EdgeStart, EdgeEnd,  S, E));
                }
                output.push_back(E);
            }
            else if (isLeft(EdgeStart, EdgeEnd, S) <= 0) {
                output.push_back(ComputeLineIntersection(EdgeStart, EdgeEnd,  S, E));
            }
            S = E;
        }
    }
    return output;
}

void print_points(VP &points) {
    if (points.size() > 0) {
        cerr << "(" << points[0].x << " " << points[0].y << ")";
        for (int i = 1; i < points.size(); ++i) {
            cerr << ", (" << points[i].x << " " << points[i].y << ")";
        }
        cerr << endl;
    }
    else {
        cerr << "<empty>" << endl;
    }
}

bool testcase_ConvexClipPolygon(VP subject, VP clip, VP expected) {
    bool success = true;    
    VP result = ConvexClipPolygon(subject, clip);
    if (result.size() != expected.size()) {
        success = false;
    }
    else {
        for (size_t i = 0; i < expected.size(); ++i) {
            if (!feq(result[i].x, expected[i].x) || !feq(result[i].y, expected[i].y)) {
                success = false;
            }
        }
    }
    if (!success) {
        cerr << "ConvexClipPolygon incorrect" << endl;
        cerr << "Expected: ";
        print_points(expected);
        cerr << "Actual: ";
        print_points(result);
        return false;
    }
    return true;
}

void test_ConvexClipPolygon_correct() {
    bool success = true;
    {
        VP subject;
        subject.push_back(Pt(9, 1));
        subject.push_back(Pt(5, -4));
        subject.push_back(Pt(3, -2));
        subject.push_back(Pt(3, 1));
        subject.push_back(Pt(5, 3));

        VP clip;
        clip.push_back(Pt(0, 0));
        clip.push_back(Pt(1, 4));
        clip.push_back(Pt(5, 0));

        VP expected;
        expected.push_back(Pt(5, 0));
        expected.push_back(Pt(3, 0));
        expected.push_back(Pt(3, 1));
        expected.push_back(Pt(3.5, 1.5));

        if (!testcase_ConvexClipPolygon(subject, clip, expected)) {
            success = false;
        }
    }
    {
        VP subject;
        subject.push_back(Pt(0, 0));
        subject.push_back(Pt(0, 2));
        subject.push_back(Pt(2, 0));

        VP clip;
        clip.push_back(Pt(2, 2));
        clip.push_back(Pt(1, 3));
        clip.push_back(Pt(3, 4));
        clip.push_back(Pt(3, 2));

        VP expected;

        if (!testcase_ConvexClipPolygon(subject, clip, expected)) {
            success = false;
        }
    }
    {
        VP subject;
        subject.push_back(Pt(0, 0));
        subject.push_back(Pt(0, 2));
        subject.push_back(Pt(2, 0));

        VP clip;
        clip.push_back(Pt(2, 0));
        clip.push_back(Pt(1, 3));
        clip.push_back(Pt(3, 4));
        clip.push_back(Pt(3, 2));

        VP expected;
        expected.push_back(Pt(2, 0));
        expected.push_back(Pt(2, 0));
        expected.push_back(Pt(2, 0));

        if (!testcase_ConvexClipPolygon(subject, clip, expected)) {
            success = false;
        }
    }
    {
        VP subject;
        subject.push_back(Pt(2, 0));
        subject.push_back(Pt(0, 5));
        subject.push_back(Pt(1, 5));
        subject.push_back(Pt(2.5, 1));
        subject.push_back(Pt(4, 3));
        subject.push_back(Pt(5, 3));
        subject.push_back(Pt(6.5, 1));
        subject.push_back(Pt(8, 5));
        subject.push_back(Pt(9, 5));
        subject.push_back(Pt(7, 0));
        subject.push_back(Pt(6, 0));
        subject.push_back(Pt(4.5, 2));
        subject.push_back(Pt(3, 0));

        VP clip;
        clip.push_back(Pt(0, 2));
        clip.push_back(Pt(1, 4));
        clip.push_back(Pt(4, 5));
        clip.push_back(Pt(9, 1));
        clip.push_back(Pt(4, 0));

        VP expected;
        expected.push_back(Pt(1.5, 1.25));
        expected.push_back(Pt(2.0/3, 10.0/3));
        expected.push_back(Pt(1, 4));
        expected.push_back(Pt(4.0/3, 37.0/9));
        expected.push_back(Pt(2.5, 1));
        expected.push_back(Pt(4, 3));
        expected.push_back(Pt(5, 3));
        expected.push_back(Pt(6.5, 1));
        expected.push_back(Pt(92.0/13, 33.0/13));
        expected.push_back(Pt(257.0/33, 65.0/33));
        expected.push_back(Pt(167.0/23, 15.0/23));
        expected.push_back(Pt(132.0/23, 8.0/23));
        expected.push_back(Pt(4.5, 2));
        expected.push_back(Pt(36.0/11, 4.0/11));

        if (!testcase_ConvexClipPolygon(subject, clip, expected)) {
            success = false;
        }
    }
    {
        VP subject;
        subject.push_back(Pt(0, 0));
        subject.push_back(Pt(0, 3));
        subject.push_back(Pt(3, 3));
        subject.push_back(Pt(3, 0));

        VP clip;
        clip.push_back(Pt(3, 2));
        clip.push_back(Pt(3, 5));
        clip.push_back(Pt(5, 5));
        clip.push_back(Pt(5, 2));

        VP expected;
        expected.push_back(Pt(3, 2));
        expected.push_back(Pt(3, 3));
        expected.push_back(Pt(3, 3));
        expected.push_back(Pt(3, 2));

        if (!testcase_ConvexClipPolygon(subject, clip, expected)) {
            success = false;
        }
    }
    {
        VP subject;
        subject.push_back(Pt(0, 0));
        subject.push_back(Pt(0, 3));
        subject.push_back(Pt(3, 3));
        subject.push_back(Pt(3, 0));

        VP clip;
        clip.push_back(Pt(1, 1));
        clip.push_back(Pt(1, 2));
        clip.push_back(Pt(2, 2));
        clip.push_back(Pt(2, 1));

        VP expected;
        expected.push_back(Pt(2, 1));
        expected.push_back(Pt(1, 1));
        expected.push_back(Pt(1, 2));
        expected.push_back(Pt(2, 2));

        if (!testcase_ConvexClipPolygon(subject, clip, expected)) {
            success = false;
        }
    }

    if (success) {
        cerr << "ConvexClipPolygon correct!" << endl;
    }
}

typedef long long ll;

bool lex_cmp_xy(const Pt &lhs, const Pt &rhs) {
    if (!feq(lhs.x, rhs.x)) return lhs.x < rhs.x;
    if (!feq(lhs.y, rhs.y)) return lhs.y < rhs.y;
    return false;
}


int main() {
    ll n1, n2;
    for (ll cs = 1; cin >> n1 && n1; ++cs) {
        VP one(n1);
        for (ll i = 0; i < n1; ++i) {
            cin >> one[i].x >> one[i].y;
        }

        cin >> n2;
        VP two(n2);
        for (ll i = 0; i < n2; ++i) {
            cin >> two[i].x >> two[i].y;
        }

        double ans = ComputeArea(one) + ComputeArea(two) - 2*ComputeArea(ConvexClipPolygon(one, two));
        printf("%8.2lf", ans);
    }
    cout << endl;

    return 0;
}
