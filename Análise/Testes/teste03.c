int multiplica(int a, int b){
	int x;

	if(a == 1){
		return b;
	}
	
	x = b + multiplica(a-1, b);
	return x;
}


void main(void)
{

   int x;
   int y;

   x = input();
   y = input();

   output(0, x);
   output(1, y);

   output(2, multiplica(x, y));
}