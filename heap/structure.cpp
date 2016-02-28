#include<stdio.h>
#define swap(xx,yy) {int zz;zz=xx;xx=yy;yy=zz;}

struct heap{
    int su[100002];
    int sz;
    heap(){
        sz=1;
    }
    int size(){
    	return sz-1;
    }
    bool compare(int a,int b){
    	return a>b;
    }
    void push(int x){
    	int idx=sz;
    	su[sz++]=x;
    	while(idx>1){
    		if(compare(su[idx],su[idx/2])){
    			swap(su[idx],su[idx/2]);
    			idx/=2;
    		}else{
    			break;
    		}
    	}
    }
    int pop(){
    	int left,right,idx=1;
    	if(size()==0) return 0;
    	sz--;
    	swap(su[sz],su[1]);
    	while(1){
    		left=idx*2;right=idx*2+1;
    		if(left>sz-1){
    			break;
    		}else if(left==sz-1){
    			if(compare(su[left],su[idx])){
    				swap(su[idx],su[left]);
    			}
    			break;
    		}else{
    			if(compare(su[left],su[right])){
	    			if(compare(su[left],su[idx])){
	    				swap(su[idx],su[left]);
	    				idx=left;
	    			}else{
	    				break;
	    			}
    			}else{
    				if(compare(su[right],su[idx])){
	    				swap(su[idx],su[right]);
	    				idx=right;
	    			}else{
	    				break;
	    			}
    			}
    		}
    	}
    	return su[sz];
    }
};

heap maxheap = heap();

int main(){
	int n,command;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&command);
		if(command==0){
			printf("%d\n",maxheap.pop());
		}else{
			maxheap.push(command);
		}
	}
}
