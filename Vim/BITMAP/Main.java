import java.util.*;

public class Main {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        int t = in.nextInt();

        for (int cs = 1; cs <= t; ++cs) {
            int n, m;
            n = in.nextInt();
            m = in.nextInt();

            ArrayList<String> board = new ArrayList<String>();
            for (int i = 0; i < n; ++i) {
                board.add(in.next());
            }

            int[][] dist = new int[n][m];
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    dist[i][j] = board.get(i).charAt(j) == '1' ? 0 : 100000000;
                }
            }
    
            ArrayDeque<int[]> q = new ArrayDeque<int[]>();
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (dist[i][j] == 0) {
                        q.add(new int[]{i, j});
                    }
                }
            }

            int[] dr = new int[]{0, 1, 0, -1};
            int[] dc = new int[]{1, 0, -1, 0};

            while (!q.isEmpty()) {
                int[] cur = q.poll();

                for (int i = 0; i < 4; ++i) {
                    int new_r = dr[i] + cur[0];
                    int new_c = dc[i] + cur[1];

                    if (new_r >= 0 && new_r < n && new_c >= 0 && new_c < m) {
                        if (dist[new_r][new_c] > dist[cur[0]][cur[1]]+1) {
                            dist[new_r][new_c] = dist[cur[0]][cur[1]]+1;
                            q.add(new int[]{new_r, new_c});
                        }
                    }
                }
            }

            for (int i = 0; i < n; ++i) {
                System.out.print(dist[i][0]);
                for (int j = 1; j < m; ++j) {
                    System.out.print(" " + dist[i][j]);
                }
                System.out.println();
            }
        }
    }
}
