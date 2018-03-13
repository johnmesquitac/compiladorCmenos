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

                    break;

                default:
                    break;
            }
            break;
        case ExpK:
            switch (t->kind.exp) {
                case FunctionK:
                    if (st_lookup(t->attr.name, scopeCurrent) == -1 && st_lookup(t->attr.name, "global") == -1) {
                        scopeCurrent = t->attr.name;
                        if (t->type == Int)
                            st_insert(t->attr.name, t->lineno, location++, "", "function", "integer");
                        else
                            st_insert(t->attr.name, t->lineno, location++, "", "function", "void");
                    } else
                        typeError(t, "Invalid Declaration. Already declared.");
                    break;

                case VariableK:
                    if (st_lookup(t->attr.name, scopeCurrent) == -1 && st_lookup(t->attr.name, "global") == -1) {
                        if (t->type == Int){
                            t->scope = scopeCurrent;
                            st_insert(t->attr.name, t->lineno, location++, t->scope, "variable", "integer");
                          }
                        else
                            typeError(t, "Invalid Declaration. It can't type VOID.");
                    } else
                        typeError(t, "Invalid Declaration. Already declared.");
                    break;

                case IdK:
                    if (st_lookup(t->attr.name, scopeCurrent) == -1 && st_lookup(t->attr.name, "global") == -1)
                        typeError(t, "It was not declared");
                    else {
                        t->scope = scopeCurrent;
                        st_insert(t->attr.name, t->lineno, 0, t->scope, "variable", "integer");
                    }
                    break;

                case IdVectorK:
                    if (st_lookup(t->attr.name, scopeCurrent) == -1 && st_lookup(t->attr.name, "global") == -1)
                        typeError(t, "It was not declared");
                    else {
                        t->scope = scopeCurrent;
                        st_insert(t->attr.name, t->lineno, 0, t->scope, "variable", "integer");
                    }
                    break;

                case CallK:
                    t->scope = scopeCurrent;
                    if (st_lookup(t->attr.name, "") == -1 && st_lookup(t->attr.name, "global") == -1)
                        typeError(t, "Invalid Call. It was not declared.");
                    else
                        st_insert(t->attr.name, t->lineno, location++, t->scope, "call", "-");
                      break;

                case VectorK:
                    if (st_lookup(t->attr.name, scopeCurrent) == -1 && st_lookup(t->attr.name, "global") == -1) {
                        if (t->type == Int){
                            t->scope = scopeCurrent;
                            st_insert(t->attr.name, t->lineno, location++, t->scope, "vector", "integer");
                          }
                        else
                            typeError(t, "Invalid Declaration. It can't type VOID.");
                    } else
                        typeError(t, "Invalid Declaration. Already declared.");
                    break;

                case TypeK:

                    break;

                case AtribK:
                    //t->child[0]->typeData = st_lookup_type(t->child[0]->attr.name, t->child[0]->scope);
                    //t->child[1]->typeData = st_lookup_type(t->child[1]->attr.name, t->child[1]->scope);
                    //if (t->child[0]->typeData != t->child[1]->typeData)
                      //  typeError(t, "Invalid expression.");
                    //fprintf(listing, "Denis   %d     %d   \n\n", t->child[0]->type, t->child[1]->type);
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
                case VectorK:
                case FunctionK:
                case LiteralK:
                case OpK:
                    break;

                case IdK:
                    t->type = Int;
                    break;

                case TypeK:
                    break;

                case AtribK:
                    break;

                case CallK:
                    break;

                default:
                    break;
            }
            break;

        case StmtK:
            switch (t->kind.stmt) {
                case IfK:
                    if (t->child[0]->type == Int && t->child[1]->type == Int)
                        typeError(t->child[0], "if test is not Boolean");
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
