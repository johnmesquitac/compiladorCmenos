/* gdc com erro semantico - vari�vel n�o declarada */

/* teste de fun��o com par�metros e corpo sem declara��es */

/* teste de fun��o sem par�metros e sem corpo */
int input(void)
{
}

/* teste de fun��o com par�metro e sem corpo */
void output(int x)
{
}

int gdc (int u, int v)
{
    /* teste de sele��o, express�es, return e chamada de fun��o */
    if (v == output()) return u; 
    else return gdc(v,u-u/v*v);
}

/* teste de fun��o sem par�metro e com corpo completo */
void main(void)
{

   /* teste de diferentes tipos de vari�veis, incluindo vetor */
   int x;
   int y;

   int v[10];
   
   v = 10;

   /* chamadas de fun��es */
   x = input();
   y = input();
   output(gdc(x,y));

   /* teste atribui��o e repeti��o */
   u = 0; /* erro sem�ntico: vari�vel n�o declarada */
   x = 1;
   while (x <= 10)
   {
      u = u + 1;  
      v[i] = u;
      x = x + 1; 
   }

   /* teste return simples */   
   return;

}