// $%U%$
// Mere bas ka nahi hai
// still i'm trying
// apna time aayega
//
//        .--------------.  
//        | Try First One|
//        '--------------'
//                |     .--------------.
//                |     |              |
//                V     V              |
//              .--------------.       |
//              |      AC.     |<---.  |  
//              '--------------'    |  |
//              (True)|  |(False)   |  |
//           .--------'  |          |  |
//           |           V          |  |
//           |  .--------------.    |  |
//           |  |   Try Again  |----'  |
//           |  '--------------'       |
//           |                         |
//           |  .--------------.       |
//           '->| Try Next One |-------'
//              '--------------'                          		  
//
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll power(ll x,ll y,ll m){if(y==0)return 1;ll p=power(x,y/2,m)%m;p=(p*p)%m;return (y%2==0)?p:(x*p)%m;}
ll nCr(ll n,ll r,ll m){if(r>n)return 0;ll a=1,b=1,i;for(i=0;i<r;i++){a=(a*n)%m;--n;}while(r){b=(b*r)%m;--r;}return (a*power(b,m-2,m))%m;}
#define Test int t;cin>>t;while(t--)
#define endl '\n'
#define poly vector<int>
// Xor [1  1]    And   [0 1]       Or [1 1]
//     [1 -1]          [1 1]          [1 0]
inline void FWHT(poly &P, bool inverse) {
	int deg=P.size();
    for (int len = 1; 2 * len <= deg; len <<= 1) {
        for (int i = 0; i < deg; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                int u = P[i + j];
                int v = P[i + len + j];
				if(!inverse)
				{
                	P[i + j] = u + v;
                	P[i + len + j] = u ;
				}
				else
				{
					P[i + j] = v;
                	P[i + len + j] = u - v;
					//P[i + j] = P[i + j]/deg;
					//P[i + len + j] = P[i + len + j]/deg;
				}
            }	
        }
    }
}
inline vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < max((int)a.size() , (int)b.size())) 
        n <<= 1;
		//cout << n << endl;
    fa.resize(n);
    fb.resize(n);

    FWHT(fa, false);
    FWHT(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    FWHT(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
		   result[i] = (fa[i]?1:0);
    return result;
}
void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	vector<int> eq((int)1e6+1);
	int ans=0;
	for(int i=0;i<n;++i)
	{
		cin >> a[i];
		eq[a[i]]=1;
		ans|=a[i];
	}
	vector<int> result;
	result=eq;
	for(int i=0;i<n;++i)
	{
		if(result[ans]>=1)
		{
			cout << i+1 << endl;
			return;
		}
		result = multiply(result,eq);
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//Test
	solve();
	return 0;
}
