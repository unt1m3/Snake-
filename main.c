#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <string.h>
#include <time.h>
#define L 0
#define R 1
#define U 2
#define D 3



typedef struct{
	int x;
	int y;
} Block;

void RandPos(Block *block){
	srand(time(NULL));
	block->x = 0;
	block->y = 0;
	int rx = GetRandomValue(0,19);
	int ry = GetRandomValue(0,19);
	for (int i = 0; i < rx; i++){
		block->x += 25;
	}
	for (int i = 0; i < ry; i++){
		block->y += 25;
	}
}

typedef struct{
	Block tails[420];
	int x;
	int y;
	int d;
	int ld;
	int l;
} Player;

Player *CreatePlayer(){
	Player *tr = malloc(sizeof(Player));
	tr->x = 0;
	tr->y = 0;
	tr->d = 4;
	tr->l = 0;
	return tr;
}

void PlayerDraw(Player *player){
	DrawRectangle(player->x, player->y, 23, 23, GREEN);	
	for (int i = 0; i < player->l; ++i) {
		DrawRectangle(player->tails[i].x,player->tails[i].y, 23, 23, GREEN);
	}
}

void PlayerPhysics(Player *player, Block *food){
	for (int i = player->l ; i > 0; --i) {
		player->tails[i] = player->tails[i - 1];
	}
	player->tails[0].x = player->x;
	player->tails[0].y = player->y;

	if (player->x == food->x && player->y == food->y){
		player->l += 1;
		RandPos(food);
	}
	
	if (player->d == L){
		WaitTime(0.1);
		player->x -= 25;
	}else if (player->d == R){
		WaitTime(0.1);
		player->x += 25;	
	}else if (player->d == U){
		WaitTime(0.1);
		player->y -= 25;
	}else if (player->d == D){
		WaitTime(0.1);
		player->y += 25;			
	}
}

void PlayerKeys(Player *player){
	player->ld = player->d;
	if (IsKeyDown(KEY_D) && player->ld != L){
		player->d = R;
	}else if (IsKeyDown(KEY_A) && player->ld != R){
		player->d = L;
	}else if (IsKeyDown(KEY_W) && player->ld != D){
		player->d = U;
	}else if (IsKeyDown(KEY_S) && player->ld != U){
		player->d = D;
	}else if (IsKeyDown(KEY_L)){
		player->l += 1;
	}
}

int main(){
	InitWindow(500,500,"Snake!");
	SetTargetFPS(60);
	Player *player = CreatePlayer();
	Block food;
	RandPos(&food);
	while (!WindowShouldClose()){
		BeginDrawing();
		ClearBackground((Color){25,25,25,255});
		DrawRectangle(food.x,food.y, 23, 23, RED);
		if (IsKeyDown(KEY_K)){
			printf("%d %d\n",food.x,food.y);
		}
		PlayerDraw(player);
		PlayerPhysics(player,&food);
		PlayerKeys(player);
		EndDrawing();
	}	
	free(player);
	CloseWindow();
}
