#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define mx 101011
typedef long long ll;
inline ll Read(){
	ll x=0;
	int f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x*f;
}
struct Node{
	int v,next;
}node[mx<<1];
struct Tree{
	int l;
	int r;
	ll val,add;
}tree[mx<<2];
int cnt=0,head[mx<<1],tid[mx],cnt1;
ll real[mx];
inline void addedge(int u,int v){
	node[++cnt].v=v;
	node[cnt].next=head[u];
	head[u]=cnt;
}
int n,m,root,mod;
int top[mx],siz[mx],dep[mx],fa[mx],son[mx],a[mx];
void dfs1(int u){
	siz[u]=1,son[u]=0;
	for(int i=head[u];i;i=node[i].next){
		int d=node[i].v;
		if(d!=fa[u]){
		fa[d]=u;
		dep[d]=dep[u]+1;
		dfs1(d);
		siz[u]+=siz[d];
		if(siz[d]>siz[son[u]])son[u]=d;	
		}
	}
}
void dfs2(int x,int tp){
	tid[x]=++cnt1;
	real[tid[x]]=x;
	//”√real ˝◊È◊∞÷ÿ–¬±Í∫≈∫Û√ø∏ˆµ„µƒ÷µ 
	top[x]=tp;
	if(son[x]!=0)dfs2(son[x],tp);
	for(int i=head[x];i;i=node[i].next){
		int d=node[i].v;
		if(d!=fa[x]&&d!=son[x])dfs2(d,d);
	}
}
inline void pushup(int x){
	tree[x].val=(tree[x<<1].val+tree[(x<<1)|1].val)%mod;
}
inline void pushdown(int x){
	if(tree[x].add!=0){
		tree[x<<1].add+=tree[x].add;
		tree[(x<<1)|1].add+=tree[x].add;
		tree[x<<1].val+=(tree[x<<1].r-tree[x<<1].l+1)*tree[x].add%mod;
		tree[(x<<1)|1].val+=(tree[(x<<1)|1].r-tree[(x<<1)|1].l+1)*tree[x].add%mod;
		tree[x].add=0;
		return;
	}
}
void build(int l,int r,int i){
	tree[i].l=l;
	tree[i].r=r;
	if(r==l){
		tree[i].val=a[real[l]]%mod;
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,i<<1);
	build(mid+1,r,(i<<1)|1);
	pushup(i);
}
ll query(int l,int r,int i){
	if(l<=tree[i].l&&r>=tree[i].r)return tree[i].val;
	if(l>tree[i].r||r<tree[i].l)return 0;
	pushdown(i);
	return (query(l,r,i<<1)+query(l,r,(i<<1)|1))%mod;
}//«¯º‰≤È—Ø 
void update(int l,int r,ll num,int i){
	if(l<=tree[i].l&&r>=tree[i].r){
		tree[i].val+=(tree[i].r-tree[i].l+1)*num%mod;
		tree[i].add+=num;
		return;
	}
	pushdown(i);
	int mid=(tree[i].r+tree[i].l)>>1;
	if(l<=mid)update(l,r,num,i<<1);
	if(r>mid)update(l,r,num,(i<<1)|1);
	pushup(i);
	return;
}//«¯º‰∏¸–¬ 
void change(int x,int y,ll val){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		update(tid[top[x]],tid[x],val,1);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	update(tid[x],tid[y],val,1);
}//¡Ωµ„∏¸–¬ 
ll find_sum(int x,int y){
	ll ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans=(ans+query(tid[top[x]],tid[x],1))%mod;
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	ans=(ans+query(tid[x],tid[y],1))%mod;
	return ans;
}//«Û¡Ωµ„∫Õ 
void root_add(int i,int x){
	int begin=tid[i];
	int end=tid[i]+siz[i]-1;
	update(begin,end,x,1);
}//◊” ˜∏¸–¬ 
ll root_sum(int i){
	int begin=tid[i];
	int end=tid[i]+siz[i]-1;
	return query(begin,end,1);
}//«Û◊” ˜∫Õ 
int main(){
	//freopen("cin.txt","r",stdin);
	n=Read(),m=Read(),root=Read(),mod=Read();
	register int i;
	int u,v;
	for(i=1;i<=n;i++)a[i]=Read();//œ»”√b ˝÷µ◊∞√ø∏ˆµ„µƒ÷µ 
	for(i=1;i<n;i++){
	u=Read(),v=Read();
	addedge(u,v);
	addedge(v,u);
	}
	cnt=0;
	dfs1(root);
	dfs2(root,root);
	build(1,n,1);
	ll f,x,y,z;
	for(i=1;i<=m;i++){
	f=Read();
	if(f==1){
		x=Read(),y=Read(),z=Read();
		change(x,y,z);
	}
	if(f==2){
		x=Read(),y=Read();
		printf("%lld\n",find_sum(x,y));
	}	
	if(f==3){
		x=Read(),y=Read();
		root_add(x,y);
	}
	if(f==4){
		x=Read();
		printf("%lld\n",root_sum(x));
	}
	}
	return 0;
}
