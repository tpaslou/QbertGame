#ifndef _DISK_H_
#define _DISK_H_
#include "Sprites.h"
#include "Animation.h"


class MovingPathAnimatorDisk : public MovingPathAnimator {
public:
	virtual bool Progress(unsigned long currTime) {
		assert(currPathFrame);
		assert(anim);
		assert(sprite);
		while (currTime > lastTime && currTime - lastTime >= currPathFrame->delay) {
			currPathFrame = anim->GetNextPathFrame(currPathFrame);
			assert(currPathFrame);															 //NULL an den yparxei 
			sprite->Move(currPathFrame->dx, currPathFrame->dy);
			sprite->SetFrame(currPathFrame->frame);
			lastTime += currPathFrame->delay;

			if (currPathFrame == anim->GetEndPathFrame()) {
				if (cont)
					currPathFrame = anim->GetStartPathFrame();
				else {
					if (!(sprite->GetId().compare("DiskLeft_withQbert"))) {
						game->SetDiskLeftMoveTop(false);
					}
					else {
						game->SetDiskRightMoveTop(false);
					}
					spriteList.Remove(sprite);
					spriteList.Insert(game->qbert->GetSprite());
					state = ANIMATOR_FINISHED;
					NotifyStopped();
					return true;
				}
			}
		}
		return false;
	}


	MovingPathAnimatorDisk(Sprite* s, MovingPathAnimation* a) : MovingPathAnimator(s, a) {
		if (sprite->GetId().compare("DiskLeft")) {
			game->SetDiskLeftMoveTop(true);
		}
		else {
			game->SetDiskRightMoveTop(true);
		}
	}
};



class Disk {
	Sprite *DiskSprite;
	Sprite *QbertSprite;
	bool moveTop; 
	bool isActive;
	bool snakeLeft;
	bool snakeRight;
public:
	void Create(string id, int x, int y) {
		AnimationFilm* DiskFilm = GetFilm();								// fortonei to film tou aplou diskou 
		AnimationFilm* QbertFilm = GetFilm_withQbert();						// fortonei to film tou diskou me qbert
		DiskSprite = new Sprite(id + "_onlyDisk", DiskFilm, x, y, 47, 47, 15);	// diastaseis gia aplo disko
		QbertSprite = new Sprite(id + "_withQbert", QbertFilm, x, y, 66, 66, 15);	// diastaseis gia disko me qbert

		spriteList.Insert(DiskSprite);
	}

	void Spin() {
		std::list<PathEntry> path;
		PathEntry * p1 = new PathEntry(0, 0, 0, 250);
		PathEntry * p2 = new PathEntry(0, 0, 1, 250);
		PathEntry * p3 = new PathEntry(0, 0, 2, 250);
		PathEntry * p4 = new PathEntry(0, 0, 3, 250);
		for (int i = 0; i < 30; ++i) {
			path.push_back(*p1);
			path.push_back(*p2);
			path.push_back(*p3);
			path.push_back(*p4);
			
		}
		MovingPathAnimation * diskAnimation = new MovingPathAnimation(path, "disk_Animation1");
		MovingPathAnimator * diskAnimator = new MovingPathAnimator(DiskSprite, diskAnimation);
		diskAnimator->SetCont(true);
		diskAnimator->Start(game->GetGameTime());			
	}
	void MoveUpLeft() {
		moveTop = true;
		isActive = false;
		SetSnakeLeft(true);
		std::list<PathEntry> path;
		PathEntry * p = new PathEntry(-100, 0, 0, 500);
		path.push_back(*p);
		PathEntry * p1 = new PathEntry(20, -30, 0, 100);
		PathEntry * p2 = new PathEntry(20, -30, 1, 100);
		PathEntry * p3 = new PathEntry(20, -30, 2, 100);
		PathEntry * p4 = new PathEntry(20, -30, 3, 100);
		PathEntry * p5 = new PathEntry(20, -30, 4, 100); 
		PathEntry * p6 = new PathEntry(20, -30, 3, 100);
		for (int i = 0; i < 2; ++i) {
			path.push_back(*p1);
			path.push_back(*p2);
			path.push_back(*p3);
			path.push_back(*p4);
			path.push_back(*p5);
			path.push_back(*p6);
		}
		p6 = new PathEntry(30, 5, 5, 100);
		path.push_back(*p6);
		path.push_back(*p6);
		p1 = new PathEntry(0, 0, 4, 100);
	    p2 = new PathEntry(0, 0, 4, 100);
		p3 = new PathEntry(0, 0, 4, 100);
		p4 = new PathEntry(0, 0, 4, 100);
		p5 = new PathEntry(0, 0, 4, 100);
		p6 = new PathEntry(0, 0, 4, 100);
		for (int i = 0; i < 2; ++i) {
			path.push_back(*p1);
			path.push_back(*p2);
			path.push_back(*p3);
			path.push_back(*p4);
			path.push_back(*p5);
			path.push_back(*p6);
		}
		spriteList.Remove(DiskSprite);
		spriteList.Insert(QbertSprite);
		MovingPathAnimation * diskAnimation = new MovingPathAnimation(path, "disk_Animation1");
		MovingPathAnimator * diskAnimator = new MovingPathAnimatorDisk(QbertSprite, diskAnimation);
		diskAnimator->Start(game->GetGameTime());	
	}
	
