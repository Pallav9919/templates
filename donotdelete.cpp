#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll power(ll x,ll y,ll m){if(y==0)return 1;ll p=power(x,y/2,m)%m;p=(p*p)%m;return (y%2==0)?p:(x*p)%m;}
// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());int get_rand(int l, int r){uniform_int_distribution<int> uid(l,r);return uid(rng);}
vector<ll> Fac(1,1),Mod_Inv(1,1);int Last_Index = 0;
ll nCr(ll n,ll r,ll m){if(n<0 || r<0) return 0;if(r>n) return 0;if(n>Last_Index){for(ll i=Last_Index+1;i<=n;++i){Fac.push_back(Fac[i-1]*i);Fac[i]%=m;Mod_Inv.push_back(power(Fac[i],m-2,m));}Last_Index=n;}return (((Fac[n]*Mod_Inv[r])%m)*Mod_Inv[n-r])%m;}ll gcd(ll a, ll b) {return (b ? gcd(b, a % b) : a);}
#define Test int t;cin>>t;while(t--)
#define endl '\n'
int Google_Test;
#define int ll
void solve()
{
	// cout << "Case #" << ++Google_Test << ": ";
}
int32_t main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//Test
	solve();
	return 0;
}
