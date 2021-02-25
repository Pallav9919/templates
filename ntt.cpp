/*
	mod = c*(1<<k) + 1;
	root = g^((mod-1)/root_pw);
	root_1 = power(root,mod-2,mod);
	root_pw = 1 << k;
	{mod , root , root_1 , root_pw }
	{ 167772161, 243, 114609789, 1 << 25 },
	{ 415236097, 73362476, 247718523, 1<<22 },
	{ 463470593, 428228038, 182429, 1<<21},
	{ 998244353, 15311432, 469870224, 1 << 23 },
	{ 918552577, 86995699, 324602258, 1 << 22 }
*/


const int mod=998244353;
int root = 15311432;
int root_1 = power(root,mod-2,mod);
const int root_pw = 1 << 23;
vector<int> leftshift(32,-1);
int pp = -1;
inline void fft(vector<int> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (int)(1LL * wlen * wlen % mod);

        for (int i = 0; i < n; i += len) {
            int w = 1;
            int lb2 = len / 2;
            for (int j = 0; j < lb2; ++j) {
            	int ind = i+j;
            	int indlb2 = ind + lb2;
                int u = a[ind], v = (int)(1LL * a[indlb2] * w % mod);
                a[ind] = u + v < mod ? u + v : u + v - mod;
                a[indlb2] = u - v >= 0 ? u - v : u - v + mod;
                w = (int)(1LL * w * wlen % mod);
            }
        }
    }

    if (invert) {
        int n_1;
        if(pp == -1) pp = power(n, mod-2,mod);
    	n_1 = pp;
        for (int & x : a)
            x = (int)(1LL * x * n_1 % mod);
    }
}
inline vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int j = 0;
    int n = leftshift[j];
    while (n < (int)a.size() + (int)b.size()) 
        n = leftshift[++j];
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] = (1ll*fa[i]*fb[i])%mod;
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = fa[i];
    return result;
}