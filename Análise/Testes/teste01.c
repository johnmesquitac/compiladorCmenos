int Else(int b){
  return b+2;
}

void main(void)
{
   int y;
   int u;
   int x[10];
   y = 1;
   u = 0;

   if(x<0){
      u = 1;
   }

   while(u<10){
    u = u + 2;
   }

   x = input();

   output(0, x);

   y = Else(3) + u;
}