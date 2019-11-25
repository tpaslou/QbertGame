#ifndef _SPRITE_H_
#define _SPRITE_H_
#include <SDL.h>
#include <iostream>
#include <map>
#include <assert.h>
#include <vector>
#include "Game.h"
#include "List"

using namespace std;

class AnimationFilm {
	vector<SDL_Rect> boxes; //SDL_Rect sourceRect for each frame
	SDL_Texture* bitmap; // to film
	string id;
public:
	int GetTotalFrames() {
		return boxes.size();
	}

	const string GetId(void) const {
		return id;
	}
	SDL_Texture* GetBitmap() {
		return bitmap;
	}

	const SDL_Rect GetFrameBox(unsigned frameNo) const {
		assert(frameNo < boxes.size());
		return boxes[frameNo];
	}

	void DisplayFrame(const int x, const int y, SDL_Rect& sousceRect, SDL_Rect& destRect, unsigned frameNo) const { //x , y -->at
		sousceRect = boxes[frameNo];
		destRect.x = x;
		destRect.y = y;
	}

	AnimationFilm(SDL_Texture* bitmap, const vector<SDL_Rect> boxes, string& id) {
		this->bitmap = bitmap;
		this->boxes = boxes;
		this->id = id;
	}

};


class BitmapLoader {
	typedef map<string, SDL_Texture*> Bitmaps;
	Bitmaps bitmaps;

	SDL_Texture* GetBitmap(const string path) {
		Bitmaps::const_iterator i = bitmaps.find(path);
		return i != bitmaps.end() ? i->second : nullptr;
	}

	SDL_Texture*  LoadBitmap(const char *path) {
		SDL_Surface* TempSurface = SDL_LoadBMP(path);
		SDL_Texture* Texture = SDL_CreateTextureFromSurface(game->GetRenderer(), TempSurface);
		SDL_FreeSurface(TempSurface);
		return Texture;
	}

	void DestroyBitmap(SDL_Texture* bitmap) {
		///// elena prepei na kanei kati sto telos gia destroy twn texture??
	}

public:
	SDL_Texture * Load(const char *path) {
		SDL_Texture* b = GetBitmap(path);
		if (!b) {
			b = LoadBitmap(path);
			bitmaps[path] = b;
			assert(b);
		}
		return b;
	}

	void CleanUp() {
		for (Bitmaps::iterator i = bitmaps.begin(); i != bitmaps.end(); ++i) {
			DestroyBitmap(i->second);
		}
		bitmaps.clear();
	}

	BitmapLoader() {}
	~BitmapLoader() { CleanUp(); }
};


class AnimationFilmHolder {
	typedef map<string, AnimationFilm*> Films;
	Films films;
	BitmapLoader bitmaps; // for loading 
	static AnimationFilmHolder holder; // singleton

	AnimationFilmHolder() {};
	~AnimationFilmHolder() { CleanUp(); };

public:
	static AnimationFilmHolder& Get() {
		return holder;
	}

	void Load(string& id, const char * path, vector<SDL_Rect> boxes) {
		SDL_Texture* bmp = bitmaps.Load(path);
		assert(!GetFilm(id));
		films[id] = new AnimationFilm(bmp, boxes, id);
	}

	void CleanUp() {
		for (Films::iterator i = films.begin(); i != films.end(); ++i) {
			delete(i->second); 
		}
		films.clear();
	}

	AnimationFilm* GetFilm(const string id) const {
		Films::const_iterator i = films.find(id);
		return i != films.end() ? i->second : nullptr;
	}
};


class Sprite {
	string id;
	unsigned frameNo; // se pio frame ftanw apo to Animation film
	SDL_Rect destinationRect;
	SDL_Rect sourceRect; // framebox
	AnimationFilm *currFilm;
	unsigned zOrder;
	bool isVisible;

public:
	void SetFrame(int i) {
		if (i != frameNo) {
			assert(i < currFilm->GetTotalFrames());
			frameNo = i;
			sourceRect = currFilm->GetFrameBox(i);
		}
	}
	void SetVisibility(bool v) {
		isVisible = v;
	}
	void SetZOrder(unsigned zOrder) {
		this->zOrder = zOrder;
	}
	void SetX(int x) {
		destinationRect.x = x;
	}
	void SetY(int y) {
		destinationRect.y = y;
	}
	void SetFilm(AnimationFilm *film) {
		currFilm = film;
	}

