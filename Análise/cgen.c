
#include "globals.h"
#include "symtab.h"
#include "code.h"
#include "cgen.h"

/* tmpOffset is the memory offset for temps
   It is decremented each time a temp is
   stored, and incremeted when loaded again
*/
static int tmpOffset = 0; //Ponteiro da Pilha "mp" que começa na posição 99 da memória e decresce até o 0
int pilha = 29;            //Registrador que controla a posição inicial na memória da pilha - possui valor 99

int baseEscopo = 30; //Registrador que controla o endereço inicial da função na memória
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
  switch (tree->kind.stmt) {

      case IfK :
         if (TraceCode) emitComment("-> if") ;
         p1 = tree->child[0] ;
         p2 = tree->child[1] ;
         p3 = tree->child[2] ;
         /* generate code for test expression */
         cGen(p1);
         //savedLoc1 = emitSkip(1) ;
         //emitComment("if: jump to else belongs here");
         /* recurse on then part */
         bzero(teste, 50);
         sprintf(teste, "_Else%d", nif);
         emitIL("BEQ",ac,0,teste,"Se for falso - vai para Else");
         cGen(p2);
         /*savedLoc2 = emitSkip(1) ;
         emitComment("if: jump to end belongs here");
         currentLoc = emitSkip(0) ;
         emitBackup(savedLoc1) ;
         emitRM_Abs("JEQ",ac,currentLoc,"if: jmp to else");
         emitRestore() ;*/
         /* recurse on else part */
         bzero(teste, 50);
         sprintf(teste, "_Fim_If%d", nif);
         emitJL("J",teste,"Vai para Fim_If");

         bzero(teste, 50);
         sprintf(teste, "_Else%d", nif);
         emitLabel(teste);
         cGen(p3);
         /*currentLoc = emitSkip(0) ;
         emitBackup(savedLoc2) ;
         emitRM_Abs("LDA",pc,currentLoc,"jmp to end") ;
         emitRestore() ;*/

         bzero(teste, 50);
         sprintf(teste, "_Fim_If%d", nif);
         emitLabel(teste);
         nif++;
         if (TraceCode)  emitComment("<- if") ;
         break; /* if_k */

      case WhileK:
         if (TraceCode) emitComment("-> while") ;
         p1 = tree->child[0] ;
         p2 = tree->child[1] ;
         savedLoc1 = emitSkip(0);
         emitComment("repeat: jump after body comes back here");
         /* generate code for test */
         
         cGen(p1);
         bzero(teste, 50);
         sprintf(teste, "_Fim_While%d", nwhile);
         emitIL("BEQ",ac,0,teste,"Se for falso - vai para o fim_while");

         /* generate code for body */
         cGen(p2);
         emitJ("J",savedLoc1,"Volta para o inicio do while");
         //emitRM_Abs("JEQ",ac,savedLoc1,"repeat: jmp back to body");
         emitLabel(teste);
         nwhile++;
         if (TraceCode)  emitComment("<- while") ;
         break; /* repeat */

      case ReturnK:
          if (TraceCode) emitComment("-> return") ;
          p1 = tree->child[0] ;
          cGen(p1);
          emitRM("STORE",ac,0,baseEscopo,"Salva valor do retorno na memória");
          //emitI1("JR",31,"Volta para onde foi chamado");
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
       emitRM("STORE",ac,loc,baseEscopo,"assign: store value");
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
        emitRM("LOAD",ac,loc,baseEscopo,"load id value");
        if (TraceCode)  emitComment("<- Id") ;
        break; /* IdK */
    
    case IdVectorK:
        if (TraceCode) emitComment("-> IdVector") ;
        loc = st_lookup(tree->attr.name, tree->scope);
        emitRM("LOAD",ac,loc+tree->child[0]->attr.val,baseEscopo,"load id value");
        if (TraceCode)  emitComment("<- IdVector") ;
        break; /* IdVectorK */

    case ParamVectorK:
        if (TraceCode) emitComment("-> ParamVector") ;
        /* gen code to load integer constant using LDC */
        loc = st_lookup(tree->attr.name, tree->scope);
        emitI3("ADDI", ac, baseEscopo, loc, "Salvando o endereço do vetor no ac");
        //if (TraceCode)  emitComment("<- ParamVector") ;
        break; /* ParamVectorK */

    case PointerK:
        if (TraceCode) emitComment("-> Pointer") ;
        loc = st_lookup(tree->attr.name, tree->scope);
        emitRM("LOAD",3,loc,baseEscopo,"load id value");
        emitRM("LOAD",ac,tree->child[0]->attr.val,3,"load id value");
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
        //baseEscopo = st_lookup(tree->attr.name, "");
        tamEscopo = st_lookup_tam(tree->attr.name);
        
        while(tree->child[i] != NULL){
            cGen(tree->child[i++]);
        }
        emitI1("JR",31,"Volta para onde foi chamado");
        if (TraceCode) emitComment("<- Function") ;
        break;

    case CallK:
        call = 1;
        if (TraceCode) emitComment("-> Call") ;
        if(strcmp(tree->attr.name, "output")!=0 && strcmp(tree->attr.name, "input")!=0){
            emitRM("STORE",31,0,pilha,"ra é armazenado na memória");
            emitI3("SUBI", pilha, pilha, 1, "mudança de base de memória");
            TreeNode * aux;
            aux = tree->child[0];
            while(aux != NULL){
                cGen(aux);
                emitI3("ADDI", baseEscopo, baseEscopo, tamEscopo, "mudança de base de memória");
                emitRM("STORE",ac,++i,baseEscopo,"Passagem de parametro");
                emitI3("SUBI", baseEscopo, baseEscopo, tamEscopo, "voltando a base antiga de memória");
                aux = aux->sibling;
            }
            emitI3("ADDI", baseEscopo, baseEscopo, tamEscopo, "mudança de base de memória");
            emitJL("JAL", tree->attr.name, "");
            emitI3("ADDI", pilha, pilha, 1, "mudança de base de memória");
            emitRM("LOAD",31,0,pilha,"ra recebe o PC antigo");
            emitRM("LOAD",ac, 0, baseEscopo, "Colocando o retorno no registrador ac (redundante)");
            emitI3("SUBI", baseEscopo, baseEscopo, tamEscopo, "voltando a base antiga de memória");
        }
        else if(strcmp(tree->attr.name, "output")==0){
            p1 = tree->child[0]->sibling;
            /* gen code for ac = left arg */
            cGen(p1);

            emitI2("OUT",tree->child[0]->attr.val,ac,"Mostra o valor do Registrador ac na saída p1");
        }
        else if(strcmp(tree->attr.name, "input")==0){
            emitI1("IN",ac,"Salva o valor de entrada no registrador ac");
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
         //emitRM("STORE",ac,tmpOffset--,pilha,"op: push left");
         emitRM("STORE",ac,0,pilha,"op: push left");
         emitI3("SUBI", pilha, pilha, 1, "Deslocamento pilha");
         /* gen code for ac = right operand */
         cGen(p2);
         /* now load left operand */
         emitI3("ADDI", pilha, pilha, 1, "Deslocamento pilha");
         emitRM("LOAD",ac1,0,pilha,"op: load left");

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
         emitRM("STORE",ac,0,pilha,"op: push left");
         emitI3("SUBI", pilha, pilha, 1, "Deslocamento pilha");
         /* gen code for ac = right operand */
         cGen(p2);
         /* now load left operand */
         emitRM("LOAD",ac1,0,pilha,"op: load left");
         emitI3("ADDI", pilha, pilha, 1, "Deslocamento pilha");

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
               emitRO("SET",ac,0,ac,"");
               break;
            case GT :   //>
               emitRO("SGT",ac,ac1,ac,"");

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
static void cGen( TreeNode * tree)
{ if (tree != NULL)
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
   //emitRM("LD",mp,0,ac,"load maxaddress from location 0");
   //emitRM("ST",ac,0,ac,"clear location 0");
   emitI2("LOADI",pilha,mp,"Inicializa o registrador que controla a memória");
   emitI2("LOADI",baseEscopo,mp+1,"Inicializa o registrador que controla a memória");
   emitI2L("LOADI",31,"_Fim","Inicializa o registrador 31 com o endereço do final do programa");
   emitJL("J","main","Vai para Main");
   emitComment("End of standard prelude.");
   /* generate code for TINY program */
   cGen(syntaxTree);
   /* finish */
   emitLabel("_Fim");
   emitComment("End of execution.");
   emitHalt("");
}