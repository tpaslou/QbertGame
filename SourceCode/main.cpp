#include <iostream>
#include "Game.h"
#include "Sprites.h"
#include "Terrain.h"
#include "Qbert.h"
#include "Animation.h"
#include "Disk.h"
#include "Ball.h"
#include "AI.h"

#include "SDL.h"

//global
Game* game = nullptr;
SpriteList spriteList = SpriteList(); 

//static 
AnimationFilmHolder AnimationFilmHolder::holder = AnimationFilmHolder();
AnimatorHolder AnimatorHolder::animatorHolder = AnimatorHolder();
list<Animator*> AnimatorHolder::running;
list<Animator*> AnimatorHolder::suspended;

int AI::sum = 0;

void f() {
	game->init("Q*bert", 200, 40, 800, 700, 0, 0);
	SDL_Event event;
	int la = 1;
	while (la) {
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_UP) {
					//	game->init("Q*bert", 200, 40, 800, 700, 0, 1);
					la = 0;
					break;
				}
			case SDL_QUIT:
				game->SetRunning(false);
				break;
			default:
				break;
			}
		}
		game->render();
		game->update();
	}

}

int main(int argc, char* args[]) {
	game = new Game();
		f();
		game->init("Q*bert", 200, 40, 800, 700, 0, 1);
		IsometricPyramid *terrain = new IsometricPyramid(400, 80, 7, 26, 74);
		Qbert *qbert = new Qbert(377, 56);
		Disk *diskLeft = new Disk("DiskLeft", 70, 350);
		Disk *diskRight = new Disk("DiskRight", 680, 350);
		bool flag = false;
		//int count = 0;
		diskLeft->Spin();
		diskRight->Spin();
		game->SetGameTime();  // arxhkopoiw to game->currTime (den einai swsto ekei kai prepei na fygei apla to xrhsimopoiw gia na dwkomasw to Qbert::Animation())

		AI* ai = new AI(game->GetGameTime());
		game->SetSprite(terrain, qbert, diskLeft, diskRight, ai);
		unsigned count = 0;
		while (game->running()) {
			game->SetGameTime();
			game->handleEvents();
			game->update();
			game->render();
			game->Collision();
			if (game->lose) {
				(game->GameLife)--;
				game->Lose();
				if (!(game->GameLife)) {
					AnimationFilm* film = AnimationFilmHolder::Get().GetFilm("GameOver");
					if (film == nullptr) {
						SDL_Rect rect;
						vector<SDL_Rect> boxes;
						rect.x = 0;
						rect.y = 0;
						rect.h = 400;
						rect.w = 800;
						boxes.push_back(rect);

						string id = "GameOver";
						AnimationFilmHolder::Get().Load(id, "Sprites/gameOver.bmp", boxes);
					}
					film = AnimationFilmHolder::Get().GetFilm("GameOver");
					Sprite * gameOver = new Sprite("GameOver", film, 200, 200, 400, 100, 100);
					spriteList.Insert(gameOver);
					cout << "GAME OVERR" << endl;
				}
				game->Restart();
			}

			if (game->win) count++;
			if (game->GameLife <= 0 && !(game->win)) count++;

			if (count == 3000)
				break;
		}
		game->clean();
		return 0;
}


