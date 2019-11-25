#ifndef _AI_H_
#define _AI_H_
#include <list>
#include "Ball.h"
#include "Animation.h"
#include "Disk.h"
#include "SoundManager.h"


class Snake {
	Sprite *sprite;
	Sprite * SnakeSprite;
	MovingPathAnimation* Animation;
	MovingPathAnimator* Animator;
	MovingPathAnimation* SnakeAnimation;
	MovingPathAnimator* SnakeAnimator;
	list<int> ColList;
	int currRow;
	int currCol;
	int prevRow;
	int prevCol;
	bool isBall;
public:
	void Create(int x, int y) {
		AnimationFilm* film = GetFilmBall();
		sprite = new Sprite("SnakeBall", film, x, y, 38, 43, 20);
		AnimationFilm* film2 = GetFilmSnake();
		SnakeSprite = new Sprite("Snake", film2, 0, 0, 38, 50, 20);  //  den to vazw sthn sprite list  -- prepei na allaksw kai position
		spriteList.Insert(sprite);
	}


	void SetCurrRow(int x) {
		currRow = x;
	}
	void SetCurrCol(int x) {
		currCol = x;
	}
	void SetPrevRow(int x) {
		prevRow = x;
	}
	void SetPrevCol(int x) {
		prevCol = x;
	}
	void SetFrame(unsigned FrameNo) {
		sprite->SetFrame(FrameNo);
	}
	void SetBallX(int x) {
		sprite->SetX(x);
	}
	void SetBallY(int y) {
		sprite->SetY(y);
	}
	void SetFilmSnake() {
		sprite->SetFilm(GetFilmSnake());
	}
	void SetFilmBall() {
		sprite->SetFilm(GetFilmBall());
	}
	void SetAnimation(MovingPathAnimation* a) {
		Animation = a;
	}
	void SetAnimator(MovingPathAnimator* a) {
		Animator = a;
	}
	void SetSnakeAnimation(MovingPathAnimation* a) {
		SnakeAnimation = a;
	}
	void SetSnakeAnimator(MovingPathAnimator* a) {
		SnakeAnimator = a;
	}
	void SetColList(list<int>& ColList) {
		assert((this->ColList.empty()));
		this->ColList.assign(ColList.begin(), ColList.end());
	}

	list<int> GetColList() {
		return ColList;
	}
	int GetCurrRow() {
		return currRow;
	}
	int GetCurrCol() {
		return currCol;
	}
	int GetPrevRow() {
		return prevRow;
	}
	int GetPrevCol() {
		return prevCol;
	}
	Sprite* GetSprite() {
		return sprite;
	}
	Sprite * GetSnakeSprite() {
		return SnakeSprite;
	}
	MovingPathAnimation * GetAnimation() {
		return Animation;
	}
	MovingPathAnimator* GetAnimator() {
		return Animator;
	}
	MovingPathAnimation * GetSnakeAnimation() {
		return SnakeAnimation;
	}
	MovingPathAnimator* GetSnakeAnimator() {
		return SnakeAnimator;
	}

