/* Function 1 */
int vet[ 10 ];

int minloc ( int a[], int low, int high ){
    int i; int x; int k;
    k = low;
    x = a[low];
    i = low + 1;
    while (i < high){
        if (a[i] < x){
            x = a[i];
            k = i;
        }
        i = i + 1;
    }
    return k;
}

void sort( int a[], int low, int high){
    int i; int k;
    i = low;
    while (i < high-1){
        int t;
        k = minloc(a,i,high);
        t = a[k];
        a[k] = a[i];
        a[i] = t;
        i = i + 1;
    }
}

/* Function 2 */
int gcd (int u, int v){       
    if (v == 0) return u ;
    else return gcd(v,u-u/v*v);
    /* u-u/v*v == u mod v */
}

/* Function 3 */
int fibonacci(int n){
    int a; int b; int c; int i;
    if (n <= 0) return 0;
    else if (n == 1) return 1;
    else {
        a = 0; 
        b = i = 1;  
        while (i < n){
            c = b;
            b = b + a;
            a = c;
            i = i + 1;
        }
        return b;
    }
}

/* Function 4 */
int buscaBinariaInterno(int vetor[], int inicio, int fim, int id){
    int meio; 
    meio = (fim + inicio)/2;
    if(fim < inicio){
        return 0;
    }else{
        if(id > vetor[meio-1]){
            return buscaBinariaInterno(vetor,meio+1,fim,id);
        }else if(id < vetor[meio-1]){
            return buscaBinariaInterno(vetor,inicio,meio-1,id);
        }else{
            return meio;
        }
    }
}

int buscaBinaria(int vec[], int size, int id){
    return buscaBinariaInterno(vec,1,size,id);
}

/* Function 5 */
int fatorial (int n){       
    if (n < 2) return 1;
    else return fatorial(n-1)*n;
}

int calculadora(int a, int b, int op){
    if (op == 1) return a+b;
    else if (op == 2) return a-b;
    else if (op == 3) return a*b;
    else if (op == 4) return a/b;
    else if (op == 5) return a-a/b*b; /* mod(a,b) */
    else if (op == 6) return a*b/100; /* porcentagem(a,b) */
}

int mediaVector(int vec[], int size){
    int i; int total;
    i = 0; total = 0;
    while(i < size){
        total = total + vec[i];
        i = i + 1;        
    }
    return total/size;
}

/*int varianciaVector(int vec[], int size){
    int i; int total; int media; int aux;
    i = 0; total = 0;
    media = mediaVector(vec,size);
    while(i < size){
        aux = vec[i] - media;
        total = total + (aux*aux);
        i = i + 1;        
    }
    return total/size;
}*/

void extremosVector(int vec[], int size){
    int i; int menor; int maior;
    i = 1;
    menor = maior = vec[0];
    while(i < size){
        if(vec[i] < menor) menor = vec[i];
        else if (vec[i] > maior) maior = vec[i];
        i = i + 1;        
    }
    output(2, menor);
    output(2, maior);
}

/* Aux Function */
void inputVector(int vec[], int size){
    int i;
    i = 0;
    while(i < size){
        vec[i] = input();
        i = i + 1;        
    }
}

void outputVector(int vec[], int size){
    int i;
    i = 0;
    while(i < size){
        output(2, vec[i]);
        i = i + 1;        
    }
}

void main(void){
    int type;
    int x; int y; int z;
    type = input();
    while(type > 0){
        if (type == 1){         /* Prog 1 */
            inputVector(vet,10);
        } else if (type == 2){  /* Prog 2 */
            outputVector(vet,10);
        } else if (type == 3){  /* Prog 3 */
            sort(vet,0,10);
        } else if (type == 4){  /* Prog 4 */
            output(2, mediaVector(vet,10));
        } else if (type == 5){  /* Prog 5 */
            extremosVector(vet,10);
        } else if (type == 6){  /* Prog 6 */
            x = input();
            output(2, buscaBinaria(vet, 10, x));
        } else if (type == 7){  /* Prog 7 */
            x = input(); y = input();
            output(2, gcd(x,y));
        } else if (type == 8){  /* Prog 8 */
            output(2, fibonacci(input()));
        } else if (type == 9){  /* Prog 9 */
            output(2, fatorial(input()));
        } else if (type == 10){ /* Prog 10 */
            x = input(); y = input(); z = input();
            output(2, calculadora(x,y,z));
        } 
        
        type = input(); /* faca enquanto */
    }
}
