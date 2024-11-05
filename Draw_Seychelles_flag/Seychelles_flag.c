
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mypnm.h"

#define WIDTH 640
#define HEIGHT 480

int sgn(int x)
{
  if ( x<0 ) return -1;
  if ( x>0 ) return 1;
  return 0;
}

int abs(int x)
{
  if ( x>=0 ) return x;
  return -x;
}

void swap(int *x,int *y)
{
  int tmp=*x;
  *x=*y;
  *y=tmp;
}


#if 1
unsigned char scr[WIDTH][HEIGHT];
unsigned char *red, *grn, *blu;

void Line(int x1, int x2, int y1, int y2, int X[HEIGHT], int nred, int ngrn, int nblu);
// Function to draw a line
// Arguments are coordinates (x1, y1) to (x2, y2) and color components nred, ngrn, nblu

int main(){
    int x, y;  // Variables representing x, y coordinates
    int X1[HEIGHT] = {0};
    int X2[HEIGHT] = {0};
    int X3[HEIGHT] = {0};
    int X4[HEIGHT] = {0};
    // Arrays to record x-coordinates for arbitrary y-coordinates when drawing a line
    // Four arrays are prepared as four lines will be drawn
    
    red = (unsigned char *)malloc(sizeof(char)*WIDTH*HEIGHT);
    grn = (unsigned char *)malloc(sizeof(char)*WIDTH*HEIGHT);
    blu = (unsigned char *)malloc(sizeof(char)*WIDTH*HEIGHT);
   

    Line(0, 200, HEIGHT-1, 0, X1, 0, 63, 135); // Draw a blue line from (0, 479) to (160, 0)
    for(y = 0; y < HEIGHT; y++){
        for(x = 0; x < X1[y]; x++){
            red[y*WIDTH+x] = 0;
            grn[y*WIDTH+x] = 63;
            blu[y*WIDTH+x] = 135;
        }
    }
    // Fill in the blue section
    
    
    Line(0, 480, HEIGHT-1, 0, X2, 252, 216, 86);
       // Draw a yellow line from (0, 479) to (480, 0)
    for(y = 0; y < HEIGHT; y++){
        for(x = X1[y]; x < X2[y]; x++){
            red[y*WIDTH+x] = 252;
            grn[y*WIDTH+x] = 216;
            blu[y*WIDTH+x] = 86;
        }
    }
    // Fill in the yellow section
    
    
    Line(0, WIDTH, HEIGHT-1, 160, X3, 214, 40, 40);
       // Draw a red line from (0, 479) to (640, 160)
    for(y = 0; y < HEIGHT; y++){
        if(X3[y] == 0){
            for(x = X2[y]; x < WIDTH; x++){
                red[y*WIDTH+x] = 214;
                grn[y*WIDTH+x] = 40;
                blu[y*WIDTH+x] = 40;
            }
        }
        // If the array value is not updated, fill until the maximum x-coordinate (640)
        else{
            for(x = X2[y]; x < X3[y]; x++){
                red[y*WIDTH+x] = 214;
                grn[y*WIDTH+x] = 40;
                blu[y*WIDTH+x] = 40;
            }
        }
        // If the array value is updated, fill until the x-coordinate recorded in the array when drawing the red line
           
    }
    // Fill in the red section
    
    
    Line(0, WIDTH, HEIGHT-1, 320, X4, 255, 255, 255);
     // Draw a white line from (0, 479) to (640, 320)
    for(y = 160; y < HEIGHT; y++){
        if(X4[y] == 0){
            for(x = X3[y]; x < WIDTH; x++){
                red[y*WIDTH+x] = 255;
                grn[y*WIDTH+x] = 255;
                blu[y*WIDTH+x] = 255;
            }
        }
        // If the array value is not updated, fill until the maximum x-coordinate (640)
        else{
            for(x = X3[y]; x < X4[y]; x++){
                red[y*WIDTH+x] = 255;
                grn[y*WIDTH+x] = 255;
                blu[y*WIDTH+x] = 255;
            }
        }
        // If the array value is updated, fill until the x-coordinate recorded in the array when drawing the white line
    }
    // Fill in the white section
    
    
    for(y = 320; y < HEIGHT; y++){
        for(x = X4[y]; x < WIDTH; x++){
            red[y*WIDTH+x] = 0;
            grn[y*WIDTH+x] = 122;
            blu[y*WIDTH+x] = 61;
        }
    }
    // Fill in the green section
    
    save_ppm( "Seychelles.ppm", red, grn, blu, WIDTH, HEIGHT ); // Save the image
  
    free(red);
    free(grn);
    free(blu);
    
    return 0;
}

void Line(int x1, int x2, int y1, int y2, int X[HEIGHT], int nred, int ngrn, int nblu){
    int x, y, e, dx, dy, sx, sy;
    
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    sx = sgn(x2 - x1);
    sy = sgn(y2 - y1);
    
    if(dx >= dy){
        if(x1 > x2){
            swap(&x1, &x2);
            swap(&y1, &y2);
            sy *= -1;
        }
        e = dx;
        for(x = x1, y = y1; x <= x2; x++){
            red[y*WIDTH+x] = nred;
            grn[y*WIDTH+x] = ngrn;
            blu[y*WIDTH+x] = nblu;
            X[y] = x;  // Record the x-coordinate value when the y-coordinate is y
            e += 2 * dy;
            if(e >= 2 * dx){
                y += sy;
                e -= 2 * dx;
            }
        }
    }
    else{
        if(y1 > y2){
            swap(&x1, &x2);
            swap(&y1, &y2);
            sx *= -1;
        }
        e = dy;
        for(x = x1, y = y1; y <= y2; y++){
            red[y*WIDTH+x] = nred;
            grn[y*WIDTH+x] = ngrn;
            blu[y*WIDTH+x] = nblu;
            X[y] = x;  // Record the x-coordinate value when the y-coordinate is y
            e += 2 * dx;
            if(e >= 2 * dy){
                x += sx;
                e -= 2 * dy;
            }
        }
        
    }
}

#endif
