class SegmentTree{
	
	// SegmentTree(int size,vector<ll> input vector)
	// update(int index,ll val)
	// result(int left_limit,int right_limit)
	
	
	private:
	int n;
	vector<ll> tree,tree2,arr,tree3;
	void build(int l,int r,int index)
	{
		if(l==r)
		{
			tree[index]=arr[l];
			tree2[index]=1;
			tree3[index]=arr[l];
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,2*index+1);
		build(mid+1,r,2*index+2);
		int c1=2*index+1;
		int c2=2*index+2;
		tree3[index]=gcd(tree3[c1],tree3[c2]);
		if(tree[2*index+1]==tree[index*2+2])
		{
			tree[index]=tree[2*index+1];
			tree2[index]=tree2[c1]+tree2[c2];
		}
		else if(tree[c1]%tree[c2]==0)
		{
			tree[index]=tree[c2];
			tree2[index]=tree2[c2];
		}
		else if(tree[c2]%tree[c1]==0)
		{
			tree[index]=tree[c1];
			tree2[index]=tree2[c1];
		}
		else
		{
			tree[index]=tree3[index];
			tree2[index]=0;
		}
	}
	
	void Iupdate(int l,int r,int index,int cindex)
	{
		if(l==r)
		{
			tree[index]=arr[l];
			tree2[index]=1;
			tree3[index]=arr[l];
			return;
		}
		int mid=(l+r)>>1;
		if(mid>=cindex)
		Iupdate(l,mid,2*index+1,cindex);
		else
		Iupdate(mid+1,r,2*index+2,cindex);
		int c1=2*index+1;
		int c2=2*index+2;
		tree3[index]=gcd(tree3[c1],tree3[c2]);
		if(tree[2*index+1]==tree[index*2+2])
		{
			tree[index]=tree[2*index+1];
			tree2[index]=tree2[c1]+tree2[c2];
		}
		else if(tree[c1]%tree[c2]==0)
		{
			tree[index]=tree[c2];
			tree2[index]=tree2[c2];
		}
		else if(tree[c2]%tree[c1]==0)
		{
			tree[index]=tree[c1];
			tree2[index]=tree2[c1];
		}
		else
		{
			tree[index]=tree3[index];
			tree2[index]=0;
		}
	}
	
	array<ll,3> Iresult(int l,int r,int index,int tl,int tr)
	{
		if(tr<tl)
		return {0,0,0};
		if(l==tl && r==tr)
		{
			return {tree[index],tree2[index],tree3[index]};
		}
		int mid=(l+r)>>1;
		array<ll,3> temp1,temp2,temp;
		temp1=Iresult(l,mid,2*index+1,tl,min(tr,mid));
		temp2=Iresult(mid+1,r,2*index+2,max(tl,mid+1),tr);
		if(temp1[0]==0 || temp2[0]==0)
		{
			temp[0]=temp1[0]+temp2[0];
			temp[1]=temp1[1]+temp2[1];
			temp[2]=temp1[2]+temp2[2];
			return temp;
		}
		temp[2]=gcd(temp1[2],temp2[2]);
		if(temp1[0]==temp2[0])
		{
			temp[0]=temp1[0];
			temp[1]=temp1[1]+temp2[1];
		}
		else if(temp1[0]%temp2[0]==0)
		{
			temp[0]=temp2[0];
			temp[1]=temp2[1];
		}
		else if(temp2[0]%temp1[0]==0)
		{
			temp[0]=temp1[0];
			temp[1]=temp1[1];
		}
		else
		{
			temp[0]=temp[2];
			temp[1]=0;
		}
		return temp;
	}
	
	public:
	//constructor
	SegmentTree(int n,vector<ll> arr)
	{
		this->n=n;
		this->arr=arr;
		tree = tree2 = tree3 = vector<ll>(4*n);
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
		array<ll,3> temp = Iresult(0,n-1,0,l,r);
		return temp[1];
	}
	
};