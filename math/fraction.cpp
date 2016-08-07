typedef pair<long long int,long long int> frac;

frac plus(frac a,frac b){
	long long int gcd;
	frac res;
	res.first = a.first*b.second + a.second*b.first;
	res.second = a.second*b.second;
	if(res.first==0){
		return make_pair(0,1);
	}
	gcd = abs(__gcd(res.first,res.second));
	res.first/=gcd;res.second/=gcd;
	return res;
}

frac minus(frac a,frac b){
	long long int gcd;
	frac res;
	res.first = a.first*b.second - a.second*b.first;
	res.second = a.second*b.second;
	if(res.first==0){
		return make_pair(0,1);
	}
	gcd = abs(__gcd(res.first,res.second));
	res.first/=gcd;res.second/=gcd;
	return res;
}

frac mul(frac a,long long int b){
	if(b==0){
		return make_pair(0,1);
	}
	long long int gcd=abs(__gcd(a.second,b));
	frac res=a;
	res.second /= gcd;
	b /= gcd;
	res.first *= b;
	return res;
}

frac div(frac a,long long int b){
	if(a.first==0){
		return a;
	}
	long long int gcd=abs(__gcd(a.first,b));
	frac res=a;
	res.first /= gcd;
	b /= gcd;
	if(b<0){
		res.first = -res.first;
		b = -b;
	}
	res.second *= b;
	return res;
}