	void SnakeAI() {
		int qbertRow = game->qbert->GetCurrRow();
		int qbertCol = game->qbert->GetCurrCol();
		list<PathEntry> path;
		if (game->diskLeft->GetSnakeLeft()) {
			qbertRow = 5;
			qbertCol = 1;
			if (currCol == 1 && currRow == 5) {
				cout << "RIP SNAKE LEFT";
				//jump left
				list<PathEntry> path;
				PathEntry *p1 = new PathEntry(0, 0, 5, 0);
				PathEntry *p2 = new PathEntry(-6, 0, 5, 0);
				PathEntry *p3 = new PathEntry(-20, -70, 5, 100);
				PathEntry *p4 = new PathEntry(-40, 0, 5, 70);
				PathEntry *p5 = new PathEntry(-10, 105, 5, 50);
				PathEntry *p6 = new PathEntry(0, 0, 5, 0);
				path.push_back(*p1);
				path.push_back(*p2);
				path.push_back(*p3);
				path.push_back(*p4);
				path.push_back(*p5);
				path.push_back(*p6);
				PathEntry *p;
				for (int i = 0; i < 30; ++i) {
					p = new PathEntry(0, 25,5, 60);
					path.push_back(*p);
				}

				SnakeSprite->SetZOrder(5);
				spriteList.GetList().sort(compare);
				SnakeAnimation->SetPath(path);
				currCol = 0;
				return;
			}
			else if (currCol == 0) {
				game->diskLeft->SetSnakeLeft(false);
				Animator->SetState(ANIMATOR_READY);
				return;
			}
		}
		else if (game->diskRight->GetSnakeRight()) {
			qbertRow = 5;
			qbertCol = 5;
			if (currCol == 5 && currRow == 5) {
				//jump left
				list<PathEntry> path;
				PathEntry *p1 = new PathEntry(0, 0, 5, 0);
				PathEntry *p2 = new PathEntry(0, 0, 5, 0);
				PathEntry *p3 = new PathEntry(20, -30, 5, 100);
				PathEntry *p4 = new PathEntry(0, -20, 5, 70);
				PathEntry *p5 = new PathEntry(40, -5, 5, 50);
				PathEntry *p6 = new PathEntry(0, 0, 5, 0);
				path.push_back(*p1);
				path.push_back(*p2);
				path.push_back(*p3);
				path.push_back(*p4);
				path.push_back(*p5);
				path.push_back(*p6);
				PathEntry *p;
				for (int i = 0; i < 30; ++i) {
					p = new PathEntry(0, 25, 1, 60);
					path.push_back(*p);
				}
				SnakeSprite->SetZOrder(5);
				spriteList.GetList().sort(compare);
				SnakeAnimation->SetPath(path);
				currCol = 0;
				return;
			}
			else if (currCol == 0) {
				game->diskRight->SetSnakeRight(false);
				Animator->SetState(ANIMATOR_READY);
				return;
			}
		}


		if (currRow >= qbertRow) {
			if (currCol <= qbertCol) {
				pathUpRight(&path);
				prevRow = currRow;
				prevCol = currCol;
				currRow--;
			}
			else {
				pathUpLeft(&path);
				prevRow = currRow;
				prevCol = currCol;
				currRow--;
				currCol--;
			}
		}
		if(currRow < qbertRow) {
			if (currCol >= qbertCol) {
				pathDownLeft(&path);
				prevRow = currRow;
				prevCol = currCol;
				currRow++;
			}
			else {
				pathDownRight(&path);
				prevRow = currRow;
				prevCol = currCol;
				currRow++;
				currCol++;
			}
		}
		SnakeAnimation->SetPath(path);
		cout << "Snake Position curr: " << currRow << "  " << currCol << "   prev: " << prevRow << " " << prevCol << endl;
	}


