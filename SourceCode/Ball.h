#ifndef _BALL_H_
#define _BALL_H_
#include "Sprites.h"
#include <ctime>

class Ball {
	Sprite *sprite;
	list<int> ColList;
	int currRow;
	int currCol;
	int prevRow;
	int prevCol;
public:
	void Create(string id, int x, int y) {
		AnimationFilm* film = GetFilm();
		sprite = new Sprite(id, film, x, y, 38, 43, 20); 
		spriteList.Insert(sprite);
	}
	
	void SetFrame(unsigned FrameNo) {
		sprite->SetFrame(FrameNo);
	}
	void SetX(int x) {
		sprite->SetX(x);
	}
	void SetY(int y) {
		sprite->SetY(y);
	}
	Sprite* GetSprite() {
		return sprite;
	}

	int GetCurrRow() {
		return currRow;
	}
	int GetCurrCol() {
		return currCol;
	}

	void SetCurrRow(int x) {
		currRow=x;
	}
	void SetCurrCol(int x) {
		currCol=x;
	}

	int GetPrevRow() {
		return prevRow;
	}
	int GetPrevCol() {
		return prevCol;
	}
	void SetPrevRow(int x) {
		prevRow = x;
	}
	void SetPrevCol(int x) {
		prevCol=x;
	}
	void SetColList(list<int>& ColList) {
		assert((this->ColList.empty()));
		this->ColList.assign(ColList.begin(), ColList.end());
	}
	list<int> GetColList() {
		return ColList;
	}
	void UpdateRowCol(int row, int col) {
		prevRow = currRow;
		prevCol = currCol;
		currRow = row;
		currCol = col;
	}

	void Destroy(){} //!!!!!!!!!!!! kathe fora pou feygei kapoio ball apo to window

	AnimationFilm* GetFilm() {
		AnimationFilm* film = AnimationFilmHolder::Get().GetFilm("balls");
		if (film == nullptr) {
			SDL_Rect rect;
			rect.x = 0;
			rect.y = 0;
			rect.h = 13;
			rect.w = 13;
			vector<SDL_Rect> boxes;
			boxes.push_back(rect);
			rect.x = 13;
			rect.y = 0;
			rect.h = 13;
			rect.w = 13;
			boxes.push_back(rect);
			rect.x = 26;
			rect.y = 0;
			rect.h = 13;
			rect.w = 10;
			boxes.push_back(rect);
			rect.x = 36;
			rect.y = 0;
			rect.h = 13;
			rect.w = 10;
			boxes.push_back(rect);
			rect.x = 46;
			rect.y = 0;
			rect.h = 13;
			rect.w = 16;
			boxes.push_back(rect);
			rect.x = 62;
			rect.y = 0;
			rect.h = 13;
			rect.w = 18;
			boxes.push_back(rect);
			string id = "balls";
			AnimationFilmHolder::Get().Load(id, "Sprites/BallsFilm.bmp", boxes);
			film = AnimationFilmHolder::Get().GetFilm("balls");
		}
		return film;
	}

	Ball(char *id, int x, int y){
		Create(id, x, y);
		SetFrame(1);
	}

	Ball(string id, int x, int y) {
		Create(id, x, y);
		SetFrame(1);
	}


};


#endif
