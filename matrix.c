#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"


/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

print the matrix
*/
void print_matrix(struct matrix *m) {
  int i = 0;
  //int k = 0;
  //thanks to stack overflow, printing 2 decimals is easy
  //using printf(%.2f, stuff) should do the trick
  while(i < m->rows){
    int k = 0;//i had to move cols here, wouldn't work when up there declaration inside fixes it
    while(k < m->cols){
      printf("%.2f  ", m->m[i][k]);
      k++;
    }
    printf("\n");
    i++;
  }
  printf("\n");

}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns: 

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
  int i = 0;
  //int k = 0;
  while(i < m->rows){
    int k = 0; //again this fixes things like above
    while(k < m->cols){
      if(i == k){
        m->m[i][k] = 1;
      }
      else{
        m->m[i][k] = 0;
      }
      k++;
    }
    i++;
  }
}


/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

a*b -> b
*/
void matrix_mult(struct matrix *a, struct matrix *b) {
  //thank u for built in fxns ^_^
  struct matrix *new = new_matrix(a->rows, b->cols);
  int i = 0;
  //int k = 0;
  //int z;
  //int sum = 0;
  while(i < a->rows){
    int k = 0;
    while(k < b->cols){
      int sum = 0;
      int z;
      for(z = 0; z < a->cols; z++){
        sum+= a->m[i][z] * b-> m[z][k];
      }
      new->m[i][k] = sum;
      k++;
    }
    i++;
  }
  copy_matrix(new, b);
  free_matrix(new);
}



/*===============================================
  These Functions do not need to be modified
  ===============================================*/

/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
         int cols 
Returns: 

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)... 
*/
struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;

  tmp = (double **)malloc(rows * sizeof(double *));
  for (i=0;i<rows;i++) {
      tmp[i]=(double *)malloc(cols * sizeof(double));
    }

  m=(struct matrix *)malloc(sizeof(struct matrix));
  m->m=tmp;
  m->rows = rows;
  m->cols = cols;
  m->lastcol = 0;

  return m;
}


/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

1. free individual rows
2. free array holding row pointers
3. free actual matrix
*/
void free_matrix(struct matrix *m) {

  int i;
  for (i=0;i<m->rows;i++) {
      free(m->m[i]);
    }
  free(m->m);
  free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols 
Returns: 

Reallocates the memory for m->m such that it now has
newcols number of collumns
====================*/
void grow_matrix(struct matrix *m, int newcols) {
  
  int i;
  for (i=0;i<m->rows;i++) {
      m->m[i] = realloc(m->m[i],newcols*sizeof(double));
  }
  m->cols = newcols;
}


/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {

  int r, c;

  for (r=0; r < a->rows; r++) 
    for (c=0; c < a->cols; c++)  
      b->m[r][c] = a->m[r][c];  
}
