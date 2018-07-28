#include<cstdio>
#include<algorithm>
#define lnode now_node->l
#define rnode now_node->r
using namespace std;

struct node{
    int val;
    node *p,*l,*r;
    int cnt;
    long long sum,mini,maxi;
    bool rev;
}tree[300002];

node *root = &tree[0];
int n,q;

void preorder(node *now_node){
    if(!now_node) return;
    if(now_node->rev){
        if(lnode) lnode->rev = !(lnode->rev);
        if(rnode) rnode->rev = !(rnode->rev);
        node *tmp = lnode; lnode = rnode; rnode = tmp;
        now_node->rev = false;
    }
    //printf("push (%d,%d,%d)\n",now_node->val, now_node->cnt, now_node->rev);
    preorder(lnode);
    if(now_node->val >=1 && now_node->val <= n) printf("%d ",now_node->val);
    //printf("pop left\n");
    preorder(rnode);
    //printf("pop right\n");
}

void Update(node *now_node){
    now_node->cnt = 1;
    now_node->sum = now_node->val;
    now_node->mini = now_node->val;
    now_node->maxi = now_node->val;
    if(lnode){
        now_node->cnt += lnode->cnt;
        now_node->sum += lnode->sum;
        now_node->mini = min(now_node->mini, lnode->mini);
        now_node->maxi = max(now_node->maxi, lnode->maxi);
    }
    if(rnode){
        now_node->cnt += rnode->cnt;
        now_node->sum += rnode->sum;
        now_node->mini = min(now_node->mini, rnode->mini);
        now_node->maxi = max(now_node->maxi, rnode->maxi);
    }
}

void Rotate(node *now_node){
    node *p = now_node->p;
    node *tmp;
    if(p->rev){
        if(p->l) p->l->rev = !(p->l->rev);
        if(p->r) p->r->rev = !(p->r->rev);
        tmp = p->l; p->l = p->r; p->r = tmp;
        p->rev = false;
    }
    if(now_node->rev){
        if(lnode) lnode->rev = !(lnode->rev);
        if(rnode) rnode->rev = !(rnode->rev);
        tmp = lnode; lnode = rnode; rnode = tmp;
        now_node->rev = false;
    }
    node *moved_node;
    if(p->l == now_node){
        moved_node = now_node->r;
        p->l = moved_node;
        now_node->r = p;
    }else{
        moved_node = now_node->l;
        p->r = moved_node;
        now_node->l = p;
    }
    now_node->p = p->p;
    p->p = now_node;
    if(moved_node) moved_node->p = p;
    if(now_node->p){
        if(p == now_node->p->l) now_node->p->l = now_node;
        else now_node->p->r = now_node;
    }else{
        root = now_node;
    }
    Update(p);
    Update(now_node);
}

void Lazy(node *now_node){
    if(now_node->rev){
        node *tmp = lnode;
        lnode = rnode;
        rnode = tmp;
        if(lnode) lnode->rev = !(lnode->rev);
        if(rnode) rnode->rev = !(rnode->rev);
        now_node->rev = false;
    }
}

void Splay(node *now_node){
    while(now_node->p){
        node *p = now_node->p;
        node *g = p->p;
        if(g){
            if((g->l == p) ^ (p->l == now_node)) Rotate(now_node);
            else Rotate(p);
        }
        Rotate(now_node);
    }
}

void find_kth(int k){
    node *now_node = root;
    while(1){
        Lazy(now_node);
        int lcnt = (lnode) ? lnode->cnt : 0;
        //printf("(%d,%d)\n",now_node->val,lcnt);
        if(lcnt == k) break;
        else if(lcnt < k){
            k -= (lcnt + 1);
            now_node = rnode;
        }else{
            now_node = lnode;
        }
        //preorder(root);
    }
    Splay(now_node);
    //preorder(root);
}

void insertNode(int x){
    node *now_node = root;
    while(rnode) now_node = rnode;
    rnode = &tree[x];
    tree[x] = {x, now_node, NULL, NULL, 1, x, x, x, false};
    Splay(&tree[x]);
}

void setInterval(int ll,int rr){
    find_kth(ll-1);
    //printf("\nStep #1\n\n");
    //preorder(root);
    node *ori_root = root;
    root = root->r;
    root->p = NULL;
    //printf("\nStep #2\n\n");
    //preorder(root);
    find_kth(rr - ll + 1);
    root->p = ori_root;
    ori_root->r = root;
    root = ori_root;
    //printf("\nStep #3\n\n");
    //preorder(root);
}

int main(){
    scanf("%d%d",&n,&q);
    tree[0] = {0,NULL,NULL,NULL,1,0,0,0,false};
    for(int i=1;i<=n+1;i++){
        insertNode(i);
    }
    //preorder(root);
    for(int i=0;i<q;i++){
        int mode, aa, bb, cc;
        scanf("%d",&mode);
        if(mode == 1){
            scanf("%d%d",&aa,&bb);
            setInterval(aa,bb);
            node *now_node = root->r->l;
            printf("%lld %lld %lld\n",now_node->mini, now_node->maxi, now_node->sum);
            now_node->rev = !(now_node->rev);
        }else if(mode == 2){
            scanf("%d%d%d",&aa,&bb,&cc);
            setInterval(aa,bb);
            node *now_node = root->r->l;
            printf("%lld %lld %lld\n",now_node->mini, now_node->maxi, now_node->sum);
            int mod;
            if(cc >= 0){
                mod = (cc % (bb-aa+1));
            }else{
                mod = ((bb-aa+1) - ((-cc) % (bb-aa+1))) % (bb-aa+1);
            }
            if(mod){
                now_node->rev = !(now_node->rev);
                setInterval(aa,aa+mod-1);
                node *now_node = root->r->l;
                now_node->rev = !(now_node->rev);
                setInterval(aa+mod,bb);
                now_node = root->r->l;
                now_node->rev = !(now_node->rev);
            }
        }else if(mode == 3){
            scanf("%d",&aa);
            find_kth(aa);
            printf("%d\n",root->val);
        }else{
            scanf("%d",&aa);
            Splay(&tree[aa]);
            printf("%d\n",(&tree[aa])->l->cnt);
            //printf("\n");
        }
        //printf("\n\nFINAL\n");
        //preorder(root);
        //printf("\n");
    }
    preorder(root);
}
