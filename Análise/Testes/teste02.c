int soma(int a, int b){
   return a + b;
}

void main(void)
{
   int x;
   int y;

   x = input();
   y = input();

   output(0, x);
   output(1, y);

   output(2, soma(x, y));

}