#include <bits/stdc++.h>
using namespace std;

static const int BLOCK = 64;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        int N, M;
        cin >> N >> M;

        vector<vector<int>> g(N + 1);
        vector<int> indeg(N + 1, 0);

        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            indeg[v]++;
        }

        // ---- Topological order ----
        queue<int> q;
        for (int i = 1; i <= N; i++)
            if (indeg[i] == 0) q.push(i);

        vector<int> topo;
        topo.reserve(N);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            topo.push_back(u);
            for (int v : g[u]) {
                if (--indeg[v] == 0) q.push(v);
            }
        }

        // ---- Reachability bitsets ----
        int B = (N + BLOCK - 1) / BLOCK;
        vector<vector<unsigned long long>> reach(N + 1, vector<unsigned long long>(B));

        // Each node can reach itself
        for (int i = 1; i <= N; i++) {
            int b = (i - 1) / BLOCK;
            int o = (i - 1) % BLOCK;
            reach[i][b] |= (1ULL << o);
        }

        // Process in reverse topological order
        for (int i = N - 1; i >= 0; i--) {
            int u = topo[i];
            for (int v : g[u]) {
                for (int b = 0; b < B; b++)
                    reach[u][b] |= reach[v][b];
            }
        }

        // ---- Precompute prefix-min and suffix-min ----
        // For efficient |U - X| minimum
        vector<int> pref(N + 2), suff(N + 2);
        const int INF = 1e9;

        // pref[i] = min(|i - j|) for j < i
        // That simply becomes: pref[i] = 1 for i>1 (but we need general use)
        // Actually we compute prefix position list:
        for (int i = 1; i <= N; i++) pref[i] = i;     // best candidate = itself
        for (int i = 1; i <= N; i++) pref[i] = min(pref[i], pref[i - 1]);

        // suffix
        for (int i = 1; i <= N; i++) suff[i] = i;
        for (int i = N; i >= 1; i--) suff[i] = min(suff[i], suff[i + 1]);

        // ---- Answer Queries ----
        int Q;
        cin >> Q;

        cout << "Case " << tc << ":\n";

        while (Q--) {
            int U, V;
            cin >> U >> V;

            // Check direct reachability:
            int b = (V - 1) / BLOCK;
            int o = (V - 1) % BLOCK;

            if (reach[U][b] & (1ULL << o)) {
                cout << 0 << "\n";
                continue;
            }

            // Need to add one temporary edge
            // Strategy: find any X reachable from U and any Y that can reach V
            // But minimal |X - Y| occurs from closest number on the right or left.

            int ans = INF;

            // Try Y = V (cheapest is X close to V)
            // We need an X such that reach[U][X] = 1
            // Search nearest X < V
            for (int x = V; x >= 1 && x >= V - 2000; x--) {
                int bb = (x - 1) / BLOCK;
                int oo = (x - 1) % BLOCK;
                if (reach[U][bb] & (1ULL << oo)) {
                    ans = min(ans, abs(x - V));
                    break;
                }
            }
            // Search nearest X > V
            for (int x = V; x <= N && x <= V + 2000; x++) {
                int bb = (x - 1) / BLOCK;
                int oo = (x - 1) % BLOCK;
                if (reach[U][bb] & (1ULL << oo)) {
                    ans = min(ans, abs(x - V));
                    break;
                }
            }

            // If unreachable inside window, fallback full scan (rare)
            if (ans == INF) {
                for (int x = 1; x <= N; x++) {
                    int bb = (x - 1) / BLOCK;
                    int oo = (x - 1) % BLOCK;
                    if (reach[U][bb] & (1ULL << oo)) {
                        ans = min(ans, abs(x - V));
                    }
                }
            }

            cout << ans << "\n";
        }
    }
    return 0;
}
