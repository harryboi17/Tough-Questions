/*
for Q query of 2 types
1) Add subtree rooted at X value Y;
2) add a (size+1)th to node V;

find final value of all nodes 
*/
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define loop(i,s,e) for(ll i = s; s<e ? i < e : i >= e; s<e ? i++ : i--)
#define forrr(i,s,e) for(ll i = s; i >= e; i--)
#define forr(i,s,e) for(ll i = s; i < e; i++)
#define vl vector<ll>
#define vvl vector<vl>
#define pll pair<ll, ll>
#define vp vector<pll>
#define mp make_pair
#define ss second
#define ff first
#define pb push_back
#define pf push_front
#define all(a) a.begin(), a.end()
#define Rand(arr, n) generate_n(arr.begin(), n, random)
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" "; _print(x); cerr << endl;
#else
#define debug(x) 
#endif
using namespace std;

template<class T> void _print(T t) {cerr << t;}
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.ff); cerr << ","; _print(p.ss); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(priority_queue<T> pq) {cerr << "[ "; vector<T> v; while(!pq.empty()){ v.push_back(pq.top()); pq.pop();} for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(priority_queue<T, vector<T>, greater<T>> pq) {cerr << "[ "; vector<T> v; while(!pq.empty()){ v.push_back(pq.top()); pq.pop();} for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> st) {cerr << "[ "; for (auto it = st.begin(); it != st.end(); it++) {_print(*it); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> st) {cerr << "[ "; for (auto it = st.begin(); it != st.end(); it++) {_print(*it); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> mp) {cerr << "[ "; for (auto it = mp.begin(); it != mp.end(); it++) {_print(*it); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(multimap <T, V> mp) {cerr << "[ "; for (auto it = mp.begin(); it != mp.end(); it++) {_print(*it); cerr << " ";} cerr << "]";}

template<typename F, typename S> ostream& operator <<(ostream& ostream, pair<F, S>& p) { cout << p.first << " " << p.second<<" "; return ostream; }
template<typename T> ostream& operator <<(ostream& ostream, vector<T>& v) { for(auto& element : v) cout << element << " "; return ostream;}
template<typename T> ostream& operator <<(ostream& ostream, vector<vector<T>>& v) {for(auto& row : v){ for(auto& cell : row) cout << cell << " "; cout << "\n";} return ostream;}
template<typename F, typename S> istream& operator >>(istream& istream, pair<F, S>& p) { cin >> p.first >> p.second; return istream;}
template<typename T> istream& operator >>(istream& istream, vector<T>& v) { for(auto& element : v) cin >> element; return istream; }

//vl prime(1000001);

int random(int s, int e){return s + rand() % (e - s + 1);}
int flip(int n){ forr(i,0,31){ int num = 1<<i; if(num > n) break; n = n xor num;} return n; }
ll power(ll x, ll y){ ll res = 1; while (y > 0){ if (y & 1) res = (ll)(res*x); y = y>>1; x = (ll)(x*x); } return res; }
vp countArr(vl &arr, ll n){ vp v1; forr(i,0,n-1){ ll cnt = 1; while(i < n-1 && arr[i] == arr[i+1]){ cnt++, i++; } v1.pb({arr[i], cnt}); } if((n > 1 && arr[n-1] != arr[n-2]) || n == 1) v1.pb({arr[n-1], 1}); return v1;}
ll gcd(ll a, ll b){if(b == 0) return a; return gcd(b, a%b);}
ll lcm(ll a, ll b){return a*b/gcd(a,b);}
vl factors(ll n){ vl fac; for (ll i = 1; i * i <= n; i++){ if (n % i == 0){ fac.pb(i); if (i * i != n)fac.pb(n / i); } } return fac; }
ll maxPow2(ll n){n |= n >> 1; n |= n >> 2; n |= n >> 4; n |= n >> 8; n |= n >> 16; return (n + 1);}
//vl sieve(){vl primes; for(ll i=0;i<1000001;i++) prime[i]=true; for(ll i=2;i<1000001;i++){ if(!prime[i]) continue; primes.pb(i); for(ll j=2;i*j<1000001;j++) prime[i*j]=false;} return primes;}
vp primeFactors(ll n){ vp v; for (ll j = 2; j <= sqrtl(n); j++){ ll cnt = 0; while(n%j == 0) n /= j, cnt++; if(cnt)v.pb({j,cnt}); } if(n!=1) v.pb({n,1}); return v;}

// ll dx[] = {0, 0, 1, 1, 1, -1, -1, -1};
// ll dy[] = {1, -1, 1, -1, 0, 1, -1, 0};
const int N = 1e6;
ll idx,sz;
ll trees[N*4], Start[N], End[N], lazy[N*4];

void dfs(ll node, vvl &adj){
    Start[node] = idx++;
    for(auto &i : adj[node]) dfs(i, adj);
    End[node] = idx++;
}

void build(ll node, ll st, ll en){ //built in O(2n -1) time
    lazy[node] = 0;
    trees[node] = 0;
    if(st == en) return;
    ll mid = (st+en)/2;
    build(2*node, st, mid);
    build(2*node + 1, mid+1, en);
}

void lazyPropogation(ll &node, ll &st, ll &en){
    if(!lazy[node]) return;
    trees[node] += lazy[node];
    if(st != en){
        lazy[2*node] += lazy[node]; 
        lazy[2*node + 1] += lazy[node]; 
    }
    lazy[node] = 0;
}

ll query(ll node, ll st, ll en, ll &l, ll &r){ //done in log(n) time
    lazyPropogation(node, st, en);
    if(st > r || en < l)
        return 0;
    
    if(l <= st && r >= en) // l... st...en ...r
        return trees[node];
    
    int mid = (st + en)/2;

    ll q1 = query(2*node, st, mid, l, r);
    ll q2 = query(2*node + 1, mid+1, en, l, r);

    return q1 + q2;
}

void update(ll node, ll st, ll en, ll &l, ll &r, ll &val){
    lazyPropogation(node, st, en);
    if(st > r || en < l)
        return;
    
    if(l <= st && r >= en){
        lazy[node] += val;
        return;
    }

    int mid = (st + en)/2;
    update(2*node, st, mid, l, r, val);
    update(2*node + 1, mid+1, en, l, r, val);

    trees[node] = trees[2*node] + trees[2*node + 1];
}

void solve(ll tc){
    ll q; cin>>q;
    vvl qry, adj(q+2);

    sz = 1, idx = 0;
    while(q--){
        ll type,v; cin>>type>>v;
        if(type == 1){
            adj[v].pb(++sz);
            qry.pb({type, sz});
        }
        else{
            ll x; cin>>x;
            qry.pb({type, v, x});
        }
    }

    dfs(1,adj);
    build(1,0,idx-1);

    for(auto &i : qry){
        ll node = i[1], val;
        if(i[0] == 1) val = -query(1,0,idx-1, Start[node], Start[node]);
        else val = i[2];
        update(1,0,idx-1, Start[node], End[node], val);
    }

    forr(i,1,sz+1) cout<<query(1,0,idx-1,Start[i], Start[i])<<" ";
    cout<<endl;   

}

int main(){
fastio(); srand(time(NULL));
ll t; cin>>t;
forr(i,1,t+1) solve(i);
return 0;
}
/* use __lg(number) to get nearest power of 2 -> 8,9,10..15 returns 3, 16-31 returns 4*/