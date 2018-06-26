void imprime(int b){
	while(10>b){
		output(2, b);
		b = b + 1;
	}
}

void main(void){
	int a;

	a = input();
	imprime(a);	
}