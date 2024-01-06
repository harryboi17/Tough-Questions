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
#define ss second
#define ff first
#define pb push_back
#define pf push_front
#define all(a) a.begin(), a.end()
#define Rand(arr, n) generate_n(arr.begin(), n, random)
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define testt ll t = 1; cin>>t; while(t--)
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
ll gcd(ll a, ll b){if(b == 0) return a; return gcd(b, a%b);};
vl factors(ll n){ vl fac; for (ll i = 1; i * i <= n; i++){ if (n % i == 0){ fac.pb(i); if (i * i != n)fac.pb(n / i); } } return fac; }
ll maxPow2(ll n){n |= n >> 1; n |= n >> 2; n |= n >> 4; n |= n >> 8; n |= n >> 16; return (n + 1);}
//vl sieve(){vl primes; for(ll i=0;i<1000001;i++) prime[i]=true; for(ll i=2;i<1000001;i++){ if(!prime[i]) continue; primes.pb(i); for(ll j=2;i*j<1000001;j++) prime[i*j]=false;} return primes;}
vp primeFactors(ll n){ vp v; for (ll j = 2; j <= sqrtl(n); j++){ ll cnt = 0; while(n%j == 0) n /= j, cnt++; if(cnt)v.pb({j,cnt}); } if(n!=1) v.pb({n,1}); return v;}


/*
given q query
l r x - make arr[i] -> max(arr[i]-x, 0);
return number of 0 in array, after each query;
*/

const int N = 1e5 + 2;
struct Trees{
    vector<int> arr;
    int lazy = 0, change = 0;
};
Trees trees[4*N];

void init(int n){
    forr(i,0,4*n){
        trees[i].arr.clear();
        trees[i].lazy = 0;
        trees[i].change = 0;
    }
}

void build(int node, int st, int en, vl &arr){ //built in O(2n -1) time
    if(st == en){
        trees[node].arr.pb(arr[st]);
        return;
    }

    int mid = (st+en)/2;
    build(2*node, st, mid, arr);
    build(2*node + 1, mid+1, en, arr);

	merge(all(trees[2*node].arr), all(trees[2*node+1].arr), back_inserter(trees[node].arr));
}

void lazyUpdate(int node, int st, int en){
    if(!trees[node].lazy) return;
    trees[node].change += trees[node].lazy;

    if(st != en){
        trees[2*node].lazy += trees[node].lazy;
        trees[2*node+1].lazy += trees[node].lazy;
    }
    trees[node].lazy = 0;
}

ll query(int node, int st, int en, int l, int r){ //done in log(n) time
    lazyUpdate(node, st, en);
    if(st > r || en < l) return 0;
    
    if(l <= st && r >= en)
        return upper_bound(all(trees[node].arr), trees[node].change) - trees[node].arr.begin();
    
    int mid = (st + en)/2;

    ll q1 = query(2*node, st, mid, l, r);
    ll q2 = query(2*node + 1, mid+1, en, l, r);

    return q1 + q2;
}

ll update(int node, int st, int en, int l, int r, int val){ //done in log(n) time
    lazyUpdate(node, st, en);
    if(st > r || en < l) return 0;
    
    if(l <= st && r >= en){
        ll prev = upper_bound(all(trees[node].arr), trees[node].change) - trees[node].arr.begin();
        trees[node].lazy += val;
        lazyUpdate(node, st, en);
        ll curr = upper_bound(all(trees[node].arr), trees[node].change) - trees[node].arr.begin();
        return curr - prev;
    }
    
    int mid = (st + en)/2;

    ll u1 = update(2*node, st, mid, l, r, val);
    ll u2 = update(2*node + 1, mid+1, en, l, r, val);
    return u1 + u2;
}

void solve(){
    ll n; cin>>n;
    vl arr(n); cin>>arr;

    init(n+1);
    build(1,0,n-1,arr);

    ll q; cin>>q;
    ll ans = 0;
    while(q--){
        ll l,r,x; cin>>l>>r>>x; l--,r--;
        ans += update(1,0,n-1,l,r,x);
        cout<<ans<<" ";
    }
    cout<<endl;
}

int main(){
fastio(); srand(time(NULL));
testt{ solve(); }
return 0;
}
/* use __lg(number) to get nearest power of 2 -> 8,9,10..15 returns 3, 16-31 returns 4*/