	void pathUpRight(list<PathEntry>* path) {
		PathEntry *p = new PathEntry(0, 0, 2, 150); 
		
		PathEntry *p1 = new PathEntry(0, 0, 3, 200);
		PathEntry *p4 = new PathEntry(0, 0, 3, 200);
		PathEntry *p5 = new PathEntry(0, -20, 3, 200);
		PathEntry *p6 = new PathEntry(0, -50, 3, 200);
		PathEntry *p2 = new PathEntry(50, -5, 3, 200);
		PathEntry *p3 = new PathEntry(0, 0, 3, 200);
		path->push_back(*p1);
		path->push_back(*p4);
		path->push_back(*p5);
		path->push_back(*p6);
		path->push_back(*p2);
		path->push_back(*p3);
		path->push_back(*p);
		p = new PathEntry(0, 0, 3, 200);
		path->push_back(*p);

	}
	void pathUpLeft(list<PathEntry>* path) {
		PathEntry *p = new PathEntry(0, 0, 0, 200);

		PathEntry *p1 = new PathEntry(0, 0, 1, 200);
		PathEntry *p4 = new PathEntry(0, 0, 1, 200);
		PathEntry *p5 = new PathEntry(0, -20, 1, 200);
		PathEntry *p6 = new PathEntry(0, -50, 1, 200);
		PathEntry *p2 = new PathEntry(-50, -5, 1, 200);
		PathEntry *p3 = new PathEntry(0, 0, 1, 200);
		path->push_back(*p1);
		path->push_back(*p4);
		path->push_back(*p5);
		path->push_back(*p6);
		path->push_back(*p2);
		path->push_back(*p3);
		
		 
		path->push_back(*p);
		p = new PathEntry(0, 0, 1, 200);
		path->push_back(*p);
	}
	void pathDownLeft(list<PathEntry>* path) {
		PathEntry *p = new PathEntry(0, 0, 6, 200);

		PathEntry *p1 = new PathEntry(0, 0, 7, 200);
		PathEntry *p4 = new PathEntry(0, 0, 7, 200);
		PathEntry *p5 = new PathEntry(0, -30, 7, 200);
		PathEntry *p6 = new PathEntry(-40, 0, 7, 200);
		PathEntry *p2 = new PathEntry(-10, 105, 7, 200);
		PathEntry *p3 = new PathEntry(0, 0, 7, 200);
		path->push_back(*p1);
		path->push_back(*p4);
		path->push_back(*p5);
		path->push_back(*p6);
		path->push_back(*p2);
		path->push_back(*p3);
		path->push_back(*p);
		p = new PathEntry(0, 0, 7, 200);
		path->push_back(*p);
	}
	void pathDownRight(list<PathEntry>* path) {
		PathEntry *p = new PathEntry(0, 0, 4, 200);

		PathEntry *p1 = new PathEntry(0, 0, 5, 200);
		PathEntry *p4 = new PathEntry(0, 0, 5, 200);
		PathEntry *p5 = new PathEntry(0, -30, 5, 200);
		PathEntry *p6 = new PathEntry(40, 0, 6, 200);
		PathEntry *p2 = new PathEntry(10, 105, 5, 200);
		PathEntry *p3 = new PathEntry(0, 0, 5, 200);
		path->push_back(*p1);
		path->push_back(*p4);
		path->push_back(*p5);
		path->push_back(*p6);
		path->push_back(*p2);
		path->push_back(*p3);
		path->push_back(*p);
		p = new PathEntry(0,0, 5, 200);
		path->push_back(*p);
	}

	void SetIsBall(bool b) {
		isBall = b;
	}
	bool GetIsBall() {
		return isBall;
	}

	void Destroy() {} 

	AnimationFilm* GetFilmSnake() {
		AnimationFilm* film = AnimationFilmHolder::Get().GetFilm("snake");
		if (film == nullptr) {
			SDL_Rect rect;
			rect.x = 0;
			rect.y = 0;
			rect.h = 32;
			rect.w = 14;
			vector<SDL_Rect> boxes;
			boxes.push_back(rect);
			rect.x = 14;
			rect.y = 0;
			rect.h = 32;
			rect.w = 16;
			boxes.push_back(rect);
			rect.x = 30;
			rect.y = 0;
			rect.h = 32;
			rect.w = 14;
			boxes.push_back(rect);
			rect.x = 44;
			rect.y = 0;
			rect.h = 32;
			rect.w = 16;
			boxes.push_back(rect);
			rect.x = 60;
			rect.y = 0;
			rect.h = 32;
			rect.w = 14;
			boxes.push_back(rect);
			rect.x = 74;
			rect.y = 0;
			rect.h = 32;
			rect.w = 16;
			boxes.push_back(rect);
			rect.x = 90;
			rect.y = 0;
			rect.h = 32;
			rect.w = 14;
			boxes.push_back(rect);
			rect.x = 104;
			rect.y = 0;
			rect.h = 32;
			rect.w = 16;
			boxes.push_back(rect);
			string id = "snake";
			AnimationFilmHolder::Get().Load(id, "Sprites/SnakeFilm.bmp", boxes);
			film = AnimationFilmHolder::Get().GetFilm("snake");
		}
		return film;
	}

