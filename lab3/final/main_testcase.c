// // struct copying checking example; 
// // ALSO IF WE ARE USING POINTER WE NEED TO ENSURE THEY HAVE VALID ADDRESS

struct rec{
	float r;
	int i;
};

struct rec just_return(){
	struct rec rec2;
	rec2.r = 1;
	rec2.i = 0;
	return rec2;
}

int ret_param(int a){
	return a;
}

int recursion(int f, int *a, int b[10][20], struct rec r1){
	b[5][6] = 15;
	*a = 20;
	printf("f %d ", f);
	printf("\n");
	printf("r1.r %f ", r1.r);
	printf("\n");
	printf("r1.i %d ", r1.i);
	printf("\n");
	r1.r = 1;
	r1.i = 0;
	return 1.5 + b[5][6] ;
}

int main(){
	int a, b[10][20], *c[10][20];
	float f;
	struct rec r2;
	a = 4.5;
	a = f;
	f = a;
	f = a + 5; 
	c[5][6] = &a;
	b[5][6] = 10;
	a = 10;
	r2.r = 0;
	r2.i = 1;
	printf("a %d ", a);
	printf("\n");
	printf("r2.r %f ", r2.r);
	printf("\n");
	printf("r2.i %d ", r2.i);
	printf("\n");
	printf("b[5][6] %d ", b[5][6]);
	printf("\n");
	a = 1.5 + recursion(ret_param(b[5][6]), c[5][6], b, just_return());
	printf("a %d ", a);
	printf("\n");
	printf("r2.r %f ", r2.r);
	printf("\n");
	printf("r2.i %d ", r2.i);
	printf("\n");
	printf("b[5][6] %d ", b[5][6]);
	printf("\n");

	r2 = just_return();
	printf("r2.r %f ", r2.r);
	printf("\n");
	printf("r2.i %d ", r2.i);
	printf("\n");

}



// struct sax {
// 	int bo;
// 	int *saggx;
// 	float a[2][3];
// };

// float factorial(float n,struct sax *t){
// 	printf("n is ", n, "\n");
// 	if(n <= 0.0)
// 		return 1.0;
// 	else 
// 		return factorial(n-1,t)*n;
// }

// void g(float x[2][3]) {
// 	printf("val: ", x[0][1], "\n");
// }

// int main() {
// 	int d;
// 	int l;
// 	struct sax t;
// 	struct sax *ll;
// 	ll = &t;
	
// 	(*ll).a[0][1] = 5.434474 - 2.2222*0.1;
// 	printf("val3: ", ll->a[0][1], "\n");
// 	g(ll->a);
// 	printf("factorial 5 is fucking :",factorial(ll->a[0][1], ll), "\n");
// }
