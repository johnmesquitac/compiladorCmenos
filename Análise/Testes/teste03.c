int mult(int a, int b){
   int x;

   output(1, a);
   output(0, b);
	
   if(a == 1){
      output(2, 11);
		return b;
	}
	
   output(2, 10);
   x = b + mult(a-1, b);
   output(2, x);
	
   return  x;
}


void main(void)
{

   int x;
   int y;

   x = input();
   y = input();

   output(0, x);
   output(1, y);

   output(2, mult(x, y));
}