	void MoveUpRight() {
		moveTop = true;
		isActive = false;
		SetSnakeRight(true);
		std::list<PathEntry> path;
		PathEntry * p = new PathEntry(0, 0, 0, 500);
		path.push_back(*p);
		PathEntry * p1 = new PathEntry(-20, -30, 0, 100);
		PathEntry * p2 = new PathEntry(-20, -30, 1, 100);
		PathEntry * p3 = new PathEntry(-20, -30, 2, 100);
		PathEntry * p4 = new PathEntry(-20, -30, 3, 100);
		PathEntry * p5 = new PathEntry(-20, -30, 4, 100);
		PathEntry * p6 = new PathEntry(-20, -30, 5, 100);
		for (int i = 0; i < 2; ++i) {
			path.push_back(*p1);
			path.push_back(*p2);
			path.push_back(*p3);
			path.push_back(*p4);
			path.push_back(*p5);
			path.push_back(*p6);
		}
		p6 = new PathEntry(-40, 0, 0, 100);
		path.push_back(*p6);
		path.push_back(*p6);
		p1 = new PathEntry(0, 0, 4, 100);
		p2 = new PathEntry(0, 0, 4, 100);
		p3 = new PathEntry(0, 0, 4, 100);
		p4 = new PathEntry(0, 0, 4, 100);
		p5 = new PathEntry(0, 0, 4, 100);
		p6 = new PathEntry(0, 0, 4, 100);
		for (int i = 0; i < 2; ++i) {
			path.push_back(*p1);
			path.push_back(*p2);
			path.push_back(*p3);
			path.push_back(*p4);
			path.push_back(*p5);
			path.push_back(*p6);
		}
		spriteList.Remove(DiskSprite);
		spriteList.Insert(QbertSprite);
		MovingPathAnimation * diskAnimation = new MovingPathAnimation(path, "disk_Animation1");
		MovingPathAnimator * diskAnimator = new MovingPathAnimatorDisk(QbertSprite, diskAnimation);
		diskAnimator->Start(game->GetGameTime());
	}

	void SetMoveTop(bool b) {
		moveTop = b;
	}
	void SetSnakeLeft(bool b) {
		if ((b && game->GetSnake() && game->GetSnakeIsBall()) || (b && !(game->GetSnake()))) return;
		snakeLeft = b;
	}
	void SetSnakeRight(bool b) {
		if ((b && game->GetSnake() && game->GetSnakeIsBall()) || (b && !(game->GetSnake()))) return;
		snakeRight = b;
	}
	bool GetSnakeLeft() {
		return snakeLeft;
	}
	bool GetSnakeRight() {
		return snakeRight;
	}
	bool GetMoveTop() {
		return moveTop;
	}
	bool GetIsActive() {
		return isActive;
	}
	
	AnimationFilm* GetFilm() {
		AnimationFilm* film = AnimationFilmHolder::Get().GetFilm("disks");
		if (film == nullptr) {
			SDL_Rect rect;
			rect.x = 0;
			rect.y = 0;
			rect.h = 18;
			rect.w = 16;
			vector<SDL_Rect> boxes;
			boxes.push_back(rect);
			rect.x = 16;
			rect.y = 0;
			rect.h = 18;
			rect.w = 16;
			boxes.push_back(rect);
			rect.x = 32;
			rect.y = 0;
			rect.h = 18;
			rect.w = 16;
			boxes.push_back(rect);
			rect.x = 48;
			rect.y = 0;
			rect.h = 18;
			rect.w = 16;
			boxes.push_back(rect);
			rect.x = 64;
			rect.y = 0;
			rect.h = 18;
			rect.w = 16;
			boxes.push_back(rect);
			string id = "disks";
			AnimationFilmHolder::Get().Load(id, "Sprites/DisksFilm.bmp", boxes);
			film = AnimationFilmHolder::Get().GetFilm("disks");
		}
		return film;
	}

	AnimationFilm* GetFilm_withQbert() {
		AnimationFilm* film = AnimationFilmHolder::Get().GetFilm("spinning_qbert");
		if (film == nullptr) {
			SDL_Rect rect;
			vector<SDL_Rect> boxes;
			rect.x = 0;
			rect.y = 0;
			rect.h = 35;
			rect.w = 35;
			boxes.push_back(rect);
			rect.x = 35;
			rect.y = 0;
			rect.h = 35;
			rect.w = 35;
			boxes.push_back(rect);
			rect.x = 67;
			rect.y = 0;
			rect.h = 35;
			rect.w = 34;
			boxes.push_back(rect);
			rect.x = 96;
			rect.y = 0;
			rect.h = 35;
			rect.w = 35;
			boxes.push_back(rect);
			rect.x = 128;
			rect.y = 0;
			rect.h = 35;
			rect.w = 35;
			boxes.push_back(rect);
			rect.x = 160;
			rect.y = 0;
			rect.h = 35;
			rect.w = 36;
			boxes.push_back(rect);
			string id = "spinning_qbert";
			AnimationFilmHolder::Get().Load(id, "Sprites/spinning_qbert.bmp", boxes);
			film = AnimationFilmHolder::Get().GetFilm("spinning_qbert");
		}
		return film;
	}

	Disk(string id,int x, int y) {
		Create(id, x, y);
		moveTop = false;
		isActive = true;
		snakeLeft = false;
		snakeRight = false;
	}

	Disk(char *id, int x, int y) {
		Create(id, x, y);
		moveTop = false;
		isActive = true;
		snakeLeft = false;
		snakeRight = false;
	}
};


// m_sourceRectangle.x = 128 * int(((SDL_GetTicks() / 100) % 6)); 

#endif