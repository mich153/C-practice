#include <stdio.h>
#include <stdlib.h>
struct board{
	int** mat;
	int height,width;
};
typedef struct board board;
#define x -30
#define o 30
int g=0;
void start();//start the game
void setMat(board*);//input height and width of the game board
int illegal(int,int,int);//check if it illegal number
void initMat(board*);//initialize the game board
void printMat(board);//print a matrix
void xTurn(board*);//x turn to playing
int oTurn(board*);//o turn to playing
int line(board*,int,int);//check of o can to win this turn or x in next turn
int column(board*,int,int);//check of o can to win this turn or x in next turn
int diagonal_1(board*,int,int);//check of o can to win this turn or x in next turn
int diagonal_2(board*,int,int);//check of o can to win this turn or x in next turn
void oPlay(board*);//o play if it can't win or block
int xWin(board*);//check if x win
int winDiagonal(board*);//check if x win
int fullBoard(board*);//check if the board is full
void freeChart(board*);//free the malloc
void main(){
	int again;
	do{
		start();
		do{
			printf("Do you want to play again?\n0. No\n1. Yes\n");
			scanf("%d",&again);
		}while(illegal(0,1,again));//wrong input
	}while(again);//the user want to play again
	printf("You choose to end the game, bye bye.");
}
void start(){
	board mat;
	setMat(&mat);
	do{
		xTurn(&mat);//x turn
		if(xWin(&mat)==0||fullBoard(&mat)==0)//if x win or the board full so game over
			break;
		printMat(mat);
		if(oTurn(&mat)==0)//o turn and if it win so game over
			break;
		printMat(mat);
	}while(fullBoard(&mat));//if the board full so game over
	printMat(mat);
	if(xWin(&mat)==0)//x win
		printf("x win\n");
	freeChart(&mat);
}
void setMat(board* mat){
	do{
		printf("enter a height(3-5):");
		scanf("%d",&(mat->height));//entring sizes
	}while(illegal(3,5,mat->height));//wrong input
	do{
		printf("enter a width(3-5):");
		scanf("%d",&(mat->width));//entring sizes
	}while(illegal(3,5,mat->width));//wrong input
	mat->mat=(int**)malloc(sizeof(int*)*(mat->height));
	if(mat->mat==NULL){//for each pointer allocation line of integers
		printf("Memory allocation problem, ending programs.\n");
		exit(1);
	}
	g++;//allocating the pointers array
	initMat(mat);
}
int illegal(int min,int max,int num){
	if(num<min||num>max)//illegal number
		return 1;
	else//legal number
		return 0;
}
void initMat(board* mat){
	int i,j,k;
	for(i=0,k=1;i<mat->height;i++){
		mat->mat[i]=(int*)malloc(sizeof(int)*(mat->width));
		if(mat->mat==NULL){//for each pointer allocation line of integers
			printf("Memory allocation problem, ending programs.\n");
			exit(1);
		}
		g++;
		for(j=0;j<mat->width;j++,k++)
			mat->mat[i][j]=k;//numbering mat's nambers
	}
	printMat(*mat);
}
void printMat(board mat){
	int i,j;
	for(i=0;i<mat.height;i++){//for each line
		for(j=0;j<mat.width;j++){//for each number in the line
			if(mat.mat[i][j]==x)//x chose this place
				printf("    x");
			else if(mat.mat[i][j]==o)//o chose this place
				printf("    o");
			else//anyone not choose this place
				printf("%5d",mat.mat[i][j]);
		}
		printf("\n");//the line is ending
	}
}
void xTurn(board* mat){
	int choise,i,j;
	do{
		printf("x enter your choice:");
		scanf("%d",&choise);
		i=(choise-1)/mat->width;//the line that choise in
		j=(choise-1)%mat->width;//the column that choise in
	}while(illegal(1,mat->height*mat->width,choise)||illegal(0,mat->height,i)||illegal(0,mat->width,j)||illegal(1,mat->height*mat->width,mat->mat[i][j]));//wrong input
	mat->mat[i][j]=x;//x choose this place
}
int oTurn(board* mat){
	printf("o turn:\n");
	if(line(mat,x,o)||column(mat,x,o)||diagonal_1(mat,x,o)||diagonal_2(mat,x,o)){//o win
		printf("o win\n");
		return 0;//game over
	}
	else if(line(mat,o,x)||column(mat,o,x)||diagonal_1(mat,o,x)||diagonal_2(mat,o,x)){//o block
		return 1;
	}
	else//play if can't win or block
		oPlay(mat);
	return 1;
}
int line(board* mat,int play1,int play2){
	int i,j,not=0,line,column;
	for(i=0;i<mat->height;i++){
		for(not=0,j=0;j<mat->width&&not<2&&mat->mat[i][j]!=play1;j++){
			if(mat->mat[i][j]!=play2){//empty space
				not++;//sum emty space in the line
				line=i;//the line in the mat that empty space is
				column=j;//the column in the mat that empty space is
			}
		}
		if(not==1&&j==mat->width){//deficient only 1 space
			mat->mat[line][column]=o;//to win or block
			return 1;
		}
	}
	return 0;//o can't win or block
}
int column(board* mat,int play1,int play2){
	int i,j,not,line,column;
	for(j=0;j<mat->width;j++){
		for(not=0,i=0;i<mat->height&&not<2&&mat->mat[i][j]!=play1;i++){
			if(mat->mat[i][j]!=play2){//empty space
				not++;//sum emty space 
				line=i;//the line in the mat that empty space is
				column=j;//the column in the mat that empty space is
			}
		}
		if(not==1&&i==mat->height){//deficient only 1 place to o to win
			mat->mat[line][column]=o;//to win or block
			return 1;
		}
	}
	return 0;//o can't win or block
}
int diagonal_1(board* mat,int play1,int play2){
	int i,j,not=0,line,column;
	if(mat->height==mat->width){
		for(i=0,j=0;i<mat->height&&mat->mat[i][j]!=play1&&not<2;i++,j++){
			if(mat->mat[i][j]!=play2){//empty space in the diagonal
				not++;//sum empty space
				line=i;//the line of the empty space
				column=j;//the column of the empty space
			}
		}
		if(not==1&&j==mat->width){//deficient 1 space to win
			mat->mat[line][column]=o;//to win or block
			return 1;
		}
	}
	return 0;//o can't to win or block
}
int diagonal_2(board* mat,int play1,int play2){
	int i,j,not=0,line,column;
	if(mat->height==mat->width){
		for(i=0,j=mat->width-1;i<mat->height&&mat->mat[i][j]!=play1&&not<2;i++,j--){
			if(mat->mat[i][j]!=play2){//empty space in the diagonal
				not++;//sum empty space
				line=i;//the line of the empty space
				column=j;//the column of the empty space
			}
		}
		if(not==1&&i==mat->height){//deficient 1 space to win
			mat->mat[line][column]=o;//to win or block
			return 1;
		}
	}
	return 0;//o can't to win or block
}
void oPlay(board* mat){
	int i,j,stop=1;
	for(i=0;i<mat->height&&stop;i++)
		for(j=0;j<mat->width&&stop;j++)
			if(mat->mat[i][j]!=o&&mat->mat[i][j]!=x){//empty space
				mat->mat[i][j]=o;//o play this turn
				stop=0;
			}
}
int xWin(board* mat){
	int i,j,sum;
	for(i=0;i<mat->height;i++){
		for(sum=0,j=0;j<mat->width&&mat->mat[i][j]==x;j++)
			sum++;//sum how much x in line
		if(sum==mat->width)//x win
			return 0;
	}
	for(i=0;i<mat->width;i++){
		for(sum=0,j=0;j<mat->height&&mat->mat[j][i]==x;j++)
			sum++;//sum how much x in column
		if(sum==mat->height)//x win
			return 0;
	}
	return winDiagonal(mat);
}
int winDiagonal(board* mat){
	int i,j,win1=1,win2=1;
	if(mat->height==mat->width){
		for(i=0,j=0;i<mat->height;i++,j++)//the diagonal not full x
			if(mat->mat[i][j]!=x)
				win1=0;//x no win
		for(i=0,j=mat->width-1;i<mat->height;i++,j--)//the diagonal not full x
			if(mat->mat[i][j]!=x)
				win2=0;//x no win
		if(win1==0&&win2==0) 
			return 1;
		return 0;//x win
	}
	else 
		return 1;//x can't win on this way
}
int fullBoard(board* mat){
	int i,j;
	for(i=0;i<mat->height;i++)
		for(j=0;j<mat->width;j++)
			if(mat->mat[i][j]!=o&&mat->mat[i][j]!=x)//there is empty space in the board
				return 1;
	printf("draw\n");//anyone no win
	return 0;//the board is full
}
void freeChart(board* mat){
	int i;
	for(i=0;i<mat->height;i++){
		free(mat->mat[i]);//free each line
		g--;
	}
	free(mat->mat);//free line of pointers
	g--;//updatinf allocation count
	mat->mat=NULL;//updating board pointer
	mat->height=mat->width=0;//updating sizes
	printf("Allocation status: %d\n",g);
}