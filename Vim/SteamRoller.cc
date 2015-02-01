#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define INF 1000000000000000LL

typedef long long ll;
typedef pair<ll, ll> ii;
typedef pair<ll, ii> iii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<vvvi> vvvvi;

ll R, C, r1, c1, r2, c2;

ll dr[] = {0, 1, 0, -1};
ll dc[] = {1, 0, -1, 0};

void readHRow(vvi &row) {
    for (ll i = 0; i < C-1; ++i) {
        ll cost;
        cin >> cost;

        if (cost == 0)
            cost = INF;

        row[i][0] = cost;
        row[i+1][2] = cost;
    }
}

void readVRow(vvi &upRow, vvi &lowRow) {
    for (ll i = 0; i < C; ++i) {
        ll cost;
        cin >> cost;

        if (cost == 0)
            cost = INF;

        upRow[i][1] = cost;
        lowRow[i][3] = cost;
    }
}

int main() {
    for (ll caseNum = 1; true; ++caseNum) {
        cin >> R >> C >> r1 >> c1 >> r2 >> c2;

        if (R == 0 && C == 0 && r1 == 0 && c1 == 0 && r2 == 0 && c2 == 0)
            break;

        --r1;
        --c1;
        --r2;
        --c2;

        vvvi cost(R, vvi(C, vi(4, INF)));
        readHRow(cost[0]);
        for (ll i = 0; i < R-1; ++i) {
            readVRow(cost[i], cost[i+1]);
            readHRow(cost[i+1]);
        }
        
        vvvvi adjMatrix(R, vvvi(C, vvi(4, vi(max(R, C), INF))));
        for (ll r = 0; r < R; ++r) {
            for (ll c = 0; c < C; ++c) {
                for (ll d = 0; d < 4; ++d) {
                    ll sum = cost[r][c][d]*2;
                    adjMatrix[r][c][d][1] = sum;
                    for (ll k = 2; true; ++k) {
                        ll rn = r + dr[d]*k;
                        ll cn = c + dc[d]*k;

                        if (rn < 0 || rn >= R || cn < 0 || cn >= C)
                            break;

                        adjMatrix[r][c][d][k] = sum + cost[rn][cn][(d+2)%4]*2;
                        sum += cost[rn][cn][(d+2)%4];
                    }
                }
            }
        }

        vvi dist(R, vi(C, INF));
        priority_queue<iii, vector<iii>, greater<iii> > pq; //(dist, (r, c))

        pq.push(iii(0, ii(r1, c1)));

        while (!pq.empty()) {
            iii cur = pq.top(); pq.pop();
            ll curDist = cur.first;
            ll r = cur.second.first;
            ll c = cur.second.second;

            //cerr << r << " " << c << " " << curDist << endl;

            if (curDist >= dist[r][c]) continue;

            dist[r][c] = curDist;

            for (ll d = 0; d < 4; ++d) {
                for (ll k = 1; k < max(R, C); ++k) {
                    if (adjMatrix[r][c][d][k] >= INF)
                        break;

                    pq.push(iii(curDist + adjMatrix[r][c][d][k], ii(r+dr[d]*k, c+dc[d]*k)));
                }
            }
        }
        
        if (dist[r2][c2] == INF)
            printf("Case %lld: Impossible\n", caseNum);
        else
            printf("Case %lld: %lld\n", caseNum, dist[r2][c2]);
    }

    return 0;
}
