#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
//default values
#define TILESIZE 25 
#define RECSIZE 22
#define MAXTAIL 369

//enum used for representing states of the player
typedef enum{None, Left, Right, Up, Down} State;

//structure of the player, as data needs to be encapsulated on a struct for these cases
typedef struct{
	 Rectangle head, tail[MAXTAIL];
	 int length;
	 State state, last_state;
	 bool win;
} Snake;

//mediocre random position generator for the food
void SetRandPos(Vector2 *ptr){
	ptr->x = 0;
	ptr->y = 0;
	int rx = GetRandomValue(0,11);
	int ry = GetRandomValue(0,11);
	for (int i = 0; i < rx; i++){
		ptr->x += TILESIZE;
	}
	for (int i = 0; i < ry; i++){
		ptr->y += TILESIZE;
	}
}

//initializes values to default
void InitSnake(Snake *ptr){
	ptr->head = (Rectangle){TILESIZE, TILESIZE, TILESIZE, TILESIZE}; //uhh i don't find this good-looking :(
	ptr->length = 0;
	ptr->state = None;
	ptr->last_state = None;
	ptr->win = false;
	for (int i = 0; i < MAXTAIL; i++){
		ptr->tail[i].x = -25;
		ptr->tail[i].y = -25;
	}
	
}

//updates the values of the game
void UpdateGame(Snake *snake, Vector2 *food){
	snake->last_state = snake->state;
	for (int i = snake->length ; i > 0; --i) {
		snake->tail[i] = snake->tail[i - 1];
		if (snake->tail[i].x == food->x && snake->tail[i].y == food->y){
			SetRandPos(food);
		}
		if (snake->head.x == snake->tail[i].x && snake->head.y == snake->tail[i].y){
			SetRandPos(food);
			snake->length = 0;
			snake->head.x = TILESIZE;
			snake->head.y = TILESIZE;
			snake->state = None;
		}
	}
	snake->tail[0].x = snake->head.x;
	snake->tail[0].y = snake->head.y;
	
	if (snake->head.x == food->x && snake->head.y == food->y){
		SetRandPos(food);
		snake->length += 1;
	}
	//wall handling
	if (snake->head.x > 300) snake->head.x = -25;
	if (snake->head.x < -25) snake->head.x = 300;
	if (snake->head.y < -25) snake->head.y = 300;
	if (snake->head.y > 300) snake->head.y = -25;
	//movement 
	if (snake->state == Left){
		snake->head.x -= TILESIZE;
	}else if (snake->state == Right){
		snake->head.x += TILESIZE;
	}else if (snake->state == Up){
		snake->head.y -= TILESIZE;
	}else if (snake->state == Down){
		snake->head.y += TILESIZE;	
	}
	//win stuff
	if (snake->length >= 369) snake->win = true;
	//keyboard management
	if (IsKeyPressed(KEY_D) && snake->last_state != Left) snake ->state = Right;
	else if (IsKeyPressed(KEY_A) && snake->last_state != Right) snake->state = Left;
	else if (IsKeyPressed(KEY_W) && snake->last_state != Down) snake->state = Up;
	else if (IsKeyPressed(KEY_S) && snake->last_state != Up) snake->state = Down;
}

//draw the contents of the game
void Drawing(Snake *player, Vector2 *food){
	for (int i = 0; i < player->length; ++i) {
		DrawRectangle(player->tail[i].x,player->tail[i].y, TILESIZE, TILESIZE, GREEN);
	}
	DrawRectangle(food->x, food->y, TILESIZE, TILESIZE , RED);
	DrawRectangleRec(player->head, GREEN);
	if (player->state == None){
		DrawText("Sneik!", 90, 120, 40, WHITE);
		DrawText("Keys: WSAD", 3, 260, 20, WHITE);
		DrawText("Runt1m3_ 2024, GNU GPL v2.0", 3, 280, 20, WHITE);
	}else{
		if (player->head.y < 150){
			DrawText(TextFormat("Score: %d", player->length), 3, 3, 20, WHITE);
		}else{
			DrawText(TextFormat("Score: %d", player->length), 3, 280, 20, WHITE);	
		}
	}
}

//initialize program and definition of used variables
int main(){	
	InitWindow(300,300,"Sneik!");
	SetTargetFPS(10); //rather crappy workaround of my ignorance on delaying movement

	Snake snake;
	Vector2 food = {0, 0};
	SetRandPos(&food);
	InitSnake(&snake);

	while (!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(DARKGREEN);
		//win state workaround 
		if (!snake.win){
			UpdateGame(&snake, &food); 
			Drawing(&snake, &food);
		}else{
			ClearBackground(RED);
			DrawText("You won! Unbelivable!", 43, 125, 20, WHITE);
			DrawText("Press space to exit", 43, 145, 20, WHITE);
			if (IsKeyPressed(KEY_SPACE)){
				exit(0);
			}
		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