	AnimationFilm* GetFilmBall() {
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

	void Reset() {
		currRow = 8; // na dw poia prpei na einai h arxikh timh
		currCol = 8; //
	}
	void UpdateRowCol(int row , int col) {
		prevRow = currRow;
		prevCol = currCol;
		currRow = row;
		currCol = col;
	}

	Snake( int x, int y) {
		Create( x, y);
		SetFrame(4);
		Animation = nullptr;
		Animator = nullptr;
		currRow = 8;
		currCol = 8;
		prevRow = 8;
		prevCol = 8;
		isBall = true;
	}
};


class MovingPathAnimatorAI : public MovingPathAnimator {
	list<int> ColList;
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
			if (!(currPathFrame->dx) && !(currPathFrame->dy) && !(currPathFrame->frame) && !(currPathFrame->delay)) {
				assert(!ColList.empty());
				if (!(sprite->GetId().compare("SnakeBall"))) {
					int row = game->GetSnake()->GetCurrRow() + 1; // ayksanw to row
					int col = game->GetSnake()->GetCurrCol() + ColList.front(); // ypologizw col
					game->GetSnake()->UpdateRowCol(row, col);
				//	cout << "SNAKE BALL: row->" << game->GetSnake()->GetCurrRow() << " col->" << game->GetSnake()->GetCurrCol() << endl;
					TheSoundManager::Instance()->playSound("Snake", 0);
				}
				else {
				int row = game->GetBall(sprite)->GetCurrRow() + 1; 
				int col = game->GetBall(sprite)->GetCurrCol() + ColList.front();
				game->GetBall(sprite)->UpdateRowCol(row, col);
			//	cout << "BALL " << sprite->GetId() <<": row->" << game->GetBall(sprite)->GetCurrRow() << " col->" << game->GetBall(sprite)->GetCurrCol() << endl;
				}
				TheSoundManager::Instance()->playSound("Ball", 0);
				ColList.pop_front();
			}
			if (currPathFrame == anim->GetEndPathFrame()) {
				if (cont)
					currPathFrame = anim->GetStartPathFrame();
				else {
					state = ANIMATOR_FINISHED;
					NotifyStopped();
					return true;
				}
			}
		}
		return false;
	}

	void SetColList(list<int>& ColList) {
		assert((this->ColList.empty()));
		this->ColList.assign(ColList.begin(), ColList.end());
	}

	MovingPathAnimatorAI(Sprite* s, MovingPathAnimation* a, list<int>& ColList) : MovingPathAnimator(s, a) {
		this->ColList.assign(ColList.begin(), ColList.end());
	}
};



class BallAnim {
	Ball* ball;
	MovingPathAnimation* BallAnimation;
	MovingPathAnimatorAI* BallAnimator;

public:
	Ball * GetBall() {
		return ball;
	}
	MovingPathAnimation* GetBallAnimation() {
		return BallAnimation;
	}
	MovingPathAnimatorAI* GetBallAnimator() {
		return BallAnimator;
	}
	BallAnim(Ball* ball, MovingPathAnimation* BallAnimation, MovingPathAnimatorAI* BallAnimator) {
		this->ball = ball;
		this->BallAnimation = BallAnimation;
		this->BallAnimator = BallAnimator;
	}
};


