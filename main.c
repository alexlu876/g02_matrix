#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  color c;
  struct matrix *edges;

  c.red = 0;
  c.blue = 0;
  c.green = 255;

  edges = new_matrix(4, 4);
  
  add_point(edges, 250, 250, 0);
  add_point(edges, 250, 100, 0);
  add_point(edges, 0, 0, 0);
  add_point(edges, 500, 500, 0);
  //print_matrix(edges);
  int i;
  srand(time(NULL));
  for(i = 0; i < 300; i++){
    add_point(edges, rand() % 500, rand() % 500, 0);
  }

  draw_lines(edges, s, c);
  save_ppm(s, "matrix.ppm");

  /*
  add_point(edges, 2, 1, 0);
  add_point(edges, 1, 2, 0);
  add_point(edges, 1, 0, 3);
  add_point(edges, 0, 1, 0);
  print_matrix(edges);
  //ident(edges);
  //print_matrix(edges);
  
  struct matrix *tester;
  tester = new_matrix(4, 4);
  add_point(tester, 1, 2, 1);
  add_point(tester, 2, 3, 0);
  add_point(tester, 0, 0, 1);
  add_point(tester, 2, 0, 2);
  print_matrix(tester);
  matrix_mult(edges, tester);
  print_matrix(tester);

  ident(edges);
  matrix_mult(edges, tester);
  print_matrix(tester);
  */
  free_matrix( edges );
  //free_matrix(tester);
}