	unsigned GetFrame(void) const {
		return frameNo;
	}
	SDL_Rect& GetDestinationRect() {
		return destinationRect;
	}
	SDL_Rect& GetSourceRect() {
		return sourceRect;
	}
	AnimationFilm *GetCurrFilm() {
		return currFilm;
	}
	unsigned GetzOrder() {
		return zOrder;
	}
	string GetId() {
		return id;
	}
	bool IsVisible(void) const {
		return isVisible;
	}

	virtual void Move(int dx,int dy) {
		assert(destinationRect.x + dx >= 0);
		//assert(destinationRect.y + dy >= 0);
		destinationRect.x += dx;
		destinationRect.y += dy;
	}

	virtual bool CollisionCheck(Sprite* s) {
		assert(s);
		int x = destinationRect.x;
		int y = destinationRect.y;
		int h = destinationRect.h;
		int w = destinationRect.w;
		int sx = s->GetDestinationRect().x;
		int sy = s->GetDestinationRect().y;
		int sw = s->GetDestinationRect().w;
		int sh = s->GetDestinationRect().h;
		if (x <= sx && sx <= x + w && y <= sy && sy <= y + h)
		{
			if (!strcmp(s->GetId().c_str(), "Snake"))
				cout << "COLLISION 1 with " << s->GetId().c_str() << ": " << sx << ", " << sy << "  Qbert: " << x << ", " << y << endl;
			return true;
		}
		else if	(sx <= x && x <= sx + sw && sy <= y && y <= sy + sh) {
			if (!strcmp(s->GetId().c_str(), "Snake"))
				cout << "COLLISION 2 with " << s->GetId().c_str() << ": " << sx << ", " << sy << "  Qbert: " << x << ", " << y << endl;
			return true;
		}
		else if (x <= sx + sw && sx + sw <= x + w && y <= sy + sh && sy + sh <= y + h) {
			if (!strcmp(s->GetId().c_str(), "Snake"))
				cout << "COLLISION 3 with " << s->GetId().c_str() << ": " << sx << ", " << sy << "  Qbert: " << x << ", " << y << endl;
			return true;
		}
		else if(sx <= x + w && x + w <= sx + sw && sy <= y + h && y + h <= sy + sh) {
			if (!strcmp(s->GetId().c_str(), "Snake"))
				cout << "COLLISION 4 with " << s->GetId().c_str() << ": " << sx << ", " << sy << "  Qbert: " << x << ", " << y << endl;
			return true;
		}
	/*	else if(sx <= x && x <= sx + sw && sy <= y + h && y + h <= sy + sh) {  // apo panw mikros Qbert
			if (!strcmp(s->GetId().c_str(), "Snake"))
				cout << "COLLISION 5 with " << s->GetId().c_str() << ": " << sx << ", " << sy << "  Qbert: " << x << ", " << y << endl;
			return true;
		}*/			
		else if (sx <= x && sx + sw && sy <= y && y <= sy + sh)	{					// apo katw mikros Qbert
			if (!strcmp(s->GetId().c_str(), "Snake"))
				cout << "COLLISION 6 with " << s->GetId().c_str() << ": " << sx << ", " << sy << "  Qbert: " << x << ", " << y << endl;
			return true;
		}
		else if(x <= sx && sx <= x + w && y <= sy + sh && sy + sh <= y + h){			// apo katw mikro sprite
				if (!strcmp(s->GetId().c_str(), "Snake"))
					cout << "COLLISION 7 with " << s->GetId().c_str() << ": " << sx << ", " << sy << "  Qbert: " << x << ", " << y << endl;
			return true;
		}
		else if (x <= sx && sx <= x + w && y <= sy && sy <= y + h) {					// apo panw mikro sprite 
			if(!strcmp(s->GetId().c_str(), "Snake"))
			cout << "COLLISION  8 with " << s->GetId().c_str() << ": " << sx << ", " << sy << "  Qbert: " << x << ", " << y << endl;
			return true;
		}
		if (x >= sx && x + w <= sx + sw && y >= sy && y + h <= sy + sh) {			// Qbert mesa se sprite
			if (!strcmp(s->GetId().c_str(), "Snake"))
				cout << "COLLISION 9 with " << s->GetId().c_str() << ": " << sx << ", " << sy << "  Qbert: " << x << ", " << y << endl;
			return true;
		}
		else if (sx >= x && sx + sw <= x + w && sy >= y && sy + sh <= y + h) {			// sprite mesa se Qbert
		//	) {
			if(!strcmp(s->GetId().c_str(), "Snake"))
				cout << "COLLISION 10 with " << s->GetId().c_str() << ": " << sx << ", " << sy << "  Qbert: " << x << ", " << y << endl;
			return true;
		}
		return false;
	}

