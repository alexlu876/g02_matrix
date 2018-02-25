#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
  //first see if we need to grow matrix, if cols = lastcol in points
  if(points->lastcol == points->cols){
    grow_matrix(points, points->cols + 2); //this just adds 1 col, it could add more but i think 1 is fine
    //i made it to add 2 cols cause i think i always want an even # of cols
  }

  //now actually add points
  points->m[0][points->lastcol] = x; //row 0, lastcol is now the x coord of added point
  points->m[1][points->lastcol] = y;
  points->m[2][points->lastcol] = z;
  points->m[3][points->lastcol] = 1; //keeping 1 here 

  //increment points.lastcol
  points->lastcol++;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
  //just 2 add points
  add_point(points, x0, y0, z0);
  add_point(points, x1, y1, z1);
}


/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {
  int i;
  //scroll through matrix pairwise
  for(i = 0, i < points->lastcol , i+=2){
    //i guess i just leave out z for now? i'll just do that
    drawline(points->m[0][i], points->m[1][i], points->m[0][i+1], points->m[1][i+1], s, c);
  }
}





//algo to determine oct
int octant(int x0, int y0, int x1, int y1){
  

  int d_x = x1 - x0;
  int d_y = y1 - y0;

  //oct 1
  if(d_x >= d_y && d_y >= 0){
    return 1;
  }

  //oct 2w
  if(d_x <= d_y && d_y >= 0){
    return 2;
  }

  //oct 8
  if(d_x >= d_y * -1 && d_y < 0){
    return 8;
  }

  //oct 7
  if(d_x <= d_y * -1 && d_y < 0){
    return 7;
  }

  return 0;
}



//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {

  //make sure we are drawing left to right
  if(x1 < x0){
    draw_line(x1, y1, x0, y0, s, c);
  }

  else{

    int A = y1 - y0;
    int B = x1 - x0;
    
    //make my life easier avoid pass by value stuff
    int x = x0;
    int y = y0;
    
    int oct = octant(x0, y0, x1, y1); 
    
    int d;

    if(oct == 1){
      
      d = A + A - B;
      while(x < x1){
        plot(s, c, x, y);
        if(d > 0){
          y++;
          d -= B + B;
        }
        x++;
        d += A + A;
      }
    }

    else if(oct == 2){

      d = A - B - B;
      while(y < y1){
        plot(s, c, x, y);
        if(d < 0){
          x++;
          d += A + A;
        }
        y++;
        d -= B + B;
      }
    }

    else if(oct == 7){
      
      d = A + B + B;
      while(y > y1){
        plot(s, c, x, y);
        if(d > 0){
          x++;
          d += A + A;
        }
        y--;
        d += B + B;
      }
    }
    
    else if(oct == 8){
      
      d = A + A + B;
      while(x < x1){
        plot(s, c, x, y);
        if(d < 0){
          y--;
          d += B + B;
        }
        x++;
        d += A + A;
      }
    }
  }
}
