//
// AED, January 2022
//
// Solution of the second practical assignement (multi-ordered tree)
//
// Place your student numbers and names here
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AED_2021_A02.h"  



//
// the custom tree node structure
//
// we want to maintain three ordered trees (using the same nodes!), so we need three left and three right pointers
// so, when inserting a new node we need to do it three times (one for each index), so we will end upo with 3 three roots
//

typedef struct tree_node_s
{
  char name[MAX_NAME_SIZE + 1];                         // index 0 data item
  char zip_code[MAX_ZIP_CODE_SIZE + 1];                 // index 1 data item
  char telephone_number[MAX_TELEPHONE_NUMBER_SIZE + 1]; // index 2 data item
  char security_number[MAX_SECURITY_NUMBER_SIZE + 1];
  struct tree_node_s *left[4];                          // left pointers (one for each index) ---- left means smaller
  struct tree_node_s *right[4];                         // right pointers (one for each index) --- right means larger
}
tree_node_t; 


// the node comparison function (do not change this)
  int compare_tree_nodes(tree_node_t *node1,tree_node_t *node2,int main_idx){
  
    int i,c;

    for(i = 0;i < 4;i++)
    {
      if(main_idx == 0)
        c = strcmp(node1->name,node2->name); // compara nome
      else if(main_idx == 1)
        c = strcmp(node1->zip_code,node2->zip_code); // compara zip
      else if(main_idx == 2)
        c = strcmp(node1->telephone_number,node2->telephone_number); // compara numero
      else
        c = strcmp(node1->security_number,node2->security_number); // compara sec numero
      if(c != 0)
        return c; // different on this index, so return (sao diferentes, retorna c)
      main_idx = (main_idx == 2) ? 0 : main_idx + 1; // advance to the next index (sao iguais, bora para o prox)
    }
    return 0;
  }
//

// tree insertion routine                               /*qual arvore*/
  void tree_insert(tree_node_t **rootp, tree_node_t *node, int main_idx){
   
    if (*rootp == NULL){
      *rootp = node;
      return;
    }

    int c = compare_tree_nodes(*rootp,node,main_idx);
    if (c < 0){
  
      tree_insert(&((*rootp)->right[main_idx]), node,main_idx);
      return;
    }
    else{
  
      tree_insert(&((*rootp)->left[main_idx]), node,main_idx);
      return;
    }
    return; 
  }
//

// tree search routine                                    
  tree_node_t* find(tree_node_t** rootp,int main_idx,tree_node_t* person){

    if (compare_tree_nodes(*rootp,person,main_idx)==0){
    
      return *rootp;
    }
    else if (compare_tree_nodes(*rootp,person,main_idx) > 0){
    
      return find(&((*rootp)->left[main_idx]),main_idx,person);
    }
    else{
    
      return find(&((*rootp)->right[main_idx]),main_idx,person);
    }
    return NULL;
  }
//
 
// tree depdth                                          
  int tree_depth(tree_node_t** root, int main_idx){

    if ( *root == NULL){

      return 0;
    }
    int leftheight = tree_depth(&((*root)->left[main_idx]),main_idx);
    int rightheight = tree_depth(&((*root)->right[main_idx]),main_idx);

    if (leftheight > rightheight){
    
      return leftheight + 1;
    }
    else{

      return rightheight + 1 ;
    }
  }
//

// list, i,e, traverse the tree 
  void visit_node(tree_node_t* node){

     
    printf("Person #\n");
    printf("  Name --------------- %s\n",node->name);
    printf("  ZipCode ------------ %s\n",node->zip_code);
    printf("  Telephone Number --- %s\n",node->telephone_number);
    printf("  Security Number --- %s\n",node->security_number);

    return;
  }       

  int list(tree_node_t* node,int main_idx){

    if (node !=NULL){

      visit_node(node);
      if (node->left[main_idx] != NULL){

        list(node->left[main_idx],main_idx);
      }
      if (node->right[main_idx] != NULL){

        list(node->right[main_idx],main_idx);
      }
    }
    return 1;
  } 
//

// Find depth of node
  tree_node_t* node_depth(tree_node_t** rootp,int main_idx,tree_node_t* person,int rights, int lefts){
  
    if (compare_tree_nodes(*rootp,person,main_idx)==0){
    
      printf("found it\n");
      printf("the position is at %d rigths and %d lefts, and has depth %d",rights,lefts,rights + lefts);
      return *rootp;
    }
    else if (compare_tree_nodes(*rootp,person,main_idx) > 0){
    
      return node_depth(&((*rootp)->left[main_idx]),main_idx,person,rights,lefts+1);
    }
    else{
    
      return node_depth(&((*rootp)->right[main_idx]),main_idx,person,rights +1,lefts);
    }
    return NULL;
  }
//

//  how many nodes
  int numberNodes(tree_node_t** root, int main_idx){
  
    if ( *root == NULL){
      return 0;
    }
    int leftnodes= numberNodes(&((*root)->left[main_idx]),main_idx);
    int rightnodes = numberNodes(&((*root)->right[main_idx]),main_idx);

    return rightnodes + leftnodes+ 1 ;
  }
//
 
//  how many nodes is each level
  int deapthNodes(tree_node_t** rootp, int main_idx,int depth){
  
    if ( *rootp == NULL){
      return 0;
    }
    if (depth == 0){
      return 1;
    }
    return deapthNodes(&(*rootp)->left[main_idx],main_idx,depth-1) + deapthNodes(&(*rootp)->right[main_idx],main_idx,depth-1);
  }
//

