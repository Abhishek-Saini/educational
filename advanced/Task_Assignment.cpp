#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h> 
 
using namespace std;
long long mod = 1e9 + 7;
double EPS = 1e-12;
typedef long long int lld;
typedef pair<lld,lld> PA;
long double tick(){static clock_t oldt; clock_t newt=clock();
    long double diff=1.0L*(newt-oldt)/CLOCKS_PER_SEC; oldt = newt; return diff; }
#define rep(i,a,n) for(long long int i = (a); i <= (n); ++i)
#define repI(i,a,n) for(int i = (a); i <= (n); ++i)
#define repD(i,a,n) for(long long int i = (a); i >= (n); --i)
#define repDI(i,a,n) for(int i = (a); i >= (n); --i)
inline lld sc() { lld a; scanf("%lld", &a); return a; }
inline int scd() { int a; scanf("%d", &a); return a; }
#define prL(a) printf("%lld\n",a)
#define prS(a) printf("%lld ",a)
#define prdL(a) printf("%d\n",a)
#define prdS(a) printf("%d ",a)
#define all(c) (c).begin(), (c).end()
#define sz(a) ((int)a.size())
#ifdef LOCAL_RUN
#define Error(x...) { cout << "(" << #x << ")" << " = ( "; printIt(x); }
#else
#define Error(x...) 42
#endif
template <typename T1> void printIt(T1 t1) { cout << t1 << " )" << endl; }
template <typename T1, typename... T2>
void printIt(T1 t1, T2... t2) { cout << t1 << " , "; printIt(t2...); }
#define popcount __builtin_popcountll

#define lim 300010
#define lim2 200010
// std::ios::sync_with_stdio(false); // Ab :)
typedef int fType;
typedef int cType;
typedef int L;

const fType INF = 0x3f3f3f3f;

struct edge {
    int u, v;
    fType flow;
    cType cost;
    edge() {}
    edge(int u, int v, fType f, cType c) : u(u), v(v), flow(f), cost(c) {}
};

struct MinCostMaxFlow {
    int N;
    vector < vector <int> > G;
    vector <edge> E;
    int numEdges;
    vector <int> found, dad;
    vector <cType> dist;

    MinCostMaxFlow(int N): 
     N(N), G(N), found(N), dist(N), dad(N), numEdges(0) {}
  
    void AddEdge(int from, int to, fType capacity, cType cost) {
        G[from].push_back(numEdges++);
        E.push_back(edge(from, to, capacity, cost));
        G[to].push_back(numEdges++);
        E.push_back(edge(to, from, 0, cType(-1) * cost));
    }
  
    bool spfa(int s, int t) {
        fill(dad.begin(), dad.end(), -1);
        fill(dist.begin(), dist.end(), INF);
        fill(found.begin(), found.end(), 0);
        queue <int> Q;
        dist[s] = 0;
        Q.push(s);
        found[s] = true;
        
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            if(u == t) continue;
            for (int i = 0; i < G[u].size(); ++i) {
                edge &pres = E[G[u][i]];
                int v = pres.v;
                if(pres.flow <= 0) continue;
                if(dist[u] + pres.cost < dist[v]) {
                    dad[v] = G[u][i];
                    dist[v] = dist[u] + pres.cost;
                    if(!found[v]) Q.push(v), found[v] = true;
                }
            }
            found[u] = false;
        }
        return (dad[t] != -1);
    }
 
    fType dfs(int s,int t) {
        fType flow = INF;
        for(int i = dad[t]; i != -1; i = dad[E[i].u]) {
            if(E[i].flow < flow) flow = E[i].flow;
        }
        for(int i = dad[t]; i != -1; i = dad[E[i].u]) {
            E[i].flow -= flow;
            E[i ^ 1].flow += flow;
        }
        return flow;
    }

    pair <fType, cType> GetMaxFlow(int s, int t) {
        fType totflow = 0;
        cType totcost = 0;
        while(spfa(s,t)) {
            fType amt = dfs(s,t);
            totflow += amt;
            totcost += dist[t] * (cType)amt;
        }
        return make_pair(totflow, totcost);
    }
};

/*
count 0 also in total number of nodes
a -> b
AddEdge(a,b,capacity,cost);
flow == 1 means that the edge is used
-- flow is a misnomer here, it's actually capacity
*/

int main(){
    int n = scd();
    int src = 0;
    int person_offset = 0;
    int task_offset = person_offset + n;
    int sink = task_offset + n + 1;
    int total = sink + 1;
    MinCostMaxFlow mcmf(total);
    repI(i, 1, n) mcmf.AddEdge(src, person_offset + i, 1, 0);
    repI(i, 1, n) repI(j, 1, n) {
        int cost = scd();
        mcmf.AddEdge(person_offset + i, task_offset + j, 1, cost);
    }
    repI(i, 1, n) mcmf.AddEdge(task_offset + i, sink, 1, 0);
    pair <fType, cType> ans = mcmf.GetMaxFlow(src, sink);
    assert(ans.first == n);
    prdL(ans.second);
    for(auto edges : mcmf.E) {
        if(edges.flow == 1) continue;
        if(edges.u < person_offset + 1 || edges.u > person_offset + n) continue;
        if(edges.v < task_offset + 1 || edges.v > task_offset + n) continue;
        // cout << edges.cost << " " << edges.flow << " ## ";
        prdS(edges.u - person_offset);
        prdL(edges.v - task_offset);
    }
    return 0;
}