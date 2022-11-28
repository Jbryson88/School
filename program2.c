#include<stdio.h>
#include<stdlib.h>

/* global 2d array */
int **A;
int **B;
int **C;

/* m for row of A
n for column of A
n for row of B
k for column of B
*/
int m,n,k;

/* get 2d matrix from user */
int **getMatrix(int a,int b){
int r,i,j;
/* create 2d dynamic matrix */
int *A = (int *)malloc(a * sizeof(int *));
for (r = 0; r < a; r++){
A[r] = (int *)malloc(b * sizeof(int));
}

/* enter matrix from user */
printf("Enter matrix %dX%d-\n",a,b);
for(i=0;i<a;i++){
for(j=0;j<b;j++){
scanf("%d",&A[i][j]);
}
}
/* return matrix A */
return A;
}


/* print matrix */
void printmatrix(int** A,int a,int b){
int i,j;
for(i=0;i<a;i++){
for(j=0;j<b;j++){
printf("%d ",A[i][j]);
}
printf("\n");
}
}

/* matrix product of 2 matrix */
int** product(int** A,int** B,int a,int b,int c){
int r,i,j,k;
/* new 2d matrix creation */
int *C = (int *)malloc(a * sizeof(int *));
for (r = 0; r < a; r++){
C[r] = (int *)malloc(c * sizeof(int));
}

/* initialize 2d matrix */
for(i=0;i<a;i++){
for(j=0;j<c;j++){
C[i][j]=0;
}
}

/* product of 2 2D matrix */
for(i=0;i<a;i++){
for(j=0;j<c;j++){
for(k=0;k<b;k++){
C[i][j]+=A[i][k]*B[k][j];
}
}
}

return C;
}


void main(){
/* local variable */
int rA,cA,rB,cB;

/* enter user inputs */
printf("Enter the number of rows of A : ");
scanf("%d",&rA);
printf("Enter the number of coloumns of A : ");
scanf("%d",&cA);

printf("Enter the number of rows of B : ");
scanf("%d",&rB);
printf("Enter the number of coloumns of B : ");
scanf("%d",&cB);

/* number of columns of A and number of rows of B are not same */
if(cA!=rB){
printf("\nnumber of columns and number of rows are not same.");
printf("\nproduct of matrix is not possible.\n");
}
/* 2 valid matrix */
else{
/* assign */
m=rA;
n=cA;
k=cB;

/* get 2 matrix from user */
printf("Matrix A\n");
A=getMatrix(m,n);

printf("Matrix B\n");
B=getMatrix(n,k);

/* product of 2 matrix */
C=product(A,B,m,n,k);

/* print 3 matrix */
printf("\n\nMatrix A--\n");
printmatrix(A,m,n);
printf("\n\nMatrix B--\n");
printmatrix(B,n,k);
printf("\n\nMatrix C--\n");
printmatrix(C,m,k);
}


}