	virtual void Display(const int x, const int y) {
		currFilm->DisplayFrame(x, y, sourceRect, destinationRect, frameNo);
		SDL_RenderCopy(game->GetRenderer(), this->currFilm->GetBitmap(), &sourceRect, &destinationRect);
	}

	virtual void Display() {
		currFilm->DisplayFrame(destinationRect.x, destinationRect.y, sourceRect, destinationRect, frameNo);
		SDL_RenderCopy(game->GetRenderer(), this->currFilm->GetBitmap(), &sourceRect, &destinationRect);
	}

	Sprite(string id, AnimationFilm* film, int x, int y, int w, int h, unsigned zorder) {
		this->id = id;
		destinationRect.x = x;	// pou na mpei sto window
		destinationRect.y = y;
		destinationRect.w = w;
		destinationRect.h = h;
		isVisible = true;
		currFilm = film;
		zOrder = zorder;
		SetFrame(0);
	}

	Sprite(const char *id, AnimationFilm* film, int x, int y, int w, int h, unsigned zorder) {
		this->id = id;
		destinationRect.x = x;	// pou na mpei sto window
		destinationRect.y = y;
		destinationRect.w = w;
		destinationRect.h = h;
		isVisible = true;
		currFilm = film;
		zOrder = zorder;
		SetFrame(0);
	}
};

//gia spritelist
bool compare(Sprite* s1, Sprite* s2);

class SpriteList  final  { 
	list<Sprite *> list;
public:

	
	void Insert(Sprite* s) { // sorted by zOrder of each sprite
		list.push_back(s);
		list.sort(compare);
	}


	Sprite* Get(string id) {
		for (auto i = list.begin(); i != list.end(); ++i) {
			if ((*i)->GetId()== id) {
				return *i;
			}
		}
		return nullptr;
	}

	void Remove(Sprite* s){
		for (auto i = list.begin(); i != list.end(); ++i) {
			if (*i == s) {
				list.remove(*i);
				return;
			}
		}
		assert(0);
	}

	std::list<Sprite *>& GetList() {
		return list;
	}

	void Collision(Sprite * s) {
		for (auto i = list.begin(); i != list.end(); ++i) {
			//cout << "eeee" << endl;
			if ((*i) == s) {
				continue;
			}
			else if (s->CollisionCheck(*i)) {
			//collision
			}
		}
	}


	void Display() {
		for (auto i = list.begin(); i != list.end(); ++i) {
			(*i)->Display();
		}
	}
};


class CubeSprite : public Sprite {
	unsigned row;
	unsigned col;
	unsigned ys;	// the top left pixel of the entire row of isocubes
	unsigned xs;
	unsigned yc;	// center 
	unsigned xc;
	bool active = false;
public:
	void SetXs(unsigned xs) {
		this->xs = xs;
	}
	void SetYs(unsigned ys) {
		this->ys = ys;
	}
	void SetXc(unsigned xc) {
	this->xc = xc;
	}
	void SetYc(unsigned yc) {
		this->yc = yc;
	}
	void SetActive() {
		active = true;
	}
	void SetInactive() {
		active =false;
	}
	bool isActive() {
		return active;
	}
	int getRow() {
		return row;
	}
	int getCol() {
		return col;
	}
	CubeSprite(string id, AnimationFilm* film, int x, int y, int w, int h, unsigned zorder, unsigned  row, unsigned col) : 
		Sprite(id, film, x, y, w, h, zorder) {
		this->row = row;
		this->col = col;
		SetFrame(4);
	}
	CubeSprite(char* id, AnimationFilm* film, int x, int y, int w, int h, unsigned zorder, unsigned  row, unsigned col) :
		Sprite(id, film, x, y, w, h, zorder) {
		this->row = row;
		this->col = col;
	}
};

extern SpriteList spriteList;

#endif
