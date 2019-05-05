#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char *file;
char label[100][20];
int nlabel[100];
int x =0;
int base = 2500;
int deslocamento = 500;
int prog = 4; //0 - SO


void decBin(int n, int t){		//n - numero  e t - qnt de digitos
	int c, k;
	for (c = t-1; c >= 0; c--){
		k = n >> c;

		if (k & 1)
		  printf("1");
		else
		  printf("0");
	}
}

void converte(char *inst, char *op){
	char *op1 = strtok(op, ",");
	char *op2 = strtok(NULL, ",");
	char *op3 = strtok(NULL, ",");
	//printf("%s %s %s\n", op1,op2,op3);

	if(verificaLabel(op1)!=-1)		sprintf(op1, "%d", verificaLabel(op1));
	if(verificaLabel(op2)!=-1)		sprintf(op2, "%d", verificaLabel(op2));
	if(verificaLabel(op3)!=-1)		sprintf(op3, "%d", verificaLabel(op3));
	
	printf("\t\t\thd[%d] = 32'b",base*(prog!=0)+prog*deslocamento+x+100*(prog==0));

	if(strcmp(inst, "LABEL")==0){		//NOP
		decBin(0, 32);
	}
	else if(strcmp(inst, "J")==0){		//Tipo J
		printf("010100_");
		decBin(atoi(op1)+base*(prog!=0)+deslocamento*prog, 26);
	}
	else if(strcmp(inst, "JR")==0){		//Tipo R
		printf("010011_");
		decBin(atoi(op1), 5);
		printf("_");
		decBin(0, 5);
		printf("_");
		decBin(0, 5);
		printf("_");
		decBin(0, 11);
	}
	else if(strcmp(inst, "JAL")==0){	//Tipo I
		printf("010101_");
		decBin(atoi(op1)+base*(prog!=0)+deslocamento*prog, 26);
	}
	else if(strcmp(inst, "LOADI")==0){	//Tipo I
		printf("011011_");
		decBin(0, 5);
		printf("_");
		decBin(atoi(op1), 5);
		printf("_");
		decBin(atoi(op2), 16);
	}
	else if(strcmp(inst, "LOADIR")==0){	//Tipo I
		printf("011011_");
		decBin(0, 5);
		printf("_");
		decBin(atoi(op1), 5);
		printf("_");
		decBin(atoi(op2)+base*(prog!=0)+deslocamento*prog, 16);
	}
	else if(strcmp(inst, "ADD")==0){	//Tipo R
		printf("000001_");
		decBin(atoi(op2), 5);
		printf("_");
		decBin(atoi(op3), 5);
		printf("_");
		decBin(atoi(op1), 5);
		printf("_");
		decBin(0, 11);
	}
	else if(strcmp(inst, "ADDU")==0){	//Tipo R
		printf("100111_");
		decBin(atoi(op2), 5);
		printf("_");
		decBin(atoi(op3), 5);
		printf("_");
		decBin(atoi(op1), 5);
		printf("_");
		decBin(0, 11);
	}
	else if(strcmp(inst, "SUB")==0){	//Tipo R
		printf("000011_");
		decBin(atoi(op2), 5);
		printf("_");
		decBin(atoi(op3), 5);
		printf("_");
		decBin(atoi(op1), 5);
		printf("_");
		decBin(0, 11);
	}
	else if(strcmp(inst, "MULT")==0){	//Tipo R
		printf("000101_");
		decBin(atoi(op2), 5);
		printf("_");
		decBin(atoi(op3), 5);
		printf("_");
		decBin(atoi(op1), 5);
		printf("_");
		decBin(0, 11);
	}
	else if(strcmp(inst, "DIV")==0){	//Tipo R
		printf("000110_");
		decBin(atoi(op2), 5);
		printf("_");
		decBin(atoi(op3), 5);
		printf("_");
		decBin(atoi(op1), 5);
		printf("_");
		decBin(0, 11);
	}
	else if(strcmp(inst, "ADDI")==0){ 	//Tipo I
		printf("000010_");
		decBin(atoi(op2), 5);	
		printf("_");
		decBin(atoi(op1), 5);		//Reg destino
		printf("_");
		decBin(atoi(op3), 16);
	}
	else if(strcmp(inst, "SUBI")==0){ 	//Tipo I
		printf("000100_");
		decBin(atoi(op2), 5);	
		printf("_");
		decBin(atoi(op1), 5);		//Reg destino
		printf("_");
		decBin(atoi(op3), 16);
	}
	else if(strcmp(inst, "SGT")==0){	//Tipo R
		printf("010111_");
		decBin(atoi(op2), 5);
		printf("_");
		decBin(atoi(op3), 5);
		printf("_");
		decBin(atoi(op1), 5);
		printf("_");
		decBin(0, 11);
	}
	else if(strcmp(inst, "SLT")==0){	//Tipo R
		printf("010110_");
		decBin(atoi(op2), 5);
		printf("_");
		decBin(atoi(op3), 5);
		printf("_");
		decBin(atoi(op1), 5);
		printf("_");
		decBin(0, 11);
	}
	else if(strcmp(inst, "SET")==0){	//Tipo R
		printf("011000_");
		decBin(atoi(op2), 5);
		printf("_");
		decBin(atoi(op3), 5);
		printf("_");
		decBin(atoi(op1), 5);
		printf("_");
		decBin(0, 11);
	}
	else if(strcmp(inst, "BEQ")==0){	//Tipo I
		printf("010000_");
		decBin(atoi(op1), 5);
		printf("_");
		decBin(atoi(op2), 5);
		printf("_");
		decBin(atoi(op3)+base*(prog!=0)+deslocamento*prog, 16);
	}
	else if(strcmp(inst, "BNE")==0){	//Tipo I
		printf("010001_");
		decBin(atoi(op1), 5);
		printf("_");
		decBin(atoi(op2), 5);
		printf("_");
		decBin(atoi(op3)+base*(prog!=0)+deslocamento*prog, 16);
	}
	else if(strcmp(inst, "OUT")==0){	//Tipo I
		printf("100000_");
		decBin(0, 5);
		printf("_");
		decBin(atoi(op2), 5);
		printf("_");
		decBin(atoi(op1), 16);
	}
	else if(strcmp(inst, "IN")==0){		//Tipo I
		printf("011111_");
		decBin(0, 5);
		printf("_");
		decBin(atoi(op1), 5);
		printf("_");
		decBin(0, 16);
	}
	else if(strcmp(inst, "LOAD")==0){		//Tipo I
		printf("011001_");
		decBin(atoi(op3), 5);
		printf("_");
		decBin(atoi(op1), 5);
		printf("_");
		decBin(atoi(op2), 16);
	}
	else if(strcmp(inst, "STORE")==0){		//Tipo I
		printf("011010_");
		decBin(atoi(op3), 5);
		printf("_");
		decBin(atoi(op1), 5);
		printf("_");
		decBin(atoi(op2), 16);
	}
	else if(strcmp(inst, "HALT")==0){
		printf("111111_");
		decBin(0, 26);
	}
	else if(strcmp(inst, "NOOP")==0){
		printf("000000_");
		decBin(0, 26);
	}
	else if(strcmp(inst, "LOADFT")==0){	//Tipo R
		printf("100010_");
		decBin(atoi(op2), 5);
		printf("_");
		decBin(atoi(op3), 5);
		printf("_");
		decBin(atoi(op1), 5);
		printf("_");
		decBin(0, 11);
	}
	else if(strcmp(inst, "MOVE")==0){		//Tipo I
		printf("011101_");
		decBin(atoi(op2), 5);
		printf("_");
		decBin(atoi(op1), 5);
		printf("_");
		decBin(0, 16);
	}
	else if(strcmp(inst, "JALR")==0){ 	//Tipo I
		printf("100110_");
		decBin(atoi(op2), 5);	
		printf("_");
		decBin(atoi(op1), 5);		//Reg destino
		printf("_");
		decBin(0, 16);
	}
	else if(strcmp(inst, "STOREHD")==0){	//Tipo R
		printf("100100_");
		decBin(atoi(op3), 5);
		printf("_");
		decBin(atoi(op2), 5);
		printf("_");
		decBin(atoi(op1), 5);
		printf("_");
		decBin(0, 11);
	}
	else if(strcmp(inst, "CPHM")==0){	//Tipo R
		printf("100011_");
		decBin(atoi(op3), 5);
		printf("_");
		decBin(atoi(op2), 5);
		printf("_");
		decBin(atoi(op1), 5);
		printf("_");
		decBin(0, 11);
	}
	else if(strcmp(inst, "CPHFT")==0){	//Tipo R
		printf("100001_");
		decBin(atoi(op3), 5);
		printf("_");
		decBin(atoi(op2), 5);
		printf("_");
		decBin(atoi(op1), 5);
		printf("_");
		decBin(0, 11);
	}
	printf(";");
	x++;
}
	
