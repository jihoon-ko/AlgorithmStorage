#include <cstdio>
using namespace std;

struct node{
	int val;
	node *l;
	node *r;
};

node mem[15000000];
node *root[500001];
int memp = 1;

void make_persistent_segtree(int x,node* now_parent,node *prev,int ss,int ee,int is_right){
	if(ss<=x && x<=ee){
		//printf(">%d %d %d %d %d %d\n",now_parent,prev-mem,ss,ee,1,prev->val);
		int new_nodep = memp,mid = (ss+ee) >> 1;
		mem[memp++] = {prev->val + 1, NULL, NULL};
		if(is_right) now_parent->r = mem + new_nodep;
		else 		 now_parent->l = mem + new_nodep;
		if(ss == ee) return;
		make_persistent_segtree(x,mem+new_nodep,prev->l,ss,   mid, 0);
		make_persistent_segtree(x,mem+new_nodep,prev->r,mid+1,ee,  1);
	}else{
		//printf(">%d %d %d %d %d\n",now_parent,prev-mem,ss,ee,prev->val);
		if(is_right) now_parent->r = prev;
		else 		 now_parent->l = prev;
		return;
	}
}

int getxor(int x,node *rp,node *lp){
	int ans = 0;
	for(int i=262144;i;i>>=1){
		//printf(">%d %d %d %d %d\n",ans,rp->l->val,rp->r->val,lp->l->val,lp->r->val);
		if(x&i){
			if(rp->l->val == lp->l->val){
				ans += i;
				rp = rp->r; lp = lp->r;
			}else{
				rp = rp->l; lp = lp->l;
			}
		}else{
			if(rp->r->val == lp->r->val){
				rp = rp->l; lp = lp->l;
			}else{
				ans += i;
				rp = rp->r; lp = lp->r;
			}
		}
	}
	return ans;
}

int getcnt(int x,node *rp,node *lp){
	int ss = 0, ee = 524287, mid, ans = 0;
	while(ss<=ee){
        //printf("%d %d %d %d %d %d\n",ss,ee,rp->l->val,rp->r->val,lp->l->val,lp->r->val);
		mid = (ss+ee) >> 1;
		if(x == mid){
			ans += rp->l->val - lp->l->val;
			break;
		}else if(x < mid){
			rp = rp->l;lp = lp->l;
            ee = mid;
		}else{
			ans += rp->l->val - lp->l->val;
			rp = rp->r;lp = lp->r;
			ss = mid + 1;
		}
	}
	return ans;
}

int getkth(int x,node *rp,node *lp){
	int ss = 0, ee = 524287, mid, ans = -1;
	while(ss<ee){
		mid = (ss+ee) >> 1;
		if(x <= rp->l->val - lp->l->val){
			ee = mid;
			rp = rp->l;lp = lp->l;
		}else{
		    ss = mid + 1;
			x -= rp->l->val - lp->l->val;
			rp = rp->r;lp = lp->r;
		}
	}
	return ss;
}

int main(){
	int t,n=0;
	scanf("%d",&t);
	for(int i=1;i<524288;i++) mem[i] = {0,mem + (i*2),mem + (i*2+1)};
	for(int i=524288;i<1048576;i++) mem[i] = {0,NULL,NULL};
	memp = 1048576;
	root[0] = mem+1;
	while(t--){
		int mode;
		scanf("%d",&mode);
		if(mode==1){
			int x;
			scanf("%d",&x);
			n++;
			root[n] = mem+memp;
			mem[memp++] = {n,NULL,NULL};
			make_persistent_segtree(x,root[n],root[n-1]->l,     0,262143,0);
			make_persistent_segtree(x,root[n],root[n-1]->r,262144,524287,1);
		}else if(mode==3){
			int x;
			scanf("%d",&x);
			n-=x;
		}else if(mode==2){
			int l,r,x;
			scanf("%d %d %d",&l,&r,&x);
			printf("%d\n",getxor(x,root[r],root[l-1]));
		}else if(mode==4){
			int l,r,x;
			scanf("%d %d %d",&l,&r,&x);
			printf("%d\n",getcnt(x,root[r],root[l-1]));
		}else{
			int l,r,x;
			scanf("%d %d %d",&l,&r,&x);
			printf("%d\n",getkth(x,root[r],root[l-1]));
		}
	}
	return 0;
}
