#include <iostream>
#include <vector>
#define MAX 100
using namespace std;

struct s {
    int x, y, dir;
};
s person;
bool tree[MAX][MAX] = {0, };
vector<int> map[MAX][MAX];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int n, m, h, k, len, cnt;
int cur = 1;
bool turn = false;

void run() {
    vector<int> tmpMap[MAX][MAX];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < map[i][j].size(); k++) {
                int d = map[i][j][k];
                int dis = abs(i - person.x) + abs(j - person.y);
                if(dis > 3) { 
                    tmpMap[i][j].push_back(map[i][j][k]);
                    continue;
                }
                int nx = i + dx[d];
                int ny = j + dy[d];
                if(nx < 0 || nx >= n || ny < 0 || ny >= n) {
                    if(d < 2)
                        d += 2;
                    else
                        d -= 2;
                    nx = i + dx[d];
                    ny = j + dy[d];
                }
                if (nx == person.x && ny == person.y) {
                    nx = nx - dx[d];
                    ny = ny - dy[d];
                }
                tmpMap[nx][ny].push_back(d);
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            map[i][j].clear();
            map[i][j] = tmpMap[i][j];
        }
    }
}

int hold() {
    int x = person.x;
    int y = person.y;
    int dir = person.dir;
    int cnt = 0;
    for(int i = 0; i < 3; i++) {
        int nx = x + dx[dir] * i;
        int ny = y + dy[dir] * i;
        if(tree[nx][ny]) continue;
        if(nx < 0 || nx >= n || ny < 0 || ny >= n) break;
        if(map[nx][ny].size() > 0) {
            cnt += map[nx][ny].size();
            map[nx][ny].clear();
        }
    }
    return cnt;
}

void move() {
    int x = person.x;
    int y = person.y;
    int dir = person.dir;
    int nx = x + dx[dir];
    int ny = y + dy[dir];
    len++;
    if(len == cur) {
        len = 0;
        cnt++;
        if(turn == false) {
            if(dir == 3)
                dir = 0;
            else
                dir++;
        } else {
            if(dir == 0) 
                dir = 3;
            else
                dir--;
        }
        if(cnt == 2) {
            cnt = 0;
            if(!turn) 
                cur++;
            else
                cur--;
        }
    }
    if(nx == 0 && ny == 0) {
        turn = true;
        cur = n - 1;
        dir = 2;
        cnt = -1;
        len = 0;
    } else if(nx == (n - 1) / 2 && ny == (n - 1) / 2) {
        turn = false;
        cur = 1;
        dir = 0;
        cnt = 0;
        len = 0;
    }
    person = {nx, ny, dir};
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
    cnt = 0;
    len = 0;
    cin >> n >> m >> h >> k;
    person = {(n - 1) / 2, (n - 1) / 2, 0};
    for(int i = 0; i < m; i++) {
        int x, y, d;
        cin >> x >> y >> d;
        if(d == 1)
            d = 1;
        else 
            d = 2;
        map[x - 1][y - 1].push_back(d);
    }
    for(int i = 0; i < h; i++) {
        int x, y;
        cin >> x >> y;
        tree[x - 1][y - 1] = 1;
    }
    int score = 0;
    for(int i = 1; i <= k; i++) {
        run();
        move();
        score += i * hold();
    }
    cout << score;
    return 0;
}