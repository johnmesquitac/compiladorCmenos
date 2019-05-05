
#include "globals.h"
#include "symtab.h"
#include "code.h"
#include "cgen.h"


/*Para apenas os programas */
#define  ac 1
#define  ac1 2
#define  ac2 3
int r_pilha = 12; 
int r_EscopGlobal = 13;   
int r_EscopAtual = 14;   
int r_ra = 16;


/*Para apenas o SO*/
//#define  ac 21
//#define  ac1 22
//#define  ac2 23
//int r_pilha = 26; 
//int r_EscopGlobal = 27;   
//int r_EscopAtual = 28;   
//int r_ra = 30;

//Para SO e programas
int r_retornoProg = 10;
int r_pcAtual = 11;
int r_MemProgAtual = 15;  
int r_nprogAtual = 24;
int r_retornoSO = 25;
int preemcao = 29;


int tamEscopo = 0;
int nif = 0;
int nwhile = 0;
char teste[50];

int call = 0;

/* prototype for internal recursive code generator */
static void cGen (TreeNode * tree);

/* Procedure genStmt generates code at a statement node */
static void genStmt( TreeNode * tree)
{ 
  //printf("Node Stmt\n");
  TreeNode * p1, * p2, * p3;
  int savedLoc1,savedLoc2,currentLoc;
  int loc;
  int nifLoc = nif;
  int nwhileLoc = nwhile;
  switch (tree->kind.stmt) {

      case IfK :
         if (TraceCode) emitComment("-> if") ;
         p1 = tree->child[0] ;
         p2 = tree->child[1] ;
         p3 = tree->child[2] ;
         /* generate code for test expression */
         nif++;
         cGen(p1);
         bzero(teste, 50);
         sprintf(teste, "_Else%d", nifLoc);
         emitI2("LOADI",0,0,"Inicializa o registrador zero");
         emitIL("BEQ",ac,0,teste,"Se for falso - vai para Else");

         cGen(p2);
         bzero(teste, 50);
         sprintf(teste, "_Fim_If%d", nifLoc);
         emitJL("J",teste,"Vai para Fim_If");

         bzero(teste, 50);
         sprintf(teste, "_Else%d", nifLoc);
         emitLabel(teste);
         cGen(p3);

         bzero(teste, 50);
         sprintf(teste, "_Fim_If%d", nifLoc);
         emitLabel(teste);

         if (TraceCode)  emitComment("<- if");
         break; /* if_k */

      case WhileK:
         if (TraceCode) emitComment("-> while") ;
         p1 = tree->child[0] ;
         p2 = tree->child[1] ;
         savedLoc1 = emitSkip(0);
         emitComment("repeat: jump after body comes back here");
         /* generate code for test */
         nwhile++;

         cGen(p1);
         bzero(teste, 50);
         sprintf(teste, "_Fim_While%d", nwhileLoc);
         emitI2("LOADI",0,0,"Inicializa o registrador zero");
         emitIL("BEQ",ac,0,teste,"Se for falso - vai para o fim_while");
         //emitI2("OUT",1,ac,"Mostra ");
         /* generate code for body */
         cGen(p2);
         emitJ("J",savedLoc1,"Volta para o inicio do while");
         //emitRM_Abs("JEQ",ac,savedLoc1,"repeat: jmp back to body");
         bzero(teste, 50);
         sprintf(teste, "_Fim_While%d", nwhileLoc);
         emitLabel(teste);
         
         if (TraceCode)  emitComment("<- while") ;
         break; /* repeat */

      case ReturnK:
          if (TraceCode) emitComment("-> return") ;
          p1 = tree->child[0] ;
          cGen(p1);
          emitRM("STORE",ac,0,r_EscopAtual,"Salva valor do retorno na memória");
          emitI1("JR",r_ra,"Volta para onde foi chamado");
          if (TraceCode) emitComment("<- return") ;
          break;
      default:
         break;
    }
} /* genStmt */