int verificaLabel(char *op){
	if(op == NULL) return -1;
	int i = 0;

	while(strcmp(label[i], "NULL")!=0){
		if(strcmp(label[i], op)==0) return nlabel[i];
		//printf("\n%s %s\n", label[i], op);
		i++;
	}
	return -1;
}

int encontraLabel(){
	FILE *fd;
	char buffer[100];
	int i=0, j=0;
	char *inst2 = NULL;
	char *op2 =NULL;
	//printf("Teste\n");
	fd = fopen(file, "r+");
	while(!feof(fd)){
		bzero(buffer, 100);
		fgets(buffer, 100, fd);

		//printf("Teste2\n");
		strtok(buffer, " ");
		inst2 = strtok(NULL," ");
		op2 = strtok(NULL," ");
		
		if(inst2!=NULL && strcmp(inst2, "LABEL")==0){
			strcpy(label[j], op2);
			nlabel[j] = i;
			j++;
		}
		i++;
	}
	strcpy(label[j], "NULL");
	return 0;
}


int main(int argv, char **argc){

	char **matrix = NULL;
	FILE *fd;
	char buffer[100];
	char *inst = NULL;
	char *op =NULL, op2[30];
	int i=0;
	file = argc[1];
	for(i=0; i<100; i++) bzero(label[i], 20);

	encontraLabel();

	if((fd = fopen(file, "r+"))==NULL){
		perror("open error");
		return 0;
	}
	while(!feof(fd)){
		bzero(buffer, 100);
		fgets(buffer, 100, fd);

		strtok(buffer, " ");
		inst = strtok(NULL," ");
		op = strtok(NULL," ");
		if(inst==NULL) break;

		strcpy(op2, op);
		converte(inst, op);
		printf("\t\t//%s\t%s\n",inst, op2);
	}

	i = 0;
	/*while(strcmp(label[i], "NULL")!=0){
		printf("%s %d\n", label[i], nlabel[i]);
		i++;
	}*/


	return 0;
}