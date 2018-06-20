/****************************************************/
/* File: analyze.c                                  */
/* Semantic analyzer implementation                 */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "analyze.h"

/* counter for variable memory locations */
static int location = 0;
static char * scopeCurrent = "global";

/* Procedure traverse is a generic recursive 
 * syntax tree traversal routine:
 * it applies preProc in preorder and postProc 
 * in postorder to tree pointed to by t
 */
static void traverse(TreeNode *t,
                     void (*preProc)(TreeNode *),
                     void (*postProc)(TreeNode *)) {
    if (t != NULL) {
        preProc(t);
        {
            int i;
            for (i = 0; i < MAXCHILDREN; i++)
                traverse(t->child[i], preProc, postProc);
        }
        postProc(t);
        traverse(t->sibling, preProc, postProc);
    }
}

/* nullProc is a do-nothing procedure to 
 * generate preorder-only or postorder-only
 * traversals from traverse
 */
static void nullProc(TreeNode *t) {
    if (t == NULL) return;
    else return;
}

/* Procedure insertNode inserts 
 * identifiers stored in t into 
 * the symbol table 
 */
static void insertNode(TreeNode *t) {

    switch (t->nodekind) {
        case StmtK:
            switch (t->kind.stmt) {
                case IfK:

                    break;

                case WhileK:

                    break;

                case ReturnK:
                    t->scope = scopeCurrent;
                    break;

                default:
                    break;
            }
            break;
        case ExpK:
            switch (t->kind.exp) {
                case FunctionK:
                location = 0;
                    if (st_lookup(t->attr.name, scopeCurrent) == -1 && st_lookup(t->attr.name, "global") == -1 && st_lookup(t->attr.name, "") == -1) {
                        scopeCurrent = t->attr.name;
                        if (t->type == Int)
                            st_insert(t->attr.name, t->lineno, location++, "", "function", "integer", 0);
                        else
                            st_insert(t->attr.name, t->lineno, location++, "", "function", "void", 0);
                    } else
                        typeError(t, "Invalid Declaration. Already declared.");
                    break;

                case VariableK:     //Declaração de Variavel
                   if (st_lookup(t->attr.name, scopeCurrent) == -1 && st_lookup(t->attr.name, "global") == -1 && st_lookup(t->attr.name, "") == -1) {
                        if (t->type == Int){
                            t->scope = scopeCurrent;
                            st_insert(t->attr.name, t->lineno, location++, t->scope, "variable", "integer", 1);
                          }
                        else
                            typeError(t, "Invalid Declaration. It can't type VOID.");
                    } else
                        typeError(t, "Invalid Declaration. Already declared.");
                    break;

                case IdK:           //Chamada de variavel
                    if (st_lookup(t->attr.name, scopeCurrent) == -1 && st_lookup(t->attr.name, "global") == -1)
                        typeError(t, "It was not declared");
                    else {

                        if((strcmp(st_lookup_typeId(t->attr.name, scopeCurrent), "vector") == 0) || (strcmp(st_lookup_typeId(t->attr.name, ""), "vector") == 0)){
                            t->kind.exp = ParamVectorK;
                        }
                        t->scope = scopeCurrent;
                        t->typeData = st_lookup_type(t->attr.name, t->scope);
                        st_insert(t->attr.name, t->lineno, 0, t->scope, "variable", "integer", 0);
                    }
                    break;

                case IdVectorK:     //Chamada de Vetor
                    if (st_lookup(t->attr.name, scopeCurrent) == -1 && st_lookup(t->attr.name, "global") == -1)
                        typeError(t, "It was not declared");
                    else {
                        t->scope = scopeCurrent;
                        t->typeData = st_lookup_type(t->attr.name, t->scope);
                        if(strcmp(t->typeData, "pointer")==0) t->kind.exp = PointerK;
                        st_insert(t->attr.name, t->lineno, 0, t->scope, "vector", "integer", 0);
                    }
                    break;

                case CallK:         
                    t->scope = scopeCurrent;
                    if(strcmp(t->attr.name, "output")==0 || strcmp(t->attr.name, "input")==0){
                        st_insert(t->attr.name, t->lineno, location++, t->scope, "call", "-", 0);
                    }
                    else if (st_lookup(t->attr.name, "") == -1 && st_lookup(t->attr.name, "global") == -1){
                        typeError(t, "Invalid Call. It was not declared.");
                    }
                    else{
                        t->typeData = st_lookup_type(t->attr.name, "");
                        st_insert(t->attr.name, t->lineno, location++, t->scope, "call", "-", 0);
                    }
                    break;

                case VectorK:       //Declaração de Vetor
                    if (st_lookup(t->attr.name, scopeCurrent) == -1 && st_lookup(t->attr.name, "global") == -1 && st_lookup(t->attr.name, "") == -1) {
                        if (t->type == Int){
                            t->scope = scopeCurrent;
                            if(t->child[0] != NULL){
                                st_insert(t->attr.name, t->lineno, location, t->scope, "vector", "integer", t->child[0]->attr.val);
                                location +=t->child[0]->attr.val;
                            } 
                            else{
                                st_insert(t->attr.name, t->lineno, location, t->scope, "vector", "pointer", 1);
                                location += 1;
                            }
                          }
                        else
                            typeError(t, "Invalid Declaration. It can't type VOID.");
                    } else
                        typeError(t, "Invalid Declaration. Already declared.");
                    break;


                case LiteralK:
                    t->typeData = "integer";
                    break;

                case OpK:
                    t->typeData = "integer";
                    break;

                case RelK:
                    t->typeData = "integer";
                    break;

                default:
                    break;
            }
            break;
        default:
            break;
    }
}

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode *syntaxTree) {
    traverse(syntaxTree, insertNode, nullProc);

    if (st_lookup("main", "") == -1) {
        printf("main was not declared");
        Error = TRUE;
    }
    if (TraceAnalyze) {
        fprintf(listing, "\nSymbol table:\n\n");
        printSymTab(listing);
    }
}

