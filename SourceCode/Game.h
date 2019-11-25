#ifndef __GAME_H__
#define __GAME_H__
#include <iostream>
#include <SDL.h>
#include <ctime>


using namespace std;

class Qbert;
class IsometricPyramid;
class Disk;
class AI;
class Snake;
class Ball;
class Sprite;


class Game {
	unsigned long currTime = 0;
	enum game_states {
		PAUSE = 0,
		PLAY = 1,
		GAMEOVER = 2,
		START = 3
	};
public:
	IsometricPyramid * terrain;
	Qbert *qbert;
	Disk *diskLeft;
	Disk *diskRight;
	AI *ai;
	bool lose = false;
	bool win = false;
	game_states game_state;
	unsigned int GameLife = 3;
	unsigned int decreaseStop = 0;
	Game();
	~Game();
	void LoseLife();
	// simply set the running variable to true  
	bool init(const char* title, int xpos, int ypos, int width, int height, int flags,int flag);
	void render();
	void update();
	void handleEvents();
	void clean();
	void Collision();
	void SetSprite(	IsometricPyramid *terrain,
					Qbert *qbert,
					Disk *diskLeft,
					Disk *diskRight,
					AI *ai);
	void SetGameTime();
	void SetDiskRightMoveTop(bool b);
	void SetDiskLeftMoveTop(bool b);
	void SetRunning(bool b);
	unsigned long GetGameTime();
	AI* GetAI();
	Snake * GetSnake();
	Ball * GetBall(Sprite *s);
	bool GetSnakeIsBall();
	void SetSnakeIsBall(bool b);
	void Lose();
	void Restart();
	void SetQbertToStart();
	int GetQbertRow();
	int GetQbertCol();
	// a function to access the private running variable   
	bool running(){ return m_bRunning; }
	SDL_Renderer* GetRenderer();

private:
	SDL_Window * m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture; // the new SDL_Texture variable 
	SDL_Rect m_sourceRectangle; // the first rectangle 
	SDL_Rect m_destinationRectangle; // another rectangle
	SDL_Texture* m_pTexture1; // the new SDL_Texture variable 
	SDL_Rect m_sourceRectangle1; // the first rectangle 
	SDL_Rect m_destinationRectangle1; // another rectangle
	SDL_Texture* m_pTexture2; // the new SDL_Texture variable 
	SDL_Rect m_sourceRectangle2; // the first rectangle 
	SDL_Rect m_destinationRectangle2; // another rectangle
	SDL_Texture* m_pTexture3; // the new SDL_Texture variable 
	SDL_Rect m_sourceRectangle3; // the first rectangle 
	SDL_Rect m_destinationRectangle3; // another rectangle
	bool m_bRunning;
};

extern Game* game;

#endif
