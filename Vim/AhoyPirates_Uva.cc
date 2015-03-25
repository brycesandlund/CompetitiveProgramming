class SegmentTree{
    
public:
    
    int tree_len, *tree; bool *source; short *situ; int size;
    int build(int p, int s, int e){
        situ[p] = S;
        if (s == e)
        return tree[p] = (source[s]?1:0);
        int mid = getMid(s, e);
        return tree[p]  = build((p<<1), s, mid) + build((p<<1) + 1, mid + 1, e);
    }
    SegmentTree(bool *ex , int n){
        size  = n;
        int h = ceil(log2(size)) + 1;
        
        source = ex;
        tree_len = 2 * pow(2, h);
        tree = new int[tree_len+1];
        situ = new short [tree_len+1];
        build(1, 0, size-1);
    }
    ~SegmentTree(){
        delete [] tree;
        delete [] situ;
    }
    void update(int p, int s, int e){
        if (situ[p] == S) return;
        if (situ[p] == F)
        tree[p] = e -s + 1;
        else if (situ[p] == E)
        tree[p] = 0;
        else if (situ[p] == I)
        tree[p] = (e - s + 1) - tree[p];
        
        if (s != e){
            if (situ[p] == F || situ[p] == E)
            situ[_left(p)] = situ[_right(p)] = situ[p];
            else
            situ[_left(p)] = flip(situ[_left(p)]), situ[_right(p)] = flip(situ[_right(p)]);
            
        }
        situ[p] = S;
    }
    
    short flip(short v){
        if (v == I) return S;
        if (v == F) return E;
        if (v == E) return F;
        return I;
    }
    
    void rUpdate(int p, int s, int e, int qs, int qe, short com){
        update (p, s, e);
        if (s > qe || e < qs) return;
        if (s == e){
            switch(com){
                case I : tree[p] = 1 - tree[p]; break;
                case F : tree[p] = 1; break;
                case E : tree[p] = 0; break;
            }
            
            return;
        }
        
        int mid = getMid(s, e);
        if (s >= qs && e <= qe){
            switch(com){
                case F :{
                    tree[p] = e- s + 1;
                    situ [_left(p)] = situ[_right(p)] = com;
                    break;
                }
                case I :{
                    tree[p] = (e -s + 1) - tree[p];
                    situ[_left(p)] = flip(situ[_left(p)]);
                    situ[_right(p)] = flip(situ[_right(p)]);
                    break;
                }
                case E :{
                    tree[p] = 0;
                    situ [_left(p)] = situ[_right(p)] = com;
                    break;
                }
            }
            
            return;
            
        }
        
        rUpdate (_left(p), s, mid, qs, qe, com);
        rUpdate (_right(p), mid + 1, e, qs, qe, com);
        tree[p] = tree[_left(p)] + tree[_right(p)];
    }
    
    
    int getSum(int p, int s, int e, int i, int j){
        if (e < i || s > j) return 0;
        update (p, s, e);
        if (s >= i && e <= j) return tree[p];
        int mid = getMid(s, e);
        return getSum(_left(p), s, mid, i, j) + getSum(_right(p), mid + 1, e, i, j);
    }
    
    
    
}