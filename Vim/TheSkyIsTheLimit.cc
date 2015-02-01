#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

#define EP 1e-8
#define INF 1000000000000000000LL

using namespace std;

typedef long long ll;
typedef vector<double> vd;
typedef pair<double, double> dd;
typedef vector<dd> vdd;

dd minusPt(dd a, dd b) {
    return dd(a.first - b.first, a.second - b.second);
}

double cross(dd a, dd b) { return a.first*b.second - a.second*b.first; }

ll isLeft(dd a, dd b, dd c) {
    double z = cross(minusPt(b, a), minusPt(c, a));
    if (abs(z) < EP) return 0;
    else if (z > 0) return 1;
    else return -1;
}

bool between(double a, double b, double c) {
    return c >= min(a, b)-EP && c <= max(a, b)+EP;
}

bool betweenPt(dd a, dd b, dd c) {
    return between(a.first, b.first, c.first) 
        && between(a.second, b.second, c.second);
}

bool SegmentsIntersect(dd a, dd b,  dd c, dd d) {
    ll one = isLeft(a, b, c);
    ll two = isLeft(a, b, d);
    ll three = isLeft(c, d, a);
    ll four = isLeft(c, d, b);

    if (one * two > 0 || three * four > 0) return false;
    if (one == 0 && two == 0 && three == 0 && four == 0) {
        return betweenPt(a, b, c) || betweenPt(a, b, d);
    }

    return true;
}

dd ComputeLineIntersection(dd a, dd b,  dd c, dd d) {
    b = minusPt(b, a); d = minusPt(d, c); c = minusPt(c, a);
    double scalar = cross(c,d)/cross(b,d);
    return dd(a.first + b.first*scalar, a.second + b.second*scalar);
}

bool LinesParallel(dd a, dd b, dd c, dd d) {
    return abs(cross(minusPt(b, a), minusPt(c, d))) < EP;
}

double dist(dd a, dd b) {
    return sqrt(pow(a.first-b.first, 2) + pow(a.second-b.second, 2));
}

void addSeg(vdd &leftEnd, vdd &rightEnd, vd &slope, dd curLeft, dd curRight, double curSlope) {
    bool add = true;
    for (ll i = 0; i < leftEnd.size(); ++i) {
        if (SegmentsIntersect(curLeft, curRight, leftEnd[i], rightEnd[i])) {
            if (LinesParallel(curLeft, curRight, leftEnd[i], rightEnd[i])) {
                if (curSlope > 0 ? (curRight.first > rightEnd[i].first) : (curLeft.first < leftEnd[i].first)) {
                    leftEnd.erase(leftEnd.begin()+i);
                    rightEnd.erase(rightEnd.begin()+i);
                    slope.erase(slope.begin()+i);
                }
                else {
                    add = false;
                }
            }
        }
    }

    if (add) {
        leftEnd.push_back(curLeft);
        rightEnd.push_back(curRight);
        slope.push_back(curSlope);
    }
}

ll findMin(vdd &leftEnd, vd &slope, double minVal) {
    ll minIdx = -1;
    for (ll i = 0; i < leftEnd.size(); ++i) {
        if (leftEnd[i].first > minVal+EP) {
            if (minIdx == -1 || (leftEnd[i].first < leftEnd[minIdx].first-EP))
                minIdx = i;
            if (minIdx == -1 || (abs(leftEnd[i].first - leftEnd[minIdx].first) < EP && slope[i] > slope[minIdx]))
                minIdx = i;
        }
    }

    return minIdx;
}

int main() {
    for (ll caseNum = 1; true; ++caseNum) {
        ll N;
        cin >> N;

        if (N == 0)
            break;

        vdd leftEnd;
        vdd rightEnd;
        vd slope;
        for (ll i = 0; i < N; ++i) {
            double X, H, B;
            cin >> X >> H >> B;

            addSeg(leftEnd, rightEnd, slope, dd(X-B/2, 0), dd(X, H), H/(B/2));
            addSeg(leftEnd, rightEnd, slope, dd(X, H), dd(X+B/2, 0), -H/(B/2));
        }

        ll minIdx = findMin(leftEnd, slope, -INF);

        double total = 0;
        ll cur = minIdx;
        dd curPt = leftEnd[minIdx];
        while (true) {
            //cerr << curPt.first << " " << curPt.second << " " << total << endl;
            ll next = -1;
            dd nextIpt;
            for (ll i = 0; i < leftEnd.size(); ++i) {
                if (i == cur) continue;
                
                if (SegmentsIntersect(leftEnd[cur], rightEnd[cur], leftEnd[i], rightEnd[i])) {
                    dd iPt = ComputeLineIntersection(leftEnd[cur], rightEnd[cur], leftEnd[i], rightEnd[i]);

                    // slope is less than current and intersection point is not right end of current
                    if (slope[i] < slope[cur] && abs(iPt.first - rightEnd[cur].first) > EP) continue;

                    // a different next candidate has been found, this candidate has same intersection point but less slope
                    if (next != -1 && abs(iPt.first - nextIpt.first) < EP && slope[i] < slope[next]) continue;
                    
                    // a different next candidate has been found, this candidate has larger x coordinate intersection point
                    if (next != -1 && iPt.first > nextIpt.first-EP) continue;

                    // this intersection point is less than the current point
                    if (iPt.first < curPt.first + EP) continue;

                    // this intersection adds no new segments
                    if (abs(iPt.first - rightEnd[i].first) < EP) continue;

                    next = i;
                    nextIpt = iPt;
                }
            }

            if (next == -1) {
                total += dist(curPt, rightEnd[cur]);

                cur = findMin(leftEnd, slope, rightEnd[cur].first);
                if (cur == -1)
                    break;

                curPt = leftEnd[cur];
            }
            else {
                total += dist(curPt, nextIpt);
                cur = next;
                curPt = nextIpt;
            }
        }

        printf("Case %lld: %lld\n\n", caseNum, (ll)(round(total+EP)+EP));
    }

    return 0;
}
