#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

typedef long long LL;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<vvb> vvvb;
typedef vector<char> vc;
typedef vector<vc> vvc;

int moves[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
char bad[5] = {'<', '^', '>', 'v', '#'};

struct st
{
    LL r, c;
    LL moves;

    st() {}

    st(LL r, LL c, LL moves) : r(r), c(c), moves(moves) {}
};

int main()
{
    LL T;

    cin >> T;

    for (size_t caseNum = 1; caseNum <= T; ++caseNum)
    {
        LL M, N;
        cin >> M >> N;

        vvc board(M, vc(N));
        st start;
        for (size_t i = 0; i < M; ++i)
        {
            for (size_t j = 0; j < N; ++j)
            {
                cin >> board[i][j];
                if (board[i][j] == 'S')
                    start = st(i, j, 0);
            }
        }

        queue<st> open;
        open.push(start);

        vvvb closed(M, vvb(N, vb(4, false)));

        LL totalMoves = -1;
        
        bool first = true;
        while (!open.empty())
        {
            st cur = open.front();
            open.pop();

            if (cur.r < 0 || cur.r >= M || cur.c < 0 || cur.c >= N)
                continue;

            bool free = true;
            for (size_t i = 0; i < 5; ++i)
                if (board[cur.r][cur.c] == bad[i])
                {
                    free = false;
                    break;
                }

            if (!free)
                continue;

            if (closed[cur.r][cur.c][cur.moves%4])
                continue;

            closed[cur.r][cur.c][cur.moves%4] = true;

            bool laser = false;
            for (size_t o = 0; o < 4; ++o)
            {
                for (LL rn = cur.r, cn = cur.c; true; rn += moves[o][0], cn += moves[o][1])
                {
                    if (rn < 0 || rn >= M || cn < 0 || cn >= N)
                        break;

                    if (board[rn][cn] == '#')
                        break;

                    bool blocked = false;
                    for (size_t i = 0; i < 4; ++i)
                    {
                        if (board[rn][cn] == bad[i])
                        {
                            if (o == (i+cur.moves)%4)
                            {
                                laser = true;
                            }

                            blocked = true;
                            break;
                        }
                    }

                    if (blocked)
                        break;
                }
            }

            if (laser && !first)
                continue;

            first = false;

            if (board[cur.r][cur.c] == 'G')
            {
                totalMoves = cur.moves;
                break;
            }

            for (size_t o = 0; o < 4; ++o)
            {
                open.push(st(cur.r + moves[o][0], cur.c + moves[o][1], cur.moves+1));
            }
        }

        if (totalMoves == -1)
            printf("Case #%lu: impossible\n", caseNum);
        else
            printf("Case #%lu: %lld\n", caseNum, totalMoves);
    }
}
