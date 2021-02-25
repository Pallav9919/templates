class FenwickTree{
	
	// FenwickTree(int size,vector<ll> input vector)
	// update(int index,ll val)
	// sum of 1 to index
	// result(int index)
	
	
	private:
	int n;
	vector<ll> tree,arr;
	
	
	
	public:
	//constructor
	FenwickTree(int n,vector<ll> arr)
	{
		this->n=n;
		this->arr=arr;
		tree = vector<ll>(n+1);
		for(int i=1;i<=n;++i)
		update(i,arr[i-1]);
	}
	
	
	
	void update(int index,ll val)
	{
		while(index<=n)
		{
			tree[index] += val;
			index += index & (-index);
		}
	}
	
	ll result(int index)
	{
		ll Ans=0;
		while(index>0)
		{
			Ans += tree[index];
			index -= index & (-index);
		}
		return Ans;
	}
	
};