#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> lnk[100001];
vector<int> tree[100001];
vector< pair<int,int> > answers;
int lvl[100001];
int visited[100001];
int without_me[100001];
int la[100001];

void maketree(int x){
    visited[x]=1;
    for(int i=0;i<lnk[x].size();i++){
        if(!visited[lnk[x][i]]){
            lvl[lnk[x][i]]=lvl[x]+1;
            tree[x].push_back(lnk[x][i]);
            maketree(lnk[x][i]);
        }
    }
}

void find_answer(int x){
    without_me[x]=lvl[x]+1;
    for(int i=0;i<tree[x].size();i++){
        find_answer(tree[x][i]);
        if(without_me[tree[x][i]]>lvl[x]&&la[tree[x][i]]==lvl[x]){
            answers.push_back(make_pair(min(x,tree[x][i]),max(x,tree[x][i])));
        }
        without_me[x]=min(without_me[x],la[tree[x][i]]);
    }
    la[x]=without_me[x];
    for(int i=0;i<lnk[x].size();i++){
        la[x]=min(la[x],lvl[lnk[x][i]]);
    }
    //printf("%d %d\n",without_me[x],la[x]);
}

int main(){
    int n,m,aa,bb;
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;i++){
        scanf("%d %d",&aa,&bb);
        lnk[aa].push_back(bb);
        lnk[bb].push_back(aa);
    }
    for(int i=1;i<=n;i++){
        if(!visited[i]) maketree(i);
    }
    /*
    for(int i=1;i<=n;i++){
        for(int j=0;j<tree[i].size();j++){
            printf(",%d",tree[i][j]);
        }
        printf("\n");
    }
    */
    for(int i=1;i<=n;i++){
        if(!lvl[i]) find_answer(i);
    }
    printf("%d\n",answers.size());
    sort(answers.begin(),answers.end());
    for(int i=0;i<answers.size();i++){
        printf("%d %d\n",answers[i].first,answers[i].second);
    }
}
