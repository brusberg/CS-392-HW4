#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

//Written by Brenden Brusberg
//11/13/2018
//I pledge my honor that I have abided by the Steven's Honor system

//This program takes 2 postive integers resembling powers of 2, the first will be with width of the matrix to be transposed
// the second variable will account for the stride at which the block sizes will be transposed

//Simple min function
float min(float left, float right){
  /*
  if(left <= right){
    return left;
  }else return right;
  */
  return left;
}

//This method takes the pointer of 2 matrices, the width of both matrices, assuming the matrix to be transposed is a valid inilized pointer
//with the same width described, and result is atleast malloced to the same size, stride must be a power of 2, and inteded to be less than
//or equal to the width of the matrix.
void transpose(float* matrix, float* result, int width, int height, int stride){
  for (int row = 0;row < height;row += stride){
    for (int col = 0;col < width;col += stride){
      //Transpose a block starting at [row,col], with the stride
      for (int block_row = row; block_row < row + stride; ++block_row){
	if(block_row < height)
	  for (int block_col = col; block_col < col + stride; ++block_col){
	    if(block_col < width)
	      //if(block_col + block_row * width < width * height && block_row + block_col * width < width *height)//Testing code
	      result[block_row + block_col * height] = matrix[block_col + block_row * width];
	  }	  
      }
    }
  }
  return;
}

int main(int argc, char** argv){

  //Check arg length
  if(argc != 4){
    printf("Incorect amount arguments\n");
    return -1;
  }
  
  int height = atoi(argv[1]);
  int width = atoi(argv[2]);
  int stride = atoi(argv[3]);

  //Checking for positivity
  if(width < 1 || stride < 1 || height < 1){
    printf("Incorect arguments\n");
    return -1;
  }
  
  //Matrix to be transposed
  float * matrix = malloc(width * height * sizeof(float));
  float random;

  //Init matrix
  for(int row = 0; row < height; row++)
    for(int col = 0; col < width; col++){
      random = (float)rand();
      matrix[width * row + col] = random;
    }
  
  //Result matrix
  float * result = malloc(width * height * sizeof(float));

  //Set up time intervals
  struct timeval begin, end;
  double time;
  gettimeofday(&begin, NULL);

  //printf("[%f][%f]\n[%f][%f]\n\n",matrix[0],matrix[width * 0 + (width-1)],matrix[width * (height-1)],matrix[width * (height-1) + (width-1)]);//Test print

  //Transpose
  transpose(matrix, result, width, height, stride);

  //printf("[%f][%f]\n[%f][%f]\n",result[0],result[height * 0 + (height-1)],result[height * (width-1)],result[height * (width-1) + (height-1)]);//Test print

  //End time and print
  gettimeofday(&end, NULL);
  time = ((end.tv_sec * 1000000 + end.tv_usec) - (begin.tv_sec * 1000000 + begin.tv_usec));
  printf("Transpose on matrix size %d X %d took %f time with stide of %d\n", width, height, time, stride);
  //printf("%d,%d,%d,%f\n", width, height, stride, time);  //This is >> to transpiftiming.csv, then made into a table

  free(matrix);
  free(result);
  
  return 0;
}
