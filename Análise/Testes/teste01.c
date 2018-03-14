/* gdc com erro semantico - vari�vel n�o declarada */

/* teste de fun��o com par�metros e corpo sem declara��es */
int gdc (int a, int v)
{
    /* teste de sele��o, express�es, return e chamada de fun��o */
    if (v == 0) return v; 
    else return gdc(v,a-a/v*v);
}

/* teste de fun��o sem par�metros e sem corpo */
int input(void)
{
}

/* teste de fun��o com par�metro e sem corpo */
int output(int x)
{
	return x;
}

/* teste de fun��o sem par�metro e com corpo completo */
void main(void)
{

   /* teste de diferentes tipos de vari�veis, incluindo vetor */
   int x;
   int y;
   int a;
   int u;
   int b;
   int v[10];

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