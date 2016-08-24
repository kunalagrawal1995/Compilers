struct inte{
	int a;
	float f;
	// struct inte i; // should raise an ERROR;
	struct inte * t;
	struct random * r; // works, just another gcc thing
};

void inte(){ // function name same as struct name allowed
	int a;
	a = 7.0; // check the casting here	
	// return 1; // raise an ERROR
}

void func(int a, float *b, int arr[5][10], int *arr2[5]){

}

struct str_2{
	float a;
	int b;
	void *vs[10][(10*7+1)]; // v[1]; // raise ERROR as void declared; check the size of vs
};

int main(){
	int i, *ip, ia[(10)], ida[10][10];
	float f, *fp, fa[10], fda[10][10];
	void *v; // to check for random pointer assignments;
	struct str_2 s, s1, *sp, sa[10], sda[10][10];
	struct inte inter;
	struct random *rando;

	// basic base type operations to check
	i && f;
	i > f;
	i == f;
	i + f;
	i - f;
	f * f;
	!f;
	f++;

	// corner ltype checks
	// (i+f)++; 	// raise ERROR as ltype needed;
	// &(ip+i); 	// raise ERROR as ltype needed;
	(*(&(*(ip+i))))++; // allowed

	// pointer checks
	// ip == fp;	// raise an ERROR
	ip == v;
	ip == (v = sp); // the return of this should be v; which is compatible
	// ip - v;	// ERROR
	ip = ip + i;
	ip && fp; 	
	ip || fp;	
	ip++;
	!ip;

	// assignment checks
	// fp = ip;		// error
	ip = 0;
	// ia = 0;		// error
	s = s1;		// CHECK THIS
	sp = sp;
	fp = v = ip;
	ip = ia;
	// ia = ip; 	// raises an error
	// fda = &fa; 	// raises an error
	sp->b = f;	// check for pointer and type cast
	// sp.a = i + f; // ERROR
	(sp + i)->a = i + f; // alllowed
	sp = &s;
	sp = sa;
	// rando->a; 	// error
	// sp  = &inter;// error
	// &i = ip; 	// error
	// !i = ip;	// error
	// i++ = i;	// error

	// function calling checks
	func(i, v, &ia, v); // check versions in here
}