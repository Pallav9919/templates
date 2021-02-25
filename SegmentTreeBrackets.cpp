class SegmentTree{
	
	// 1 for ( 
	// -1 for )
	// SegmentTree(int size,vector<ll> input vector)
	// update(int index,ll val)
	// result(int left_limit,int right_limit)
	
	
	private:
	int n;
	vector<ll> tree,arr,open,close;
	void build(int l,int r,int index)
	{
		if(l==r)
		{
			if(arr[l]==1)
			open[index]=1;
			else
			close[index]=1;
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,2*index+1);
		build(mid+1,r,2*index+2);
		tree[index]=tree[2*index+1]+tree[2*index+2];
		tree[index]+=2*min(open[2*index+1],close[2*index+2]);
		open[index]=open[2*index+1]-min(open[2*index+1],close[2*index+2]);
		open[index]+=open[2*index+2];
		close[index]=close[2*index+2]-min(open[2*index+1],close[2*index+2]);
		close[index]+=close[2*index+1];
	}
	
	void Iupdate(int l,int r,int index,int cindex)
	{
		if(l==r)
		{
			if(arr[l]==1)
			{
				open[index]=1;
				close[index]=0;
				tree[index]=0;
			}
			else
			{
				open[index]=0;
				close[index]=1;
				tree[index]=0;
			}
			return;
		}
		int mid=(l+r)>>1;
		if(mid>=cindex)
		Iupdate(l,mid,2*index+1,cindex);
		else
		Iupdate(mid+1,r,2*index+2,cindex);
		tree[index]=tree[2*index+1]+tree[2*index+2];
		tree[index]+=2*min(open[2*index+1],close[2*index+2]);
		open[index]=open[2*index+1]-min(open[2*index+1],close[2*index+2]);
		open[index]+=open[2*index+2];
		close[index]=close[2*index+2]-min(open[2*index+1],close[2*index+2]);
		close[index]+=close[2*index+1];
	}
	
	array<ll,3> Iresult(int l,int r,int index,int tl,int tr)
	{
		if(tr<tl)
		return {0,0,0};
		if(l==tl && r==tr)
		{
			return {tree[index],open[index],close[index]};
		}
		int mid=(l+r)>>1;
		array<ll,3> temp1,temp2,temp;
		temp1=Iresult(l,mid,2*index+1,tl,min(tr,mid));
		temp2=Iresult(mid+1,r,2*index+2,max(tl,mid+1),tr); 
		temp[0]=temp1[0]+temp2[0]+2*min(temp1[1],temp2[2]);
		ll mn=min(temp1[1],temp2[2]);
		temp1[1]-=mn;
		temp2[2]-=mn;
		temp[1]=temp1[1]+temp2[1];
		temp[2]=temp1[2]+temp2[2];
		return temp;
	}
	
	public:
	//constructor
	SegmentTree(int n,vector<ll> arr)
	{
		this->n=n;
		this->arr=arr;
		tree = open = close = vector<ll>(4*n);
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
		array<ll,3> u=Iresult(0,n-1,0,l,r);
		return u[0];
	}
	
};