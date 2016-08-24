// struct copying checking example; 
// ALSO IF WE ARE USING POINTER WE NEED TO ENSURE THEY HAVE VALID ADDRESS
// struct rec{
// 	float d;
// };

// struct mystruct{
// 	int a, b;
// 	float c, d;
// 	struct rec rec1;
// };

// int main(){
// 	struct mystruct p, *q;
// 	struct rec rec1;
// 	q = &p;
// 	rec1.d = 2.5;
// 	q->a = 4;
// 	q->b = 5;
// 	q->c = 4.4;
// 	q->d = 5.5;
// 	q->rec1 = rec1;
// 	printf(p.a, "\n");
// 	printf(p.b, "\n");
// 	printf(p.c, "\n");
// 	printf(p.d, "\n");
// 	printf((p.rec1).d, "\n");
// 	printf(q->a, "\n");
// 	printf(q->b, "\n");
// 	printf(q->c, "\n");
// 	printf(q->d, "\n");
// 	printf((q->rec1).d, "\n");
// }


struct rec{
	float r;
	int i;
};

int recursion(int f, int *a, int b[10][20], struct rec r1){
	int i;
	i = 10;
	b[5][6] = 20;
	return b[5][6];
}

int main(){
	int a, b[10][20];
	struct rec r2;
	b[5][6] = 10;
	a = 1;
	r2.r = 6;
	r2.i = a;
	a = recursion(a, &a, b, r2);
	printf("%d\n", b[5][6]);
}