//  how many leaf nodes
  int leafCount(tree_node_t** rootp,int main_idx){
  
    if ( *rootp == NULL){
      return 0;
    }

    if ((*rootp)->left[main_idx] == NULL && (*rootp)->right[main_idx] == NULL){
    
      return 1;
    }
    else{
    
      return leafCount(&(*rootp)->left[main_idx],main_idx) + leafCount(&(*rootp)->right[main_idx],main_idx);
    }
  }
//
 
// main program
  int main(int argc,char **argv){
  
    double dt;

    // process the command line arguments
      if(argc < 3)
      {
        fprintf(stderr,"Usage: %s student_number number_of_persons [options ...]\n",argv[0]);
        fprintf(stderr,"Recognized options:\n");
        fprintf(stderr,"  -list[N]              # list the tree contents, sorted by key index N (the default is index 0)\n");
        // place a description of your own options here
        return 1;
      }
      int student_number = atoi(argv[1]);
      if(student_number < 1 || student_number >= 1000000)
      {
        fprintf(stderr,"Bad student number (%d) --- must be an integer belonging to [1,1000000{\n",student_number);
        return 1;
      }
      int n_persons = atoi(argv[2]);
      if(n_persons < 3 || n_persons > 10000000)
      {
        fprintf(stderr,"Bad number of persons (%d) --- must be an integer belonging to [3,10000000]\n",n_persons);
        return 1;
      }
    //

    // generate all data
      tree_node_t *persons = (tree_node_t *)calloc((size_t)n_persons,sizeof(tree_node_t));
      if(persons == NULL)
      {
        fprintf(stderr,"Output memory!\n");
        return 1;
      }
      aed_srandom(student_number);
      for(int i = 0;i < n_persons;i++)
      {
        random_name(&(persons[i].name[0]));
        random_zip_code(&(persons[i].zip_code[0]));
        random_telephone_number(&(persons[i].telephone_number[0]));
        random_security_number(&(persons[i].security_number[0]));
        for(int j = 0;j < 4;j++)
          persons[i].left[j] = persons[i].right[j] = NULL; // make sure the pointers are initially NULL
      }
    // 

    // create the ordered binary trees

      dt = cpu_time();
      tree_node_t *roots[4]; // three indices, three roots

      for(int main_index = 0;main_index < 4;main_index++){
        roots[main_index] = NULL;
      }

      double tm;
      for(int main_index = 0;main_index < 4;main_index++){
        
        FILE *f = NULL;
        char str[16];
        sprintf(str, "%d", main_index);
        strcat(str,"_creation.txt");
        f = fopen(str, "a");

        tm = cpu_time();
        for(int i = 0;i < n_persons;i++){
          
          tree_insert(&(roots[main_index]), &(persons[i]), main_index); // place your code here to insert &(persons[i]) in the tree with number main_index
          
          if((i+1) % 5000 == 0){
            double tmf = cpu_time() - tm;
            //fprintf(f, "%d %f \n",i, tmf);
          }
        }
      }
      dt = cpu_time() - dt;
      //printf("Tree creation time (%d persons): %.3es\n",n_persons,dt);
    //
    
    // search the tree
      for(int main_index = 0;main_index < 4;main_index++){

        FILE *f2 = NULL;
        char str[20];
        sprintf(str, "%d", main_index);
        strcat(str,"_Search.txt"); 
        f2 = fopen(str, "a");

        dt = cpu_time();
        for(int i = 0;i < n_persons;i++){
        
          tree_node_t n = persons[i]; // make a copy of the node data
          if(find(&roots[main_index],main_index,&n) != &(persons[i])){ // place your code here to find a given person, searching for it using the tree with number main_index
          
            fprintf(stderr,"person %d not found using index %d\n",i,main_index);
            return 1;
          }

          if((i+1) % 5000 == 0){

            double tmf = cpu_time() - dt;
            //fprintf(f2, "%d %f \n",i, tmf);
          }
        }
        dt = cpu_time() - dt;
        //printf("Tree search time (%d persons, index %d): %.3es\n",n_persons,main_index,dt);
      }
    //

    // compute the largest tree depdth
      for(int main_index = 0;main_index < 4;main_index++)
      {
        dt = cpu_time();
        int depth = tree_depth(&roots[main_index],main_index); // place your code here to compute the depth of the tree with number main_index
        dt = cpu_time() - dt;
        //printf("Tree depth for index %d: %d (done in %.3es)\n",main_index,depth,dt);
        printf("%d  %d  %d\n", n_persons, main_index,depth);
      }
    //

    
    // process the command line optional arguments
       
      if(argc == 4){
        printf("\n\n");
        if(strcmp(argv[3],"-list0") == 0){   
          printf("List of persons:\n");
          list(roots[0], 0); // place your code here to traverse, in order, the tree with number main_index
        }else if(strcmp(argv[3],"-list1") == 0){   
          printf("List of persons:\n");
          list(roots[1], 1); // place your code here to traverse, in order, the tree with number main_index
        }else if(strcmp(argv[3],"-list2") == 0){   
          printf("List of persons:\n");
          list(roots[2], 2); // place your code here to traverse, in order, the tree with number main_index
        }
        else if(strcmp(argv[3],"-list3") == 0){   
          printf("List of persons:\n");
          list(roots[3], 3); // place your code here to traverse, in order, the tree with number main_index
        }
        printf("\n\n");   
      }
    //
    

     
    /*
    // Some more prints
      printf("how many nodes is ---> %d\n", numberNodes(&roots[2],2));
      node_depth(&roots[2],2,&persons[2],0,0);
      printf("\nleaf count is -------> %d\n",leafCount(&roots[2],2));
      printf("nodes with depth 10  =  %d\n",deapthNodes(&roots[2],2, 10));
    //
    */
    
    // clean up --- don't forget to test your program with valgrind, we don't want any memory leaks
    free(persons);
    return 0;
  }
//