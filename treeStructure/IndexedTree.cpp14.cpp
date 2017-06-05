#include<bits/stdc++.h>
using namespace std;

template<typename T>
class idxTree{
private:
    int sz;
    vector<T> tree;
    T initVal;
    T exeRule(T ans, T oddNode){
        return min(ans, oddNode);
        // Can change rule for your indexedTree
    }
    bool updRule(int pIdx){
        if(!pIdx) return false;
        else{
            tree[pIdx] = exeRule(tree[pIdx * 2], tree[pIdx * 2 + 1]);
            return true;
        }
        // Can change rule for your indexedTree
    }
public:
    idxTree(int _sz, T _initVal){
        _sz--;
        sz = 1;
        while(_sz){
            _sz >>= 1;
            sz <<= 1;
        }
        initVal = _initVal;
        tree.resize(sz * 2);
        for(int i=0;i<(sz * 2);i++) tree[i] = initVal;
    }
    void upd(int tIdx, T target){
        tIdx += sz;
        tree[tIdx] = target;
        tIdx >>= 1;
        while(updRule(tIdx)) tIdx >>= 1;
    }
    T exe(int from, int to){
        T ans = initVal;
        from += sz; to += sz;
        while(from <= to){
            if((from & 1) == 1) ans = exeRule(ans, tree[from++]);
            if((to & 1) == 0) ans = exeRule(ans, tree[to--]);
            if(from > to) break;
            from >>= 1; to >>= 1;
        }
        return ans;
    }
};

idxTree<int> iTree = idxTree<int>(n+1, 0x7fffffff);
//iTree.upd(i, su) : put su in ith index
//iTree.exe(ss, ee) : get max (or min) value (index from ss to ee)
