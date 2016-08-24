void ar(float f[10]){
	int i;
	float *g;
	printf("hello\n");
	g = f;
	for (i = 0; i < 10; i++){
		printf(" %f ", g[i]);
		printf("\n");
	}
	for (i = 0; i < 5; i++){
		g[i] = 1;
	}
}


int main(){
	int i;
	float f[10];
	float *g;
	for (i = 0; i < 10; i++){
		f[i] = 2;
	}
	
	printf("hello\n");
	g = f;

	ar(g);
	printf("hello\n");
	for (i = 0; i < 10; i++){
		printf(" %f ", f[i]);
		printf("\n");
	}	

	i = g[1] + g[6];
	printf(" %d ", i);
	printf("\n");
}