#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll power(ll x,ll y,ll m){if(y==0)return 1;ll p=power(x,y/2,m)%m;p=(p*p)%m;return (y%2==0)?p:(x*p)%m;}
ll nCr(ll n,ll r,ll m){if(r>n)return 0;ll a=1,b=1,i;for(i=0;i<r;i++){a=(a*n)%m;--n;}while(r){b=(b*r)%m;--r;}return (a*power(b,m-2,m))%m;}
vector<ll> fac;
ll nCr2(ll n,ll r,ll m){if(r>n) return 0;return (((fac[n]*power(fac[r],m-2,m))%m)*power(fac[n-r],m-2,m))%m;}
ll gcd(ll a, ll b) {return (b ? gcd(b, a % b) : a);}
#define Test int t;cin>>t;while(t--)
#define endl '\n'

bool BPM(vector<vector<int>> g,int node,vector<int> vis,vector<int> &match)
{
	for(int child:g[node])
	{
		if(!vis[child])
		{
			vis[child] = true;
			if(match[child] < 0 || BPM(g,match[child],vis,match))
			{
				match[child]=node;
				return true;
			}
		}
	}
	return false;
}

vector<int> maxBPM(int n,vector<vector<int>> g)
{
	vector<int> match(n,-1);
	for(int i=0;i<n;++i)
	{
		vector<int> vis(n);
		BPM(g,i,vis,match);
	}
	return match;
}

vector<int> hungarian(int n,vector<vector<int>> v)
{
	for(int i=0;i<n;++i)
	{
		int mn=INT_MAX;
		for(int j=0;j<n;++j)
		{
			mn=min(mn,v[i][j]);
		}
		for(int j=0;j<n;++j)
		{
			v[i][j] -= mn;
		}
	}
	for(int i=0;i<n;++i)
	{
		int mn=INT_MAX;
		for(int j=0;j<n;++j)
		{
			mn=min(mn,v[j][i]);
		}
		for(int j=0;j<n;++j)
		{
			v[j][i] -= mn;
		}
	}
	while(true)
	{
		vector<bool> horizontal(n),vertical(n);
		for(int i=0;i<n;++i)
		{
			int cnt=0;
			for(int j=0;j<n;++j)
			{
				if(v[i][j]==0)
				cnt++;
			}
			if(cnt>1)
			horizontal[i]=true;
		}
		for(int i=0;i<n;++i)
		{
			for(int j=0;j<n;++j)
			{
				if(v[i][j]==0 && !horizontal[i])
				{
					vertical[j]=true;
				}
			}
		}
		int cnt=0;
		for(int i=0;i<n;++i)
		{
			cnt+=horizontal[i];
			cnt+=vertical[i];
		}
		if(cnt==n)
		break;
		int mn = INT_MAX;
		for(int i=0;i<n;++i)
		{
			for(int j=0;j<n;++j)
			{
				if(!horizontal[i] && !vertical[j])
				mn = min(mn,v[i][j]);
			}
		}
		for(int i=0;i<n;++i)
		{
			for(int j=0;j<n;++j)
			{
				if(!horizontal[i] && !vertical[j])
				v[i][j] -= mn;
			}
		}
	}
	vector<vector<int>> g(n);
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<n;++j)
		{
			if(v[i][j]==0)
			g[i].push_back(j);
		}
	}
	return maxBPM(n,g);
}
void solve()
{
	int n;
	cin >> n;
	vector<vector<int>> v(n,vector<int>(n));
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<n;++j)
			cin >> v[i][j];
	}
	vector<int> ans = hungarian(n,v);
	int fans=0;
	for(int i=0;i<n;++i)
	{
		fans += v[ans[i]][i];
	}
	cout << fans << endl;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//Test
	solve();
	return 0;
}
