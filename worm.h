#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <curses.h>

#define SECOND		1000000		// 1 second in NCurses.
#define SHOW_INTRO		FALSE

#define DIFICULTY_EASY		1
#define DIFICULTY_MEDIUM		2
#define DIFICULTY_HARD		3

#define FOOD		'x'
#define WORMUP			'^'
#define WORMDOWN 		'v'
#define WORMLEFT 		'<'
#define WORMRIGHT 		'>'
#define WORMSEGMENT 'o'

#define WORLD_CORNER 			'+'
#define WORLD_HORIZONTAL_WALL	'-'
#define WORLD_VERTICAL_WALL 	'|'
#define WORLD_EMPTY_SPACE		' '

// Larger dimensions cause stack overflows (malloc* knowledge needed).
#define WORLD_LARGE_Y		24
#define WORLD_LARGE_X		34
#define WORLD_MEDIUM_Y		20
#define WORLD_MEDIUM_X		24
#define WORLD_SMALL_Y		16
#define WORLD_SMALL_X		20


/*WORM BEHAVIOR*/
void InputRespond (char *wrm_headTurn);
int DidILose(
	int wrm_head_Y, int wrm_head_X, int *wrm_allPos_YX[], int wrm_len, int world_Y, int world_X);
void IsItFood(
	int *wrm_head_Y, int *wrm_head_X, int *wrm_allPos_YX[], int *wrm_len, int food_max, 
	int *food_no, int *score, int score_Y, int score_X, int *food_YX[], int world_Y, int world_X);
void AddSegment (int newLoc_Y, int newLoc_X, int *wrm_len, int *wrm_allPos_YX[]);
void MoveWorm(
	int *wrm_head_Y, int *wrm_head_X, char *wrm_headTurn, int *wrm_allPos_YX[], int wrm_len);
void MoveSegments (int pos_Y, int pos_X, int *wrm_allPos_YX[], int wrm_len);

/*WORLD_GEN*/
void SpawnFood(
	int wrm_head_Y, int wrm_head_X, 
	int *wrm_allPos_YX[], int wrm_len, int world_Y, 
	int world_X, int food_max, int *food_no, int *food_YX[]);
void PlaceWorm(
	int *wrm_head_Y, int *wrm_head_X, char *wrm_headTurn, 
	int *wrm_allPos_YX[], int *wrm_len, int world_Y, int world_X);
void CreateWorld (int world_Y, int world_X, char *world[]);

/*GRAPHICS*/
void DrawAssets(
	int wrm_head_Y, int wrm_head_X, char wrm_headTurn, 
	int *wrm_allPos_YX[], int wrm_len, int food_no, int *food_YX[]);
void ShowIntro (int scrnMax_Y, int scrnMax_X);
void GetDificulty (int *dificulty, int *wrm_step_len, int scrnMax_Y, int scrnMax_X);
void GetWorldSize(
	int *gameActive, int *food_max, 
	int *world_Y, int *world_X, int scrnMax_Y, int scrnMax_X);

void CharArray2d_Draw (int arr_Y, int arr_X, char arr[][arr_Y]);
void CharArrayPtr_Draw (int arr_Y, int arr_X, char *arr[arr_Y]);
void CharArrayPtr_ColumnFill (int lineNo, int startCol, int endCol, char *Array_2D[], char fillWithMe);

void IntArray_Fill (int array[], int array_length, int fill_with_this);
void IntArray2d_ColumnFill(
	int lineNo, int startCol, int endCol, 
	int total_cols, int Array_2D[][total_cols], int fillWithMe);
