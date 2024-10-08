#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define MAX 30
using namespace std;

struct s {
    int x, y;
};
int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };
int n;
int map[MAX][MAX] = {0, };
int g[MAX][MAX] = {0, };
int t[MAX*MAX][MAX*MAX] = {0, };

void touch() {
    memset(t, 0, sizeof(t));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int from = g[i][j];
            for(int k = 1; k <= 2; k++) {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if(nx < 0 || ny < 0 || nx >= n || ny >= n || g[nx][ny] == from)   continue;
                t[from][g[nx][ny]]++;
            }
        }
    }
}

int score() {
    memset(g, 0, sizeof(g));
    int groupCnt = 1;
    int groupSize[MAX*MAX] = {0, };
    int groupIdx[MAX*MAX] = {0, };
    queue<s> q;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(g[i][j] == 0) { 
                q.push({i, j});
                g[i][j] = groupCnt;
                groupIdx[groupCnt] = map[i][j];
                groupCnt += 1 ;
            }
            while(!q.empty()) {
                int x = q.front().x;
                int y = q.front().y;
                q.pop();
                groupSize[g[x][y]]++;

                for(int k = 0; k < 4; k++) {
                    int nx = x + dx[k];
                    int ny = y + dy[k];
                    if(nx < 0 || ny < 0 || nx >= n || ny >= n || g[nx][ny] != 0)   continue;
                    if(map[nx][ny] != map[x][y])   continue;
                    q.push({nx, ny});
                    g[nx][ny] = g[x][y];
                }
            }
        }
    }
    touch(); // 맞닿아 있는 변의 수
    int total = 0;
    for(int i = 1; i < groupCnt; i++) {
        for(int j = i + 1; j <= groupCnt; j++) {
            total += (groupSize[i] + groupSize[j]) * groupIdx[i] * groupIdx[j] * (t[i][j] + t[j][i]);
        }
    }
    return total;
}

void rotate(int x, int y) {
    int len = (n - 1) / 2;
    int tmp[MAX][MAX] = {0, };
    
    for(int i = 0; i < len; i++) {
        for(int j = 0; j < len; j++) {
            tmp[j][len - 1 - i] = map[x + i][y + j];
        }
    }
    for(int i = 0; i < len; i++) {
        for(int j = 0; j < len; j++) {
            map[x + i][y + j] = tmp[i][j];
        }
    }
}

void rotate() {
    int len = (n - 1) / 2 + 1;
    rotate(0, 0);
    rotate(0, len);
    rotate(len, 0);
    rotate(len, len);
    int tmp[MAX] = {0, };
    len -= 1;
    
    for(int i = 0; i < len; i++)  tmp[i] = map[i][len];
    for(int i = 0; i < len; i++)  map[i][len] = map[len][n-1-i];
    for(int i = 0; i < len; i++)  map[len][n-1-i] = map[n-1-i][len];
    for(int i = 0; i < len; i++)  map[n-1-i][len] = map[len][i];
    for(int i = 0; i < len; i++)  map[len][i] = tmp[i];

}

int main(void) {
    ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
        cin >> map[i][j];
    }
    int total = 0;
    total += score();
    for(int i = 0; i < 3; i++) {
        rotate();
        total += score();
    }
    cout << total;
    return 0;
}