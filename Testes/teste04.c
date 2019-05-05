int ma[10];

void teste(int m[], int s){

   m[s-1] = s;
   output(0, m[s-1]);
   output(1, s);
}

void main(void)
{

   /* teste de diferentes tipos de vari�veis, incluindo vetor */
   int m[10]; int s;
   s = 10;
   m[s-1] = 1;
   output(2, m[s-1]);
   teste(m,s);
   output(2, m[s-1]);

   ma[s-1] = 2;
   output(2, ma[s-1]);
   teste(ma,s);
   output(2, ma[s-1]);
   /* teste return simples */   
   return;

}