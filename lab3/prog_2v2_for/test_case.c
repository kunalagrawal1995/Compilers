// struct copying checking example; 
// ALSO IF WE ARE USING POINTER WE NEED TO ENSURE THEY HAVE VALID ADDRESS
// struct rec{
// 	float d;
// };

// struct mystruct{
// 	int a;
// 	float c;
// 	struct rec rec1;
// };

// int main(){
// 	struct mystruct p, *q, r;
// 	struct rec rec1;
// 	q = &p;
// 	rec1.d = 2.5;
// 	q->a = 4;
// 	q->c = 4.4;
// 	q->rec1 = rec1;
// 	r = *q;
// 	printf(r.a, "\n");
// 	printf(r.c, "\n");
// 	printf((r.rec1).d, "\n");
// 	printf(q->a, "\n");
// 	printf(q->c, "\n");
// 	printf((q->rec1).d, "\n");
// 	printf(p.a, "\n");
// 	printf(p.c, "\n");
// 	printf((p.rec1).d, "\n");
// 	r.a = 5.5;
// 	r.c = 2;
// 	rec1.d = 3;
// 	r.rec1 = rec1;
// 	*q = r;	
// 	printf(r.a, "\n");
// 	printf(r.c, "\n");
// 	printf((r.rec1).d, "\n");
// 	printf(q->a, "\n");
// 	printf(q->c, "\n");
// 	printf((q->rec1).d, "\n");
// 	printf(p.a, "\n");
// 	printf(p.c, "\n");
// 	printf((p.rec1).d, "\n");
// }


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

float recursion(int f, int *a, int b[10][20], struct rec r1){
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
	a = 1;
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
	a = recursion(ret_param(b[5][6]), c[5][6], b, just_return());
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
