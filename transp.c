#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

//Written by Brenden Brusberg
//11/13/2018
//I pledge my honor that I have abided by the Steven's Honor system

//This program takes 2 postive integers resembling powers of 2, the first will be with width of a square  matrix to be transposed
//the second variable will account for the stride at which the block sizes will be transposed

//This method takes the pointer of 2 matrices, the width of both matrices, assuming the matrix to be transposed is a valid inilized pointer
// with the same width described, and result is atleast malloced to the same size, stride must be a power of 2, and inteded to be less than
// or equal to the width of the matrix.
void transpose(float* matrix, float* result, int width, int stride){
  for (int row = 0;row < width;row += stride) {
    for (int col = 0;col < width;col += stride) {
      //Transpose a block starting at [row,col], with the stride
      for (int block_row = row; block_row < row + stride; ++block_row) {      
	for (int block_col =col; block_col < col + stride; ++block_col) {
	  result[block_row + block_col * width] = matrix[block_col + block_row * width];
	}
      }
    }
  }
}

int main(int argc, char** argv){

  //Check arg length
  if(argc != 3){
    printf("Incorect amount arguments\n");
    return -1;
  }
  
  int width = atoi(argv[1]);
  int stride = atoi(argv[2]);

  //Checking for positivity
  if(width < 1 || stride < 1){
    printf("Incorect arguments\n");
    return -1;
  }
 
  //Matrix to be transposed
  float * matrix = malloc(width * width * sizeof(float));
  float random;

  //Init matrix
  for(int row = 0; row < width; row++)
    for(int col = 0; col < width; col++){
      random = (float)rand();
      matrix[width * row + col] = random;
    }
  //Result matrix
  float * result = malloc(width * width * sizeof(float));
  
  //Set up time intervals
  struct timeval begin, end;
  double time;
  gettimeofday(&begin, NULL);

  //Transpose
  transpose(matrix, result, width, stride);

  //End time and print
  gettimeofday(&end, NULL);
  time = ((end.tv_sec * 1000000 + end.tv_usec) - (begin.tv_sec * 1000000 + begin.tv_usec));
  printf("Transpose on matrix size %d X %d took %f time with stide of %d\n", width, width, time, stride);
  //printf("%d,%d,%f\n", width, stride, time);  //This is >> to transptiming.csv, then made into a table

  free(matrix);
  free(result);
  return 0;
}