class AI {
	list<BallAnim*> Balls;  
	Snake *snake;
	unsigned delay = 3700; 
	unsigned long lastTime;
	static int sum;

public:
	void logic(unsigned long currTime) {
		srand(time(0));
		if (snake && snake->GetAnimator()->GetState() == ANIMATOR_FINISHED && snake->GetSnakeAnimator()->GetState() == ANIMATOR_READY) { // ksekinaei to fidi
			snake->GetSnakeSprite()->GetDestinationRect().x = snake->GetSprite()->GetDestinationRect().x;
			snake->GetSnakeSprite()->GetDestinationRect().y = snake->GetSprite()->GetDestinationRect().y;
			snake->SetIsBall(false);
			spriteList.Insert(snake->GetSnakeSprite());
			spriteList.Remove(snake->GetSprite()); 
			snake->GetSnakeAnimator()->Start(game->GetGameTime());
		}
		else if (snake && snake->GetAnimator()->GetState() == ANIMATOR_FINISHED && snake->GetSnakeAnimator()->GetState() == ANIMATOR_FINISHED) { // AI for snake			
			snake->SnakeAI();
			if(snake->GetAnimator()->GetState() != ANIMATOR_READY) 
				snake->GetSnakeAnimator()->Start(game->GetGameTime());
			// tha to kanw ayto gia na ksexwrizw tis periptwseis
			// tha ANIMATOR_READY to sprite ths ball otan rip to snake
			// alliws tha to exw ANIMATOR_FINISHED opote tote to snake zei kai ananewnei path gia na "piasei" ton qbert
			//snake->GetAnimator()->SetState(ANIMATOR_READY);
		}
		if (snake && snake->GetAnimator()->GetState() == ANIMATOR_READY && snake->GetSnakeAnimator()->GetState() == ANIMATOR_FINISHED) {
			// mporw na bgazw kai snake apo list kai na kanw null kai na ta kanei ola apo thn arxh se syndiasmo  me to apokatw(else if)				
			//spriteList.Remove(snake->GetSnakeSprite());
			snake->GetSnakeAnimator()->SetState(ANIMATOR_READY);
		}

		while (currTime > lastTime && currTime - lastTime >= delay && (BallsWithState(ANIMATOR_RUNNING)+ BallsWithState(ANIMATOR_READY)) < 3 ){
			int col = rand() % 2 + 1;
			BallAnim* ballAnim = nullptr;

			if (!snake) {
				list<int> ColList;
				snake = new Snake(330 + ((col - 1) * 100), 0);
				snake->UpdateRowCol(2,col);
				list<PathEntry> path;
				PathEntry *p;
				p = new PathEntry(0, 0, 5, 0);  // current position
				path.push_back(*p);
				for (int i = 0; i < 4; ++i) {
					p = new PathEntry(0, 28, 5, 70);
					path.push_back(*p);
				}
				p = new PathEntry(0, 28, 4, 70);
				path.push_back(*p);
				for (int i = 0; i < 5; ++i) {
					if (rand() % 2) {				// aristera
						PathEntry *p1 = new PathEntry(0, 0, 5, 150);
						PathEntry *p4 = new PathEntry(0, 0, 5, 150);
						PathEntry *p5 = new PathEntry(0, -30, 5, 150);
						PathEntry *p6 = new PathEntry(-40, 0, 5, 150);
						PathEntry *p2 = new PathEntry(-10, 105,5, 150);
						PathEntry *p3 = new PathEntry(0, 0, 4, 500);
						PathEntry *p = new PathEntry(0, 0, 0, 0);
						path.push_back(*p1);
						path.push_back(*p4);
						path.push_back(*p5);
						path.push_back(*p6);
						path.push_back(*p2);
						path.push_back(*p3);
						path.push_back(*p);
						ColList.push_back(0);
					}
					else {							
						PathEntry *p1 = new PathEntry(0, 0, 5, 150);
						PathEntry *p4 = new PathEntry(0, 0, 5, 150);
						PathEntry *p5 = new PathEntry(0, -30, 5, 150);
						PathEntry *p6 = new PathEntry(40, 0, 5, 150);
						PathEntry *p2 = new PathEntry(10, 105, 5, 150);
						PathEntry *p3 = new PathEntry(0, 0, 4, 500);
						PathEntry *p = new PathEntry(0, 0, 0, 0);
						path.push_back(*p1);
						path.push_back(*p4);
						path.push_back(*p5);
						path.push_back(*p6);
						path.push_back(*p2);
						path.push_back(*p3);
						path.push_back(*p);
						ColList.push_back(1);
					}
				}

				p = new PathEntry(-4, 0, 4, 200);
				for (int i = 0; i < 5; ++i) {
					p = new PathEntry(-8, 0, 4, 200);
					path.push_back(*p);
					p = new PathEntry(8, 0, 4, 200);
					path.push_back(*p);
				}
				p = new PathEntry(-4, 0, 4, 200);
				path.push_back(*p);

				snake->SetColList(ColList);
				MovingPathAnimation* SnakeBallAnimation = new MovingPathAnimation(path, "Snake1");
				MovingPathAnimatorAI* SnakeBallAnimator = new MovingPathAnimatorAI(snake->GetSprite(), SnakeBallAnimation, ColList); /////
				snake->SetAnimation(SnakeBallAnimation);
				snake->SetAnimator(SnakeBallAnimator);
				snake->GetAnimator()->Start(game->GetGameTime());

				list<PathEntry> path2;
				PathEntry *p2;
				p2 = new PathEntry(0, 0, 4, 500);
				path2.push_back(*p2);
				p2 = new PathEntry(0, 0, 5, 500);
				path2.push_back(*p2);

				MovingPathAnimation* SnakeAnimation = new MovingPathAnimation(path2, "Snake2");
				MovingPathAnimator* SnakeAnimator = new MovingPathAnimator(snake->GetSnakeSprite(), SnakeAnimation);
				snake->SetSnakeAnimation(SnakeAnimation);
				snake->SetSnakeAnimator(SnakeAnimator);
			}
			else if (snake->GetAnimator()->GetState() == ANIMATOR_READY && snake->GetSnakeAnimator()->GetState() == ANIMATOR_READY) { // an kathysterei poly ta kanw ena me to apopanw
				/*spriteList.Insert(snake->GetSprite());
				//spriteList.Remove(snake->GetSnakeSprite()); // to exw bgalei hdh
				snake->SetBallX(330 + ((col - 1) * 100));
				snake->SetBallY(0);
				snake->SetCurrRow(8);
				snake->SetCurrCol(8);
				snake->UpdateRowCol(2, col);
				list<int> ColList = snake->GetColList();
				MovingPathAnimatorAI * anim = dynamic_cast<MovingPathAnimatorAI*>(snake->GetAnimator());
				anim->SetColList(ColList);
				snake->GetAnimator()->Start(game->GetGameTime());*/
				list<int> ColList;
				snake = new Snake(330 + ((col - 1) * 100), 0);
				snake->UpdateRowCol(2, col);
				list<PathEntry> path;
				PathEntry *p;
				p = new PathEntry(0, 0, 5, 0);  // current position
				path.push_back(*p);
				for (int i = 0; i < 4; ++i) {
					p = new PathEntry(0, 28, 5, 70);
					path.push_back(*p);
				}
				p = new PathEntry(0, 28, 4, 70);
				path.push_back(*p);

				for (int i = 0; i < 5; ++i) {
					if (rand() % 2) {				// aristera
						PathEntry *p1 = new PathEntry(0, 0, 5, 150);
						PathEntry *p4 = new PathEntry(0, 0, 5, 150);
						PathEntry *p5 = new PathEntry(0, -30, 5, 150);
						PathEntry *p6 = new PathEntry(-40, 0, 5, 150);
						PathEntry *p2 = new PathEntry(-10, 105, 5, 150);
						PathEntry *p3 = new PathEntry(0, 0, 4, 500);
						PathEntry *p = new PathEntry(0, 0, 0, 0);
						path.push_back(*p1);
						path.push_back(*p4);
						path.push_back(*p5);
						path.push_back(*p6);
						path.push_back(*p2);
						path.push_back(*p3);
						path.push_back(*p);
						ColList.push_back(0);
					}
					else {
						PathEntry *p1 = new PathEntry(0, 0, 5, 150);
						PathEntry *p4 = new PathEntry(0, 0, 5, 150);
						PathEntry *p5 = new PathEntry(0, -30, 5, 150);
						PathEntry *p6 = new PathEntry(40, 0, 5, 150);
						PathEntry *p2 = new PathEntry(10, 105, 5, 150);
						PathEntry *p3 = new PathEntry(0, 0, 4, 500);
						PathEntry *p = new PathEntry(0, 0, 0, 0);
						path.push_back(*p1);
						path.push_back(*p4);
						path.push_back(*p5);
						path.push_back(*p6);
						path.push_back(*p2);
						path.push_back(*p3);
						path.push_back(*p);
						ColList.push_back(1);
					}
				}

				p = new PathEntry(-4, 0, 4, 200);
				for (int i = 0; i < 5; ++i) {
					p = new PathEntry(-8, 0, 4, 200);
					path.push_back(*p);
					p = new PathEntry(8, 0, 4, 200);
					path.push_back(*p);
				}
				p = new PathEntry(-4, 0, 4, 200);
				path.push_back(*p);

				snake->SetColList(ColList);
				MovingPathAnimation* SnakeBallAnimation = new MovingPathAnimation(path, "Snake1");
				MovingPathAnimatorAI* SnakeBallAnimator = new MovingPathAnimatorAI(snake->GetSprite(), SnakeBallAnimation, ColList); /////
				snake->SetAnimation(SnakeBallAnimation);
				snake->SetAnimator(SnakeBallAnimator);
				snake->GetAnimator()->Start(game->GetGameTime());


				list<PathEntry> path2;
				PathEntry *p2;
				p2 = new PathEntry(0, 0, 4, 500);
				path2.push_back(*p2);
				p2 = new PathEntry(0, 0, 5, 500);
				path2.push_back(*p2);

				MovingPathAnimation* SnakeAnimation = new MovingPathAnimation(path2, "Snake2");
				MovingPathAnimator* SnakeAnimator = new MovingPathAnimator(snake->GetSnakeSprite(), SnakeAnimation);
				snake->SetSnakeAnimation(SnakeAnimation);
				snake->SetSnakeAnimator(SnakeAnimator);
			}
			else if (BallsWithState(ANIMATOR_FINISHED)) {    // + BallsWithState(ANIMATOR_STOPPED)
				for (auto i = Balls.begin(); i != Balls.end(); ++i) {
					if ((*i)->GetBallAnimator()->GetState() == ANIMATOR_FINISHED) {
						ballAnim = (*i);
						ballAnim->GetBallAnimator()->SetState(ANIMATOR_READY);
						ballAnim->GetBall()->SetX(330 +((col - 1) * 100));
						ballAnim->GetBall()->SetY(0);
						ballAnim->GetBall()->SetCurrRow(8);
						ballAnim->GetBall()->SetCurrCol(8);
						ballAnim->GetBall()->UpdateRowCol(2, col);
						list<int> ColList = ballAnim->GetBall()->GetColList();
						ballAnim->GetBallAnimator()->SetColList(ColList);
						ballAnim->GetBallAnimator()->Start(game->GetGameTime());
						break;
					}
				}
				assert(ballAnim);
			}
			else {
				Ball* ball = new Ball("Ball" + to_string(sum), 330 + ((col - 1) * 100), 0);
				ball->UpdateRowCol(2,col);
				list<int> ColList;
				list<PathEntry> path;
				PathEntry *p;
				p = new PathEntry(0, 0, 1, 0);  // current position
				path.push_back(*p);
				for (int i = 0; i < 4; ++i) {
					p = new PathEntry(0, 28, 1, 70);
					path.push_back(*p);
				}
				p = new PathEntry(0, 28, 0, 70);
				path.push_back(*p);

				for (int i = 0; i < 6; ++i) {
					if (rand() % 2) {				// aristera
						PathEntry *p1 = new PathEntry(0, 0, 1, 150);
						PathEntry *p4 = new PathEntry(0, 0, 1, 150);
						PathEntry *p5 = new PathEntry(0, -30, 1, 150);
						PathEntry *p6 = new PathEntry(-40, 0, 1, 150);
						PathEntry *p2 = new PathEntry(-10, 105, 1, 150);
						PathEntry *p3 = new PathEntry(0, 0, 0, 500);
						PathEntry *p = new PathEntry(0, 0, 0, 0);
						path.push_back(*p1);
						path.push_back(*p4);
						path.push_back(*p5);
						path.push_back(*p6);
						path.push_back(*p2);
						if (i == 5) break;
						path.push_back(*p);
						ColList.push_back(0);
						path.push_back(*p3);
					}
					else {							//deksia
						//p = new PathEntry(50, 74, 1, 1000);
						// thelei kai endiamesa gia na kanei omala to jump
						//path.push_back(*p);
						PathEntry *p1 = new PathEntry(0, 0, 1, 150);
						PathEntry *p4 = new PathEntry(0, 0, 1, 150);
						PathEntry *p5 = new PathEntry(0, -30, 1, 150);
						PathEntry *p6 = new PathEntry(40, 0, 1, 150);
						PathEntry *p2 = new PathEntry(10, 105, 1, 150);
						PathEntry *p = new PathEntry(0, 0, 0, 0);
						PathEntry *p3 = new PathEntry(0, 0, 0, 500);

						path.push_back(*p1);
						path.push_back(*p4);
						path.push_back(*p5);
						path.push_back(*p6);
						path.push_back(*p2);
						if (i == 5) break;
						path.push_back(*p);
						ColList.push_back(1);
						path.push_back(*p3);
					}
				}
				for (int i = 0; i < 10; ++i) {
					p = new PathEntry(0, 25, 1, 70);
					path.push_back(*p);
				}

				ball->SetColList(ColList);
				MovingPathAnimation* BallAnimation = new MovingPathAnimation(path, "Ball" + to_string(sum));
				MovingPathAnimatorAI* BallAnimator = new MovingPathAnimatorAI(ball->GetSprite(), BallAnimation,ColList);
				ballAnim = new BallAnim(ball, BallAnimation, BallAnimator);
				Balls.push_back(ballAnim);
				ballAnim->GetBallAnimator()->Start(game->GetGameTime());
				sum++;
			}
			//TheSoundManager::Instance()->playSound("Ball", 0);
			lastTime += delay;
		}
	}

	int BallsWithState(animatorstate_t state) {
		int count = 0;
		for (auto i = Balls.begin(); i != Balls.end(); ++i) {
			if ((*i)->GetBallAnimator()->GetState() == state) ++count;
		}
		return count;
	}

	Snake * GetSnake() {
		return snake;
	}
	Ball * GetBall(Sprite *s) {
		for (auto i = Balls.begin(); i != Balls.end(); ++i) {
			if (!((*i)->GetBall()->GetSprite()->GetId()).compare(s->GetId()))
				return (*i)->GetBall();
		}
		assert(0);
		return nullptr;
	}

	void SnakeNull() {
		snake = nullptr;
	}

	void ClearBalls() {
		for (auto i = Balls.begin(); i != Balls.end(); ++i) {
			(*i)=nullptr;
		}
		Balls.clear();
	}

	AI(unsigned long t) {
		snake = nullptr;
		lastTime = t;
	}

};




#endif