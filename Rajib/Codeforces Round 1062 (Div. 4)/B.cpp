

#include <bits/stdc++.h>
using namespace std;

// -------------------- FAST I/O --------------------
#define FAST_IO ios::sync_with_stdio(false); cin.tie(nullptr);

// -------------------- MACROS ----------------------
#define ll long long
#define ld long double
#define endl '\n'
#define pb push_back
#define ff first
#define ss second
#define all(v) (v).begin(), (v).end()
#define sz(v) ((int)(v).size())
#define rep(i,a,b) for(int i=(a); i<(b); ++i)
#define rrep(i,a,b) for(int i=(a); i>=(b); --i)

// -------------------- CONSTANTS -------------------
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;
const double EPS = 1e-9;

// -------------------- TYPE ALIASES ----------------
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi = vector<int>;
using vll = vector<ll>;

// -------------------- UTILS -----------------------
ll modpow(ll a, ll b, ll m=MOD){ ll r=1; while(b){ if(b&1) r=r*a%m; a=a*a%m; b>>=1; } return r; }
ll modinv(ll a, ll m=MOD){ return modpow(a, m-2, m); }
ll gcdll(ll a, ll b){ return b? gcdll(b, a%b): a; }

// -------------------- DSU / UNION-FIND ------------
struct DSU {
    vector<int> p, sz;
    DSU(int n){ p.resize(n+1); iota(all(p),0); sz.assign(n+1,1); }
    int find(int v){ return v==p[v]? v: p[v]=find(p[v]); }
    bool unite(int a,int b){
        a=find(a), b=find(b);
        if(a==b) return false;
        if(sz[a]<sz[b]) swap(a,b);
        p[b]=a; sz[a]+=sz[b];
        return true;
    }
};

// -------------------- GRAPH TEMPLATE --------------
struct Graph {
    int n;
    vector<vector<pair<int,int>>> adj;
    Graph(int n):n(n){ adj.assign(n+1,{}); }
    void addEdge(int u,int v,int w=1,bool undirected=true){
        adj[u].push_back({v,w});
        if(undirected) adj[v].push_back({u,w});
    }
    vector<int> bfs(int src){
        vector<int> dist(n+1,INF); queue<int>q;
        dist[src]=0; q.push(src);
        while(!q.empty()){
            int u=q.front(); q.pop();
            for(auto [v,w]:adj[u]) if(dist[v]>dist[u]+1){
                dist[v]=dist[u]+1; q.push(v);
            }
        }
        return dist;
    }
    vector<ll> dijkstra(int src){
        vector<ll> dist(n+1,LINF);
        priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<>> pq;
        dist[src]=0; pq.push({0,src});
        while(!pq.empty()){
            auto [d,u]=pq.top(); pq.pop();
            if(d!=dist[u]) continue;
            for(auto [v,w]:adj[u]) if(dist[v]>d+w){
                dist[v]=d+w; pq.push({dist[v],v});
            }
        }
        return dist;
    }
};

// -------------------- GEOMETRY HELPERS ------------
struct Point{ double x,y; };
double dist(Point a,Point b){ return hypot(a.x-b.x,a.y-b.y); }
double cross(Point a,Point b){ return a.x*b.y - a.y*b.x; }
double orient(Point a,Point b,Point c){
    double val = cross({b.x-a.x,b.y-a.y},{c.x-a.x,c.y-a.y});
    if(fabs(val)<EPS) return 0;
    return (val>0)?1:-1;
}

// -------------------- SOLVE FUNCTION --------------
void solve(){

    int n;
    string a, b;
    cin >> n >> a >> b;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    if( a == b) cout << "YES" << endl;
    else cout << "NO" << endl;


}



// -------------------- MAIN ------------------------
int main(){
    FAST_IO;
    int t=1;
    cin>>t; // Uncomment for multiple test cases
    while(t--) solve();
    return 0;
}
