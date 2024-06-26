#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
   //validar filas
    for(int i = 0; i < 9; i++)
    {
       int puerta[10] = {};
        for(int j = 0; j < 9; j++)
        {
          if(puerta[n->sudo[i][j]] == 0 && n->sudo[i][j] != 0)
             puerta[n->sudo[i][j]] = 1;
          else if(puerta[n->sudo[i][j]] == 1) return 0;
        }
    }
       
   
   //validar columnas
    for(int j = 0; j < 9; j++)
    {
       int puerta[10] = {};
       for(int i = 0; i < 9; i++)
      {
         if(puerta[n->sudo[i][j]] == 0 && n->sudo[i][j] != 0)
            puerta[n->sudo[i][j]] = 1;
         else if(puerta[n->sudo[i][j]] == 1)return 0;
      }
    }

   //validar submatrices
   for(int k = 0; k < 9; k++) 
   {
      int puerta[10] = {};
      int p;
      for(p = 0; p < 9; p++)
      {
         int i=3*(k/3) + (p/3);
         int j=3*(k%3) + (p%3);
         if(puerta[n->sudo[i][j]] == 0 && n->sudo[i][j] != 0)
            puerta[n->sudo[i][j]] = 1;
         else if(puerta[n->sudo[i][j]] == 1) return 0;
      }
   } 
      
    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int create = 0;
    for(int i = 0; i < 9; i++)
       {
          for(int j = 0; j < 9; j++)
              {
                 if(n->sudo[i][j] == 0)
                 {
                    create = 1;
                    for(int k = 1; k <= 9; k++)
                         {
                            Node *adj = copy(n);
                            adj->sudo[i][j] = k;
                            if(is_valid(adj))
                               pushBack(list, adj);
                         }
                 }
                if(create) break;
              }
          if(create) break;
       } 
    return list;
}


int is_final(Node* n){
   for(int i = 0; i < 9; i++)
      for(int j = 0; j < 9; j++)
         if(n->sudo[i][j] == 0) return 0;
    return 1;
}

Node* DFS(Node* initial, int* cont){
   Stack* S = createStack();
   push(S, initial);
   while(get_size(S) != 0)
      {
         *cont += 1;
         Node *n = top(S);
         pop(S);
         if(is_final(n)) return n;
         
         List *adj = get_adj_nodes(n);
         Node *aux = first(adj);
         while(aux)
            {
               push(S, aux);
               aux = next(adj);
            }
         free(n);
      }
  return NULL;
}

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}
*/