/* Procedure genExp generates code at an expression node */
static void genExp( TreeNode * tree)
{ int loc;
  int i = 0;
  TreeNode * p1, * p2;
  //printf("Node Exp\n");
  switch (tree->kind.exp) {

    case AtribK:
       if (TraceCode) emitComment("-> assign") ;
       /* generate code for rhs */
       cGen(tree->child[1]);
       /* now store value */
       tree = tree->child[0];
       loc = st_lookup(tree->attr.name, tree->scope);
       if(strcmp(st_lookup_typeId(tree->attr.name, tree->scope), "variable")==0){
         if(strcmp(tree->scope, "global") == 0)
            emitRM("STORE",ac,loc,r_EscopGlobal,"assign: store value");
          else
            emitRM("STORE",ac,loc,r_EscopAtual,"assign: store value");
       }
       else if(tree->kind.exp == PointerK){
          p1 = tree->child[0];
          emitRM("STORE",ac,0,r_pilha,"op: push left");
          emitI3("SUBI", r_pilha, r_pilha, 1, "Deslocamento r_pilha");
           
          cGen(p1);
           /* now load left operand */
          emitI3("ADDI", r_pilha, r_pilha, 1, "Deslocamento r_pilha");
          emitRM("LOAD",ac1,0,r_pilha,"op: load left");

          emitRM("LOAD", ac2,loc,r_EscopAtual,"load id value");
          emitRO("ADD", ac2,ac, ac2,"Deslocamento do vetor para a posição da expressão");

          emitRM("STORE",ac1,0, ac2,"assign: store value");          
       }
       else {
          p1 = tree->child[0];
          emitRM("STORE",ac,0,r_pilha,"op: push left");
          emitI3("SUBI", r_pilha, r_pilha, 1, "Deslocamento r_pilha");
           
          cGen(p1);
           /* now load left operand */
          emitI3("ADDI", r_pilha, r_pilha, 1, "Deslocamento r_pilha");
          emitRM("LOAD",ac1,0,r_pilha,"op: load left");
          if(strcmp(tree->scope, "global") == 0)
            emitI3("ADD", ac2, ac, r_EscopGlobal, "Deslocamento do vetor para a posição da expressão");
          else
            emitRO("ADD", ac2,ac,r_EscopAtual,"Deslocamento do vetor para a posição da expressão");
          emitRM("STORE",ac1,loc, ac2,"assign: store value");

       }
       if (TraceCode)  emitComment("<- assign") ;
       break; /* AtribK */

    case LiteralK :
        if (TraceCode) emitComment("-> Literal") ;
        /* gen code to load integer constant using LDC */
        emitI2("LOADI",ac,tree->attr.val,"loadi variable");
        if (TraceCode)  emitComment("<- Literal") ;
        break; /* LiteralK */
    
    case IdK :
        if (TraceCode) emitComment("-> Id") ;
        loc = st_lookup(tree->attr.name, tree->scope);
        if(strcmp(tree->scope, "global") == 0)
          emitRM("LOAD",ac,loc,r_EscopGlobal,"load id value");
        else
          emitRM("LOAD",ac,loc,r_EscopAtual,"load id value");
        if (TraceCode)  emitComment("<- Id") ;
        break; /* IdK */
    
    case IdVectorK:
        if (TraceCode) emitComment("-> IdVector") ;
        loc = st_lookup(tree->attr.name, tree->scope);
        p1 = tree->child[0];
        cGen(p1);
        if(strcmp(tree->scope, "global") == 0)
          emitI3("ADD", ac2, ac, r_EscopGlobal, "Deslocamento do vetor para a posição da expressão");
        else
          emitRO("ADD", ac2,ac,r_EscopAtual,"Deslocamento do vetor para a posição da expressão");
        emitRM("LOAD",ac,loc, ac2,"load id value");
        if (TraceCode)  emitComment("<- IdVector") ;
        break; /* IdVectorK */

    case ParamVectorK:
        if (TraceCode) emitComment("-> ParamVector") ;
        /* gen code to load integer constant using LDC */
        loc = st_lookup(tree->attr.name, tree->scope);
        if(strcmp(tree->scope, "global") == 0)
          emitI3("ADDI", ac, r_EscopGlobal, loc, "Salvando o endereço do vetor no ac");
        else
          emitI3("ADDI", ac, r_EscopAtual, loc, "Salvando o endereço do vetor no ac");

        //if (TraceCode)  emitComment("<- ParamVector") ;
        break; /* ParamVectorK */

    case ParamPointerK:
          loc = st_lookup(tree->attr.name, tree->scope);
          emitRM("LOAD",ac,loc,r_EscopAtual,"load id value");
          break;

    case PointerK:
        if (TraceCode) emitComment("-> Pointer") ;
        p1 = tree->child[0];
        cGen(p1);
        loc = st_lookup(tree->attr.name, tree->scope);
        /*if(strcmp(tree->scope, "global") == 0){
          emitRM("LOAD", ac2,ac,r_EscopGlobal,"load id value");
          emitRM("LOAD",ac,loc, ac2,"load id value");
        }
        else{*/

          emitRM("LOAD", ac2,loc,r_EscopAtual,"load id value");
          emitRO("ADD", ac2,ac, ac2,"Deslocamento do vetor para a posição da expressão");
          emitRM("LOAD",ac,0, ac2,"load id value");
        //}
        if (TraceCode)  emitComment("<- Pointer") ;
        break;

    case VectorK:
        //Não faz nada
        break;

    case VariableK:
        //Não faz nada
        break;

    case TypeK:
        p1 = tree->child[0];
        cGen(p1);
        break;
 
    case FunctionK:
        if (TraceCode) emitComment("-> Function") ;
        emitLabel(tree->attr.name);
        //r_EscopAtual = st_lookup(tree->attr.name, "");
        tamEscopo = st_lookup_tam(tree->attr.name);
        
        while(tree->child[i] != NULL){
            cGen(tree->child[i++]);
        }
        emitI1("JR",r_ra,"Volta para onde foi chamado");
        if (TraceCode) emitComment("<- Function") ;
        break;

    case CallK:
        call = 1;
        if (TraceCode) emitComment("-> Call") ;
        
        if(strcmp(tree->attr.name, "output")==0){
            p1 = tree->child[0]->sibling;
            /* gen code for ac = left arg */
            cGen(p1);

            emitI2("OUT",tree->child[0]->attr.val,ac,"Mostra o valor do Registrador ac na saída p1");
            emitNoop("");
            emitNoop("");
        }
        else if(strcmp(tree->attr.name, "input")==0){

            emitI1("IN",ac,"Salva o valor de entrada no registrador ac");
            emitNoop("");
            emitNoop("");
        }
        else if(strcmp(tree->attr.name, "nameArq")==0){
            p1 = tree->child[0];
            cGen(p1);
            emitI2("LOADI",ac2,5,"Inicializa o registrador zero");
            emitRO("MULT",ac,ac2,ac,"");
            emitRO("LOADFT",ac,0,ac,"");
        }
        else if(strcmp(tree->attr.name, "delProg")==0){
            p1 = tree->child[0];
            cGen(p1);
            emitI2("LOADI",ac2,5,"Inicializa o registrador zero");
            emitRO("MULT",ac,ac2,ac,"");
            emitI3("ADDI", ac, ac, 3, "");
            emitRO("STOREHD",0,0,ac,"");
            emitRO("CPHFT",ac, 0, ac, "");
        }
        else if(strcmp(tree->attr.name, "ativProg")==0){
            p1 = tree->child[0];
            cGen(p1);
            emitI2("LOADI",ac2,5,"");
            emitI2("LOADI",ac1,1,"");
            emitRO("MULT",ac,ac2,ac,"");
            emitI3("ADDI", ac, ac, 3, "");
            emitRO("STOREHD",ac1,0,ac,"");
            emitRO("CPHFT",ac, 0, ac, "");
        }
        else if(strcmp(tree->attr.name, "statusArq")==0){
            p1 = tree->child[0];
            cGen(p1);
            emitI2("LOADI",ac2,5,"Inicializa o registrador zero");
            emitRO("MULT",ac,ac2,ac,"");
            emitI3("ADDI", ac, ac, 3, "");
            emitRO("LOADFT",ac,0,ac,"");
        }
        else if(strcmp(tree->attr.name, "get_nprogAtual")==0){

            emitI2("MOVE",ac,r_nprogAtual,"Pega o numero do programa atual");
        }
        else if(strcmp(tree->attr.name, "get_MemProgAtual")==0){

            emitI2("MOVE",ac,r_MemProgAtual,"Pega a base da memória do programa atual");
        }
        else if(strcmp(tree->attr.name, "set_MemProgAtual")==0){
            p1 = tree->child[0];
            cGen(p1);
            emitI2("MOVE",r_MemProgAtual,ac,"Pega a base da memória do programa atual");
        }
        else if(strcmp(tree->attr.name, "set_nprogAtual")==0){
            p1 = tree->child[0];
            cGen(p1);
            emitI2("MOVE",r_nprogAtual,ac,"Pega a base da memória do programa atual");
        }
        else if(strcmp(tree->attr.name, "set_prog")==0){
            emitRM("STORE",r_ra,0,r_pilha,"ra é armazenado na memória");
            emitI3("SUBI", r_pilha, r_pilha, 1, "mudança de base de memória");

            p1 = tree->child[0];
            cGen(p1);

            emitI2("LOADI",ac1,500,"");
            emitRO("MULT",ac,ac1,ac,"Localiza na memInst o programa");
            emitI3("ADDI", ac, ac, 2500, "mudança de base de memória");
            //emitI2("OUT",2,ac,"");
            emitI2("JALR",r_retornoSO,ac,"Vai para o programa selecionado");
        }
        else if(strcmp(tree->attr.name, "set_progBack")==0){

            emitRM("STORE",r_ra,0,r_pilha,"ra é armazenado na memória");
            emitI3("SUBI", r_pilha, r_pilha, 1, "mudança de base de memória");

            emitI3("ADDI", r_retornoProg, r_retornoProg, 1, "mudança de base de memória");
            emitI2("JALR",r_retornoSO,r_retornoProg,"Vai para o programa selecionado");
        }
        else if(strcmp(tree->attr.name, "regToMem")==0){
            p1 = tree->child[0]->sibling;
            cGen(p1);
            
            emitRM("STORE",tree->child[0]->attr.val ,0,ac,"Salvando Registradores");
        }
        else if(strcmp(tree->attr.name, "memToReg")==0){
           
            p1 = tree->child[0]->sibling;
            cGen(p1);
            
            emitRM("LOAD",tree->child[0]->attr.val,0,ac,"Salvando Registradores");
        }
        else if(strcmp(tree->attr.name, "set_SO")==0){

            emitI2("LOADI",ac,700,"");
            emitRO("MULT",r_MemProgAtual,r_nprogAtual,ac,"Seta a base da memória para esse programa");

            emitI3("ADDI", r_pilha, r_pilha, 1, "mudança de base de memória");
            emitRM("LOAD",r_ra,0,r_pilha,"ra recebe o PC antigo");
        }
        else if(strcmp(tree->attr.name, "showReg")==0){

            emitI2("OUT",2,tree->child[0]->attr.val,"Mostra o valor do Registrador ac na saída p1");
        }
        else if(strcmp(tree->attr.name, "setNameArq")==0){

            p1 = tree->child[0];
            p2 = tree->child[0]->sibling;

            cGen(p1);

            emitRM("STORE",ac,0,r_pilha,"op: push left");
            emitI3("SUBI", r_pilha, r_pilha, 1, "Deslocamento r_pilha");

            cGen(p2);

            emitI3("ADDI", r_pilha, r_pilha, 1, "Deslocamento r_pilha");
            emitRM("LOAD",ac1,0,r_pilha,"op: load left");
            
            emitI2("LOADI",ac2,5,"");
            emitRO("MULT",ac1,ac2,ac1,"");
            emitRO("STOREHD",ac,0,ac1,"");
            emitRO("CPHFT",ac1, 0, ac1, "");
        }
        else if(strcmp(tree->attr.name, "setPreempcao")==0){
            p1 = tree->child[0];
            cGen(p1);
            emitI2("MOVE",preemcao,ac,"Pega a base da memória do programa atual");
        }
        else if(strcmp(tree->attr.name, "copyToMem")==0){
            p1 = tree->child[0];            //posição -1
            p2 = tree->child[0]->sibling;   //indice

            cGen(p1);

            emitRM("STORE",ac,0,r_pilha,"op: push left");
            emitI3("SUBI", r_pilha, r_pilha, 1, "Deslocamento r_pilha");

            cGen(p2);

            emitI3("ADDI", r_pilha, r_pilha, 1, "Deslocamento r_pilha");
            emitRM("LOAD",ac1,0,r_pilha,"op: load left");            

            emitI3("ADDI", ac1, ac1, 1, "");


            emitI2("LOADI",ac2,500,"");
            emitRO("MULT",ac2,ac2,ac1,"");
            emitI3("ADDI",ac2, ac2, 2000, "");
            emitRO("ADD", ac2,ac2,ac,"");

            emitRO("CPHM",ac2, ac1, ac, "");
        }
        else if(strcmp(tree->attr.name, "readInstruction")==0){
            p1 = tree->child[0];            //programa -1
            p2 = tree->child[0]->sibling;   //indice

            emitI1("IN",ac,"Salva o valor de entrada no registrador ac");   //Parte superior
            emitI1("IN",ac1,"Salva o valor de entrada no registrador ac");  //Parte inferior
            emitRO("ADDU",ac2,ac1,ac,"op");
            emitI2("OUT",2,ac2,"");

            cGen(p1);

            emitRM("STORE",ac,0,r_pilha,"op: push left");
            emitI3("SUBI", r_pilha, r_pilha, 1, "Deslocamento r_pilha");

            cGen(p2);

            emitI3("ADDI", r_pilha, r_pilha, 1, "Deslocamento r_pilha");
            emitRM("LOAD",ac1,0,r_pilha,"op: load left");            

            emitI3("ADDI", ac1, ac1, 1, "");
            emitI2("OUT",2,ac1,"");

            emitRO("STOREHD",ac2,ac1,ac,"");
        }

        else{
            emitRM("STORE",r_ra,0,r_pilha,"ra é armazenado na memória");
            emitI3("SUBI", r_pilha, r_pilha, 1, "mudança de base de memória");
            TreeNode * aux;
            aux = tree->child[0];
            while(aux != NULL){
                cGen(aux);
                emitI3("ADDI", r_EscopAtual, r_EscopAtual, tamEscopo, "mudança de base de memória");
                emitRM("STORE",ac,++i,r_EscopAtual,"Passagem de parametro");
                emitI3("SUBI", r_EscopAtual, r_EscopAtual, tamEscopo, "voltando a base antiga de memória");
                aux = aux->sibling;
            }
            emitI3("ADDI", r_EscopAtual, r_EscopAtual, tamEscopo, "mudança de base de memória");
            emitJL("JAL", tree->attr.name, "");
            emitI3("ADDI", r_pilha, r_pilha, 1, "mudança de base de memória");
            emitRM("LOAD",r_ra,0,r_pilha,"ra recebe o PC antigo");
            emitRM("LOAD",ac, 0, r_EscopAtual, "Colocando o retorno no registrador ac (redundante)");
            emitI3("SUBI", r_EscopAtual, r_EscopAtual, tamEscopo, "voltando a base antiga de memória");
        }
        if (TraceCode) emitComment("<- Call") ;
        call = 0;
        break;

    case OpK :
         if (TraceCode) emitComment("-> Op") ;
         p1 = tree->child[0];
         p2 = tree->child[1];
         /* gen code for ac = left arg */
         cGen(p1);
         /* gen code to push left operand */
         //emitRM("STORE",ac,tmpOffset--,r_pilha,"op: push left");
         emitRM("STORE",ac,0,r_pilha,"op: push left");
         emitI3("SUBI", r_pilha, r_pilha, 1, "Deslocamento r_pilha");
         /* gen code for ac = right operand */
         cGen(p2);
         /* now load left operand */
         emitI3("ADDI", r_pilha, r_pilha, 1, "Deslocamento r_pilha");
         emitRM("LOAD",ac1,0,r_pilha,"op: load left");

         switch (tree->op) {
            case PLUS :
               emitRO("ADD",ac,ac1,ac,"op +");
               break;
            case MINUS :
               emitRO("SUB",ac,ac1,ac,"op -");
               break;
            case TIMES :
               emitRO("MULT",ac,ac1,ac,"op *");
               break;
            case OVER :
               emitRO("DIV",ac,ac1,ac,"op /");
               break;
            default:
               emitComment("BUG: Unknown operator");
               break;
         } /* case op */
         if (TraceCode)  emitComment("<- Op") ;
         break; /* OpK */

    case RelK :
         if (TraceCode) emitComment("-> Rel") ;
         p1 = tree->child[0];
         p2 = tree->child[1];
         /* gen code for ac = left arg */
         cGen(p1);
         /* gen code to push left operand */
         emitRM("STORE",ac,0,r_pilha,"op: push left");
         emitI3("SUBI", r_pilha, r_pilha, 1, "Deslocamento r_pilha");
         /* gen code for ac = right operand */
         cGen(p2);
         /* now load left operand */
         emitI3("ADDI", r_pilha, r_pilha, 1, "Deslocamento r_pilha");
         emitRM("LOAD",ac1,0,r_pilha,"op: load left");

         switch (tree->op) {
            case LT :   //<
               /*emitRO("SUB",ac,ac1,ac,"op <") ;
               emitRM("JLT",ac,2,pc,"br if true") ;
               emitRM("LDC",ac,0,ac,"false case") ;
               emitRM("LDA",pc,1,pc,"unconditional jmp") ;
               emitRM("LDC",ac,1,ac,"true case") ;*/

               emitRO("SLT",ac,ac1,ac,"");
               break;
            case LTEQ : //<=

               emitRO("SGT",ac,ac,ac1,"");
               break;
            case EQ :   //==
               /*emitRO("SUB",ac,ac1,ac,"op ==") ;
               emitRM("JEQ",ac,2,pc,"br if true");
               emitRM("LDC",ac,0,ac,"false case") ;
               emitRM("LDA",pc,1,pc,"unconditional jmp") ;
               emitRM("LDC",ac,1,ac,"true case") ;*/

               emitRO("SET",ac,ac1,ac,"");
               break;
            case NEQ :   //<>
               emitRO("SET",ac,ac1,ac,"");
               emitI2("LOADI",0,0,"Inicializa o registrador zero");
               emitRO("SET",ac,0,ac,"");
               break;
            case GT :   //>

               //emitI2("OUT",0,ac1,"Mostra ");
               emitRO("SGT",ac,ac1,ac,"");
               //emitI2("OUT",0,ac,"Mostra ");

               break;
            case GTEQ : //>=

               emitRO("SLT",ac,ac,ac1,"");
               break;
            default:
               emitComment("BUG: Unknown relacional");
               break;
         } /* case op */
         if (TraceCode)  emitComment("<- Rel") ;
         break; /* RelK */
    default:
      break;
  }
} /* genExp */

