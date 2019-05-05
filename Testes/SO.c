int tamanhoPilha;
int tamanhoMemProg;

int findProg(int name){
    int i;
    i = 0;
    while(i < 16){
        if(statusArq(i)==1)
            if(name == nameArq(i))
                return i;
        i = i + 1;
    }
    return 0-1;
} 

void saveRegs(void){
    int baseMem;
    int nprogAtual;
    int desl;

    baseMem = get_MemProgAtual();
    nprogAtual = get_nprogAtual();

    desl = baseMem+200;

    regToMem(0, desl+0);
    regToMem(1,  desl+1);
    regToMem(2, desl+2);
    regToMem(3,  desl+3);
    regToMem(4,  desl+4);
    regToMem(5, desl+5);
    regToMem(6, desl+6);
    regToMem(7,  desl+7);
    regToMem(8,  desl+8);
    regToMem(9,  desl+9);
    regToMem(10,  desl+10);
    regToMem(11,  desl+11);
    regToMem(12,  desl+12);
    regToMem(13,  desl+13);
    regToMem(14,  desl+14);
    regToMem(15,  desl+15);
    regToMem(16,  desl+16);
    regToMem(17,  desl+17);
    regToMem(18,  desl+18);
    regToMem(19,  desl+19);

    return;
}

void recoveryRegs(int prog){
    
    int desc;
    desc = 700*prog+200;

    memToReg(0, desc+0);
    memToReg(1, desc+1);
    memToReg(2, desc+2);
    memToReg(3, desc+3);
    memToReg(4, desc+4);
    memToReg(5, desc+5);
    memToReg(6, desc+6);
    memToReg(7, desc+7);
    memToReg(8, desc+8);
    memToReg(9, desc+9);
    memToReg(10, desc+10);
    memToReg(11, desc+11);
    memToReg(12, desc+12);
    memToReg(13, desc+13);
    memToReg(14, desc+14);
    memToReg(15, desc+15);
    memToReg(16, desc+16);
    memToReg(17, desc+17);
    memToReg(18, desc+18);
    memToReg(19, desc+19);
    
    return;
}

int execProg(int name, int executado){
    int posicaoProg;
    int x;
    int finalizou;
    int error;
    error = 0 - 1;
    finalizou = 1;
    posicaoProg = findProg(name);
    output(2, posicaoProg);

    if(posicaoProg == error){
        return 0 - 1;
    } 
    else{

        saveRegs();
        recoveryRegs(posicaoProg);
        set_nprogAtual(posicaoProg);
        if(executado == 0){
            set_prog(posicaoProg);
        }
        else { 
            set_progBack();
        }
        /*Retorno Dinamico*/

        finalizou = 0;

        /*Retorno Estático*/
        setPreempcao(0);
        saveRegs();
        set_nprogAtual(0);
        set_SO();
        recoveryRegs(0);

    }/*Retorna 0 se finalizou, senao retorna 1*/
    return finalizou;
}

int execUmProg(void){
    int nameprog;
    setPreempcao(0);
    nameprog = input();
    execProg(nameprog, 0);

    return 1;
}


int execNProg(void){
    int qnt;
    int lista[10];
    int ativo[10];
    int executado[10];
    int ativos;
    int i;
    int j;

    j = 0-1;
    i = 0;
    qnt = input();
    while(i<qnt){
        lista[i] = input();
        ativo[i] = 1;
        executado[i] = 0;
        i = i + 1;
    }

    i = 0;
    ativos = 0;

    while(i<qnt){
        ativos = ativos + ativo[i];
        i = i + 1;
    }

    while(ativos>0){
        j = j + 1;
        if(j == qnt) j = 0;

        if(ativo[j] == 1){

            setPreempcao(1);
            ativo[j] = execProg(lista[j], executado[j]);
            executado[j] = 1;
            if(ativo[j] == 0) output(2, 100+lista[j]);
        }

        i = 0;
        ativos = 0;

        while(i<qnt){
            ativos = ativos + ativo[i];
            i = i + 1;
        }
    }
    /*showReg(16);*/
    return 1;
}

int renameProg(void){
    int nameprog;
    int newName;
    int posicaoProg;
    nameprog = input();
    posicaoProg = findProg(nameprog);
    output(2, posicaoProg);

    newName = input();
    setNameArq(posicaoProg, newName);

    output(2, 9999);
    output(2, nameArq(posicaoProg));

    return 1;
}

int findEmpty(void){
    int i;
    i = 0;
    while(i < 16){
        if(statusArq(i)==0)
            return i;
        i = i + 1;
    }
    return 0-1;
}

int createProg(void){
    int empty;
    int name;
    int qntLinhas;
    int i;
    i = 0;

    empty = findEmpty();
    output(2, empty);

    name = input();
    setNameArq(empty, name);

    qntLinhas = input();
    ativProg(empty);

    while (i < qntLinhas){
        readInstruction(empty, i);
        copyToMem(empty, i);
        i = i + 1;
    }

    return 1;
}

int deleteProg(void){
    int nameprog;
    int posicaoProg;

    nameprog = input();
    posicaoProg = findProg(nameprog);
    output(2, posicaoProg);

    delProg(posicaoProg);

    return 1;
}

void main(void){
    int type;
    tamanhoPilha =  200;
    tamanhoMemProg = 700;
    type = input();
    while(type > 0){
        if (type == 1){         /* Executar um Programa*/
            execUmProg();
        } else if (type == 2){  /* Executar N  Programas*/
            execNProg();
        } else if (type == 3){  /* Renomear um Programa */
            renameProg();
        } else if (type == 4){  /* Criar um Programa */
            createProg();
        } else if (type == 5){  /* Deletar um Programa */
            deleteProg();
        } else{  /* Opção Inválida */
            output(2, 0-1);
        }
        type = input(); /* faca enquanto */
    }
    return;
}