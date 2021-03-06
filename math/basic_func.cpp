namespace mathfunc{
  typedef long long LL;
  LL powermod(LL n_,LL k_,LL m_){ // n^k mod m
    LL res = 1, gop = n_%m_;
    while(k_){
      if(k_&1){
        res *= gop;
        res %= m_;
      }
      gop *= gop;
      gop %= m;
      k_ >>= 1;
    }
    return res;
  }
  LL gcd(LL a_,LL b_){  //gcd(a,b)
    if(!b_) return a_;
    else return gcd(b_,a_%b_);
  }
  pair<LL,LL> extended_gcd(LL a_,LL b_){  //ax+by = gcd(a,b)
    if(!b_) return make_pair(1,0);
    pair<LL,LL> retval = extended_gcd(b_,a_%b_);
    return make_pair(retval.second,retval.first - ((a_/b_) * retval.second));
  }
  LL modinv(LL a_,LL m_){  //ax === gcd(a,m) (mod m)
    return (extended_gcd(a_,m_).first % m_ + m_) % m_;
  }
};
