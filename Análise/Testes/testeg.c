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
        return 0-1;
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


/* Aux Function */
void iteraVector(int vec[], int size, int curr, int type){
    if (curr < size){
        if (type == 0) vec[curr] = input();
        else output(vec[curr]);
        iteraVector(vec, size, curr + 1, type);
    }
}

void inputVector(int vec[], int size){
    iteraVector(vec, size, 0, 0);
}

void outputVector(int vec[], int size){
    iteraVector(vec, size, 0, 1);
}

void main(void){
    int type;
    int x; int y;
    type = input();
    while(type > 0){
        if (type == 1){         /* Prog 1 */
            inputVector(vet,10);
            sort(vet,0,10);
            outputVector(vet,10);
        } else if (type == 2){  /* Prog 2 */
            x = input(); y = input();
            output(gcd(x,y));
        } else if (type == 3){  /* Prog 3 */
            output(fibonacci(input()));
        } else if (type == 4){  /* Prog 4 */
            x = input();
            output(buscaBinaria(vet, 10, x));
        }
        
        type = input(); /* faca enquanto */
    }
}