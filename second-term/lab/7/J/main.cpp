#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXT = 1e6 * 8 + 1234;
const int INF = 1e9 + 123;
const int NN = 2e6 + 123;
int t[MAXT];
int p[MAXT];
int pl[MAXT];
int tj[MAXT];

bool check(int v) {
    return v < MAXT;
}

void push(int v) {
    int vv = 2 * v + 1;
    int pv = p[v];
    int plv = pl[v];
    if (check(vv)) {
        if (p[v] != INF) {
            p[vv] = p[v];
            pl[vv] = 0;
            // p[v] = INF;
            t[vv] = p[v];
            pv = INF;
        } else {
            // pl[vv] += pl[v];
            if (p[vv] != INF) {
                p[vv] += pl[v];
            } else {
                pl[vv] += pl[v];
            }
            // pl[v] = 0;
            t[vv] += pl[v];
            plv = 0;
        }
    }
    vv = 2 * v + 2;
    if (check(vv)) {
        if (p[v] != INF) {
            p[vv] = p[v];
            pl[vv] = 0;
            // p[v] = INF;
            t[vv] = p[v];
            pv = INF;
        } else {
            // pl[vv] += pl[v];
            if (p[vv] != INF) {
                p[vv] += pl[v];
            } else {
                pl[vv] += pl[v];
            }
            // pl[v] = 0;
            t[vv] += pl[v];
            plv = 0;
        }
    }
    p[v] = pv;
    pl[v] = plv;
}

pair<int, int> get_max(int v, int tl, int tr, int l, int r) {
    if (l > r) { return {-INF, -INF}; }
    if (tl == l && tr == r) {
        return {t[v], tj[v]};
    } else {
        push(v);
        int tm = (tl + tr) / 2;
        pair<int, int> ans = get_max(2 * v + 1, tl, tm, l, min(tm, r));
        pair<int, int> ans1 = get_max(2 * v + 2, tm + 1, tr, max(l, tm + 1), r);
        if (ans1.first == ans.first) {
        	tj[v] = min(ans1.second, ans.second);
        	return {ans.first, min(ans1.second, ans.second)};
        } else {
        	if (ans1.first > ans.first) {
        		tj[v] = ans1.second;
        		return ans1;
        	} else {
        		tj[v] = ans.second;
        		return ans;
        	}
        }
        return ans;
    }
}

void add(int v, int tl, int tr, int l, int r, int x) {
    if (l > r) { return; }
    if (tl == l && tr == r) {
        t[v] += x;
        if (p[v] != INF) {
            p[v] += x;
        } else {
            pl[v] += x;
        }
    } else {
        push(v);
        int tm = (tl + tr) / 2;
        add(2 * v + 1, tl, tm, l, min(tm, r), x);
        add(2 * v + 2, tm + 1, tr, max(l, tm + 1), r, x);
        t[v] = max(t[2 * v + 1], t[2 * v + 2]);
        if (t[v] == t[2 * v + 1]) {
        	tj[v] = tj[2 * v + 1];
        } else {
        	tj[v] = tj[2 * v + 2];
        }
    }
}

struct rect {
    int x1, y1, x2, y2, id;
    rect() {}
    rect(int xx1, int yy1, int xx2, int yy2, int idd) {
        x1 = xx1;
        y1 = yy1;
        x2 = xx2;
        y2 = yy2;
        id = idd;
    }
};

struct event {
    int x, rectid, type, y;
    event(int xx, int rectidd, int typee, int yy) {
        x = xx;
        rectid = rectidd;
        type = typee;
        y = yy;
    }
    bool operator < (const event& other) {
        return (x < other.x || (x == other.x && type < other.type));
    }
};

istream& operator>>(istream& is, rect& a) {
    is >> a.x1 >> a.y1 >> a.x2 >> a.y2;
    return is;
}

void build(int v, int l, int r) {
	if (l == r) {
		t[v] = 0;
		tj[v] = l;
	} else {
		int m = (l + r) / 2;
		build(2 * v + 1, l, m);
		build(2 * v + 2, m + 1, r);
		tj[v] = tj[2 * v + 1];
	}
}

vector <event> events;
vector <rect> rects;

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    for (int v = 0; v < MAXT; v++) {
        p[v] = INF;
        pl[v] = 0;
    }
    build(0, 0, NN - 1);
    int n;
    cin >> n;
    rects.resize(n);
    int maxxx = -1;
    for (int i = 0; i < n; i++) {
        cin >> rects[i];
        rects[i].x1 += (int) 1e6;
        rects[i].y1 += (int) 1e6;
        rects[i].x2 += (int) 1e6;
        rects[i].y2 += (int) 1e6;
        events.push_back(event(rects[i].x1, i, -1, rects[i].y1));
        events.push_back(event(rects[i].x2, i, 1, rects[i].y2));
        maxxx = max(maxxx, max(rects[i].x1, rects[i].x2));
    }
    sort(events.begin(), events.end());
    int res = 0;
    pair <int, int> ans;
    for (int i = 0; i < int(events.size()); i++) {
        event cur = events[i];
        int id = cur.rectid;
        int y2 = rects[id].y2, y1 = rects[id].y1;
        if (cur.type == -1) {
            add(0, 0, NN - 1, y1, y2, 1);
            // cout << get_max(0, 0, NN - 1, y1, y2) << "\n";
        } else {
            pair<int, int> mx = get_max(0, 0, NN - 1, y1, y2);
            res = max(res, mx.first);
            if (mx.first == res) {
                ans = {events[i].x, mx.second};
            }
            add(0, 0, NN - 1, y1, y2, -1);
        }
    }
    cout << res << "\n" << ans.first - 1e6 << ' ' << ans.second - 1e6;
    return 0;
}
