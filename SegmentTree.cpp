class SegmentTree{
	
	// SegmentTree(int size,vector<ll> input vector)
	// update(int index,ll val)
	// result(int left_limit,int right_limit)
	
	
	private:
	int n;
	vector<ll> tree,arr;
	void build(int l,int r,int index)
	{
		if(l==r)
		{
			tree[index]=arr[l];
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,2*index+1);
		build(mid+1,r,2*index+2);
		tree[index]=tree[2*index+1]+tree[2*index+2];
	}
	
	void Iupdate(int l,int r,int index,int cindex)
	{
		if(l==r)
		{
			tree[index]=arr[l];
			return;
		}
		int mid=(l+r)>>1;
		if(mid>=cindex)
		Iupdate(l,mid,2*index+1,cindex);
		else
		Iupdate(mid+1,r,2*index+2,cindex);
		tree[index]=tree[2*index+1]+tree[2*index+2];
	}
	
	ll Iresult(int l,int r,int index,int tl,int tr)
	{
		if(tr<tl)
		return 0;
		if(l==tl && r==tr)
		{
			return tree[index];
		}
		int mid=(l+r)>>1;
		return Iresult(l,mid,2*index+1,tl,min(tr,mid))+Iresult(mid+1,r,2*index+2,max(tl,mid+1),tr); 
	}
	
	public:
	//constructor
	SegmentTree(int n,vector<ll> arr)
	{
		this->n=n;
		this->arr=arr;
		tree = vector<ll>(4*n);
		build(0,n-1,0);
	}
	
	
	
	void update(int index,ll val)
	{
		--index;
		arr[index]=val;
		Iupdate(0,n-1,0,index);
	}
	
	ll result(int l,int r)
	{
		--l;--r;
		return Iresult(0,n-1,0,l,r);
	}
	
};