static void typeError(TreeNode *t, char *message) {
    fprintf(listing, "Type error in %s at line %d: %s\n", t->attr.name, t->lineno, message);
    Error = TRUE;
}

/* Procedure checkNode performs
 * type checking at a single tree node
 */
static void checkNode(TreeNode *t) {
    switch (t->nodekind) {
        case ExpK:
            switch (t->kind.exp) {
                case RelK:
                    //fprintf(listing, "RelK:  %s    Tipo1: %s   Tipo2: %s\n\n",t->attr.name, t->child[0]->typeData, t->child[1]->typeData);
                    if(strcmp(t->child[0]->typeData, "void") == 0 || strcmp(t->child[1]->typeData, "void") ==  0)
                        typeError(t, "Invalid expression.");
                break;
                case VectorK:
                case FunctionK:
                case LiteralK:
                case OpK:
                    break;

                case IdK:

                    break;

                case TypeK:

                    break;

                case AtribK:

                    if(t->child[0]->kind.exp == CallK){
                        t->child[0]->typeData = st_lookup_type(t->child[0]->attr.name, "");
                    }
                    else if (t->child[0]->kind.exp == LiteralK || t->child[0]->kind.exp == IdK || t->child[0]->kind.exp == IdVectorK || t->child[1]->kind.exp == OpK || t->child[1]->kind.exp == RelK || t->child[1]->kind.exp == AtribK)
                        t->child[0]->typeData = "integer";
                    else{
                        typeError(t, "Invalid Attribution.");
                        break;
                    }

                    if(t->child[1]->kind.exp == CallK){
                        t->child[1]->typeData = st_lookup_type(t->child[1]->attr.name,  "");
                    }
                    else if (t->child[1]->kind.exp == LiteralK  || t->child[1]->kind.exp == IdK || t->child[1]->kind.exp == IdVectorK || t->child[1]->kind.exp == OpK || t->child[1]->kind.exp == RelK || t->child[1]->kind.exp == AtribK)
                        t->child[1]->typeData = "integer";
                    else{
                        typeError(t, "Invalid Attribution.");
                        break;
                    }
                    if (strcmp(t->child[0]->typeData, "void") == 0 || strcmp(t->child[1]->typeData, "void") == 0){
                        typeError(t, "Invalid expression.");
                    }
                    break;


                default:
                    break;
            }
            break;

        case StmtK:
            switch (t->kind.stmt) {
                case IfK:
                    break;

                case ReturnK:
                    if(t->attr.val == 2){
                      //fprintf(listing, "Return Nome: %s   Tipo : %s\n\n",  t->child[0]->attr.name, t->child[0]->typeData);
                      t->typeData = t->child[0]->typeData;
                    }
                    else
                      t->typeData = "void";

                    //fprintf(listing, "Tipo retorno:  %s    Escopo: %s   Tipo : %s\n\n",t->typeData, t->scope, st_lookup_type(t->scope,  ""));
                    if(strcmp(t->typeData, st_lookup_type(t->scope,  "")) != 0){
                        fprintf(listing, "Type error in Return at line %d: Return Invalid.\n", t->lineno);
                        Error = TRUE;
                    }
                    break;
                default:
                    break;
            }
            break;

        default:
            break;

    }
}

/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode *syntaxTree) {
    traverse(syntaxTree, nullProc, checkNode);
}
