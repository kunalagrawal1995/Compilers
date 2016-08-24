struct sax {
	int bo;
	int *saggx;
	float a[2][3];
};

float factorial(float n,struct sax *t){
	printf("n is ", n, "\n");
	if(n <= 0.0)
		return 1.0;
	else 
		return factorial(n-1,t)*n;
}

void g(float x[3]) {
	printf("val: ", x[1], "\n");
	x[1] = 10;
}

int main() {
	int d;
	int l;
	struct sax t;
	struct sax *ll;
	ll = &t;
	(*ll).a[0][1] = 5.434474 - 2.2222*0.1;
	printf("val3: ", ll->a[0][1], "\n");
	g(ll->a[0]);
	printf("factorial 5 is fucking :",factorial(ll->a[0][1], ll), "\n");
}