/* Procedure cGen recursively generates code by
 * tree traversal
 */
static void cGen( TreeNode * tree){ 
  if (tree != NULL)
  { 
    switch (tree->nodekind) {
      case StmtK:
        //printf("Denis Stmtk\n");
        genStmt(tree);
        break;
      case ExpK:
        //printf("Denis Expk\n");
        genExp(tree);
        break;
      default:
        //printf("default\n");
        break;
    }

    if(call != 1) cGen(tree->sibling);
  }
}

/**********************************************/
/* the primary function of the code generator */
/**********************************************/
/* Procedure codeGen generates code to a code
 * file by traversal of the syntax tree. The
 * second parameter (codefile) is the file name
 * of the code file, and is used to print the
 * file name as a comment in the code file
 */
void codeGen(TreeNode * syntaxTree, char * codefile)
{  
   char * s = malloc(strlen(codefile)+7);
   strcpy(s,"File: ");
   strcat(s,codefile);
   emitComment("CMINUS Compilation to TM Code");
   emitComment(s);
     /* generate standard prelude */
   emitComment("Standard prelude:");
   //emitI2("OUT",2,r_nprogAtual,"Mostra o valor do Registrador ac na saída p1");
   emitI2("LOADI",ac,700,"");
   emitRO("MULT",r_MemProgAtual,r_nprogAtual,ac,"Seta a base da memória para esse programa");
   //emitI2("OUT",2,r_MemProgAtual,"Mostra o valor do Registrador ac na saída p1");

   emitI2("LOADI",r_pilha,mp,"Inicializa o registrador que controla a r_pilha");
   emitRO("ADD",r_pilha,r_MemProgAtual,r_pilha,"Deslocamento da Mem de acordo com o programa");
   tamEscopo = st_lookup_tam("global");
   emitI2("LOADI",r_EscopAtual,mp+21+tamEscopo,"Inicializa o registrador que controla a memória");
   emitRO("ADD",r_EscopAtual,r_MemProgAtual,r_EscopAtual,"Deslocamento da Mem de acordo com o programa");
   emitI2("LOADI",r_EscopGlobal,mp+21,"Inicializa o registrador que controla a memória");
   emitRO("ADD",r_EscopGlobal,r_MemProgAtual,r_EscopGlobal,"");
   emitI2("LOADI",0,0,"Inicializa o registrador zero");
   emitI2L("LOADIR",r_ra,"_Fim","Inicializa o registrador r_ra com o endereço do final do programa");
   emitJL("J","main","Vai para Main");
   emitComment("End of standard prelude.");
   /* generate code for TINY program */
   cGen(syntaxTree);
   /* finish */
   emitLabel("_Fim");
   emitComment("End of execution.");
   //emitI2("OUT",2,r_retornoSO,"");
   if(ac == 1) emitI1("JR",r_retornoSO,"Volta para onde foi chamado no SO"); //Se programa
   emitNoop("");
   if(ac == 1) emitI1("JR",r_retornoSO,"Volta para onde foi chamado no SO"); //Se programa
   emitNoop("");
   emitHalt("");    //Se SO
}