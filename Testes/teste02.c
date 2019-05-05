void funcb(void){
   output(2, 9);
}

int func(void){
   output(1, 7);
   funcb();
}

void main(void)
{
   output(0, 5);
   func();
   output(0, 2);

}