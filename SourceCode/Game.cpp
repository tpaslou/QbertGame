#include "Game.h"
#include "Sprites.h"
#include "Terrain.h"
#include "Qbert.h"
#include "Animation.h"
#include "AI.h"
#include "Disk.h"
#include <windows.h>
#include "SoundManager.h"



Game::Game() {
	m_pWindow = nullptr;
	m_pRenderer = nullptr;
	m_bRunning = true;
}

Game::~Game() {}

void Game::LoseLife() {
	lose = true;
}


bool Game::init(const char * title, int xpos, int ypos, int width, int height, int flags,int flag) {
	TheSoundManager::Instance()->load("Sounds/Hop.wav", "Qberthop", SOUND_SFX);
	TheSoundManager::Instance()->load("Sounds/QbertFall.wav", "QbertFalls", SOUND_SFX);
	TheSoundManager::Instance()->load("Sounds/ByeBye.wav", "bye", SOUND_SFX);
	TheSoundManager::Instance()->load("Sounds/disk.wav", "disk", SOUND_SFX);
	TheSoundManager::Instance()->load("Sounds/BallHop.wav", "Ball", SOUND_SFX);
	TheSoundManager::Instance()->load("Sounds/snakeHop.wav", "Snake", SOUND_SFX);
	TheSoundManager::Instance()->load("Sounds/Sware1.wav", "Sware1", SOUND_SFX);
	TheSoundManager::Instance()->load("Sounds/win.wav", "win", SOUND_SFX);
	TheSoundManager::Instance()->load("Sounds/intro.wav", "intro", SOUND_SFX);
	if (flag == 0) {
		game_state = START;
		if (SDL_Init(SDL_INIT_VIDEO) == 0) {
			m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

			if (m_pWindow == nullptr) {

				std::cout << "SDL Error: Failed to create window: " << SDL_GetError() << std::endl;
				SDL_Quit();
				return false;
			}

			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

			if (m_pRenderer == nullptr) {
				std::cout << "SDL Error: Failed to create renderer: " << SDL_GetError() << std::endl;
				SDL_DestroyWindow(m_pWindow);
				SDL_Quit();
				return false;
			}
		}
		else {
			std::cout << "SDL Error: Failed to initialize: " << SDL_GetError() << std::endl;
			return false;
		}
		SDL_Surface * pTempSurface = SDL_LoadBMP("Sprites/start.bmp");
		m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
		SDL_FreeSurface(pTempSurface);
		SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);
		m_sourceRectangle.x = 0;
		m_sourceRectangle.y = 0;
		m_destinationRectangle.w = m_sourceRectangle.w;
		m_destinationRectangle.h = m_sourceRectangle.h;
		m_destinationRectangle.x = 200;
		m_destinationRectangle.y = 250;
		SDL_Surface * pTempSurface1 = SDL_LoadBMP("Sprites/startNames.bmp");
		m_pTexture1 = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface1);
		SDL_FreeSurface(pTempSurface1);
		SDL_QueryTexture(m_pTexture1, NULL, NULL, &m_sourceRectangle1.w, &m_sourceRectangle1.h);
		m_sourceRectangle1.x = 0;
		m_sourceRectangle1.y = 0;
		m_destinationRectangle1.w = m_sourceRectangle1.w;
		m_destinationRectangle1.h = m_sourceRectangle1.h;
		m_destinationRectangle1.x = 0;
		m_destinationRectangle1.y = 0;
		SDL_Surface * pTempSurface2 = SDL_LoadBMP("Sprites/startProject.bmp");
		m_pTexture2 = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface2);
		SDL_FreeSurface(pTempSurface2);
		SDL_QueryTexture(m_pTexture2, NULL, NULL, &m_sourceRectangle2.w, &m_sourceRectangle2.h);
		m_sourceRectangle2.x = 0;
		m_sourceRectangle2.y = 0;
		m_destinationRectangle2.w = m_sourceRectangle2.w;
		m_destinationRectangle2.h = m_sourceRectangle2.h;
		m_destinationRectangle2.x = 0;
		m_destinationRectangle2.y = 500;
		SDL_Surface * pTempSurface3 = SDL_LoadBMP("Sprites/spinning_qbert.bmp");
		m_pTexture3 = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface3);
		SDL_FreeSurface(pTempSurface3);
		SDL_QueryTexture(m_pTexture3, NULL, NULL, &m_sourceRectangle3.w, &m_sourceRectangle3.h);
		m_sourceRectangle3.x = 0;
		m_sourceRectangle3.y = 0;
		m_sourceRectangle3.w = 35;
		m_sourceRectangle3.h = 35;
		m_destinationRectangle3.w = 35;
		m_destinationRectangle3.h = 35;
		m_destinationRectangle3.x = 250;
		m_destinationRectangle3.y =100;
		TheSoundManager::Instance()->playSound("intro", 0);
	}
	else {
		game_state = PLAY;
		if (SDL_Init(SDL_INIT_VIDEO) == 0) {
			m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

			if (m_pWindow == nullptr) {

				std::cout << "SDL Error: Failed to create window: " << SDL_GetError() << std::endl;
				SDL_Quit();
				return false;
			}

			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

			if (m_pRenderer == nullptr) {
				std::cout << "SDL Error: Failed to create renderer: " << SDL_GetError() << std::endl;
				SDL_DestroyWindow(m_pWindow);
				SDL_Quit();
				return false;
			}
		}
		else {
			std::cout << "SDL Error: Failed to initialize: " << SDL_GetError() << std::endl;
			return false;
		}
	}
	return true;
}


void Game::render() {
	switch (game_state) {
	case START:
		SDL_RenderClear(m_pRenderer);
		SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
		SDL_RenderCopy(m_pRenderer, m_pTexture1, &m_sourceRectangle1, &m_destinationRectangle1);
		SDL_RenderCopy(m_pRenderer, m_pTexture2, &m_sourceRectangle2, &m_destinationRectangle2);
		SDL_RenderCopy(m_pRenderer, m_pTexture3, &m_sourceRectangle3, &m_destinationRectangle3);
		SDL_RenderPresent(m_pRenderer);
		break;
	case PLAY:
		SDL_RenderClear(m_pRenderer);
		spriteList.Display();
		SDL_RenderPresent(m_pRenderer);
		break;
	case PAUSE:
		break;
	case GAMEOVER:
		break;
	default:
		break;
	}
}

bool DoBoxesIntersect(Sprite* a, Sprite* b) {
	return (abs(a->GetDestinationRect().x - b->GetDestinationRect().x) * 2 < (a->GetDestinationRect().w + b->GetDestinationRect().w)) &&
		(abs(a->GetDestinationRect().y - b->GetDestinationRect().y) * 2 < (a->GetDestinationRect().h + b->GetDestinationRect().h));
}

void Game::Collision() {
	for (auto i = spriteList.GetList().begin(); i != spriteList.GetList().end(); ++i) {

		/*colission with ball*/
		if (!((*i)->GetId().compare(0, 4, "Ball"))) {

			if (DoBoxesIntersect(qbert->GetSprite(), (*i))) {
				cout << "Colission with ball" << endl;
				TheSoundManager::Instance()->playSound("Sware1", 0);
				LoseLife();
			}


		}
		/*collision with snake*/
		else if (!((*i)->GetId().compare(0, 5, "Snake"))) {

			if (DoBoxesIntersect(qbert->GetSprite(), (*i)) &&
				ai->GetSnake()->GetCurrCol() == qbert->GetCurrCol() &&
				ai->GetSnake()->GetCurrRow() == qbert->GetCurrRow()) {
				cout << "Colission with Snake" << endl;
				TheSoundManager::Instance()->playSound("Sware1", 0);
				LoseLife();
			}

		}
	}
}

void Game::update() {
	switch (game_state) {
	case START:
		m_sourceRectangle3.x = 32 * int(((SDL_GetTicks() / 150) % 6));
		m_destinationRectangle3.x = 32.5 * int(((SDL_GetTicks() / 150) % 25));
		break;
	case PLAY:
		ai->logic(GetGameTime());
		//spriteList.Collision(qbert->GetSprite());
        AnimatorHolder::Progress(currTime);

		break;
	case PAUSE:
		break;
	case GAMEOVER:
		break;

	}
}

void Game::handleEvents() {
	switch (game_state) {
	case PLAY:
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			if (!((diskLeft &&  diskLeft->GetMoveTop()) || (diskRight &&  diskRight->GetMoveTop()))) {
				switch (event.type) {
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_UP)
					{
						if (qbert->GetCurrRow() == qbert->GetCurrCol()) {
							//check for disk and then new event
							//OR
							//Here we lose
							if (qbert->GetCurrRow() == 5 && diskRight->GetIsActive()) {
								TheSoundManager::Instance()->playSound("bye", 0);
								TheSoundManager::Instance()->playSound("disk", 0);
								diskRight->MoveUpRight();
								qbert->MoveUpDiskRight();
								qbert->Restore();
								return;
							}

							cout << "END OF GAME " << endl;

							list<PathEntry> path;
							PathEntry *p1 = new PathEntry(0, 0, 0, 0);
							PathEntry *p2 = new PathEntry(0, 0, 1, 0);
							PathEntry *p3 = new PathEntry(20, -30, 1, 70);
							PathEntry *p4 = new PathEntry(0, -20, 1, 70);
							PathEntry *p5 = new PathEntry(40, -5, 0, 50);
							PathEntry *p6 = new PathEntry(0, 0, 0, 0);
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
							MovingPathAnimation* qbertAnimation = new MovingPathAnimation(path, "qbert_Animation1");
							MovingPathAnimator* qbertAnimator = new MovingPathAnimator(qbert->GetSprite(), qbertAnimation);
							qbert->SetZOrder(5);
							spriteList.GetList().sort(compare);
							qbertAnimator->Start(game->GetGameTime());
							TheSoundManager::Instance()->playSound("QbertFalls", 0);
							LoseLife();
						}
						else {
							qbert->moveUpRight();
							TheSoundManager::Instance()->playSound("Qberthop", 0);
							terrain->SetActive(qbert->GetCurrCol(), qbert->GetCurrRow());
							cout << "Current active : " << terrain->currActive() << endl;
							cout << "Qbert Position changed to : ";
							qbert->PrintPos();
						}
					}
					else if (event.key.keysym.sym == SDLK_DOWN) {
						if (qbert->GetCurrRow() == terrain->GetTotalRows()) {
							cout << "END OF GAME" << endl;
							list<PathEntry> path;
							PathEntry *p1 = new PathEntry(0, 0, 2, 0);
							PathEntry *p2 = new PathEntry(-6, 0, 3, 0);
							PathEntry *p3 = new PathEntry(-20, -30, 3, 70);
							PathEntry *p4 = new PathEntry(-40, 0, 2, 70);
							PathEntry *p5 = new PathEntry(-10, 105, 2, 50);
							PathEntry *p6 = new PathEntry(0, 0, 2, 0);
							path.push_back(*p1);
							path.push_back(*p2);
							path.push_back(*p3);
							path.push_back(*p4);
							path.push_back(*p5);
							path.push_back(*p6);
							PathEntry *p;
							for (int i = 0; i < 30; ++i) {
								p = new PathEntry(0, 25, 2, 60);
								path.push_back(*p);
							}
							MovingPathAnimation* qbertAnimation = new MovingPathAnimation(path, "qbert_Animation1");
							MovingPathAnimator* qbertAnimator = new MovingPathAnimator(qbert->GetSprite(), qbertAnimation);
							if (qbert->GetCurrCol() == 1) {
								qbert->SetZOrder(5);
								spriteList.GetList().sort(compare);
							}
							qbertAnimator->Start(game->GetGameTime());
							TheSoundManager::Instance()->playSound("QbertFalls", 0);
							LoseLife();
						}
						else {
							qbert->moveDownLeft();
							TheSoundManager::Instance()->playSound("Qberthop", 0);
							terrain->SetActive(qbert->GetCurrCol(), qbert->GetCurrRow());
							cout << "Current active : " << terrain->currActive() << endl;
							cout << "Qbert Position changed to : ";
							qbert->PrintPos();

						}

					}
					else if (event.key.keysym.sym == SDLK_RIGHT) {
						if (qbert->GetCurrRow() == terrain->GetTotalRows()) {
							cout << "END OF GAME" << endl;
							list<PathEntry> path;
							PathEntry *p1 = new PathEntry(0, 0, 0, 0);
							PathEntry *p2 = new PathEntry(0, 0, 1, 0);
							PathEntry *p3 = new PathEntry(20, -30, 1, 70);
							PathEntry *p4 = new PathEntry(0, -20, 1, 70);
							PathEntry *p5 = new PathEntry(40, -5, 0, 50);
							PathEntry *p6 = new PathEntry(0, 0, 0, 0);
							path.push_back(*p1);
							path.push_back(*p2);
							path.push_back(*p3);
							path.push_back(*p4);
							path.push_back(*p5);
							path.push_back(*p6);
							PathEntry *p;
							for (int i = 0; i < 30; ++i) {
								p = new PathEntry(0, 25, 0, 60);
								path.push_back(*p);
							}
							MovingPathAnimation* qbertAnimation = new MovingPathAnimation(path, "qbert_Animation1");
							MovingPathAnimator* qbertAnimator = new MovingPathAnimator(qbert->GetSprite(), qbertAnimation);
							if (qbert->GetCurrCol() == terrain->GetTotalRows()) {
								qbert->SetZOrder(5);
								spriteList.GetList().sort(compare);
							}
							qbertAnimator->Start(game->GetGameTime());
							TheSoundManager::Instance()->playSound("QbertFalls", 0);
							LoseLife();


						}
						else {
							qbert->moveDownRight();
							TheSoundManager::Instance()->playSound("Qberthop", 0);
							terrain->SetActive(qbert->GetCurrCol(), qbert->GetCurrRow());
							cout << "Current active : " << terrain->currActive() << endl;
							cout << "qbert Position changed to : ";
							qbert->PrintPos();
						}

					}
					else if (event.key.keysym.sym == SDLK_LEFT) {
						if (qbert->GetCurrCol() == 1) {
							if (qbert->GetCurrRow() == 5 && diskLeft->GetIsActive()) {
								TheSoundManager::Instance()->playSound("bye", 0);
								TheSoundManager::Instance()->playSound("disk", 0);
								diskLeft->MoveUpLeft();
								qbert->MoveUpDiskLeft();
								qbert->Restore();
								return;
							}

							cout << "END OF GAME" << endl;
							list<PathEntry> path;
							PathEntry *p1 = new PathEntry(0, 0, 2, 0);
							PathEntry *p2 = new PathEntry(-6, 0, 3, 0);
							PathEntry *p3 = new PathEntry(-20, -30, 3, 70);
							PathEntry *p4 = new PathEntry(-40, 0, 2, 70);
							PathEntry *p5 = new PathEntry(-10, 105, 2, 50);
							PathEntry *p6 = new PathEntry(0, 0, 2, 0);
							path.push_back(*p1);
							path.push_back(*p2);
							path.push_back(*p3);
							path.push_back(*p4);
							path.push_back(*p5);
							path.push_back(*p6);
							PathEntry *p;
							for (int i = 0; i < 30; ++i) {
								p = new PathEntry(0, 25, 2, 60);
								path.push_back(*p);
							}
							MovingPathAnimation* qbertAnimation = new MovingPathAnimation(path, "qbert_Animation1");
							MovingPathAnimator* qbertAnimator = new MovingPathAnimator(qbert->GetSprite(), qbertAnimation);
							qbert->SetZOrder(5);
							spriteList.GetList().sort(compare);
							qbertAnimator->Start(game->GetGameTime());
							TheSoundManager::Instance()->playSound("QbertFalls", 0);
							LoseLife();
						}
						else {
							qbert->moveUpLeft();
							TheSoundManager::Instance()->playSound("Qberthop", 0);
							terrain->SetActive(qbert->GetCurrCol(), qbert->GetCurrRow());
							cout << "Current active : " << terrain->currActive() << endl;
							cout << "Position changed to : ";
							qbert->PrintPos();

						}
					}
					break;

				case SDL_QUIT:
					m_bRunning = false;
					break;
				default:
					break;
				}
			}

		}

		if (terrain->currActive() == 28 && win == false) {
			win = true;
			TheSoundManager::Instance()->playSound("win", 0);
			terrain->Epilipsia1();
		}
	}
}


void Game::clean() {
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	TheSoundManager::Instance()->clearSoundMap();
	SDL_Quit();
}

void Game::SetRunning(bool b) {
	m_bRunning = b;
}

SDL_Renderer* Game::GetRenderer() {
	return m_pRenderer;
}


void Game::SetSprite(IsometricPyramid *terrain, Qbert *qbert, Disk *diskLeft, Disk *diskRight, AI *ai) {
	this->terrain = terrain;
	this->qbert = qbert;
	this->diskLeft = diskLeft;
	this->diskRight = diskRight;
	this->ai = ai;
}

void Game::SetGameTime() {
	currTime = SDL_GetTicks(); //ms
}
unsigned long Game::GetGameTime() {
	return currTime;
}

AI* Game::GetAI() {
	return ai;
}

Snake * Game::GetSnake() {
	return ai->GetSnake();
}
Ball * Game::GetBall(Sprite *s) {
	return ai->GetBall(s);
}

void Game::SetDiskRightMoveTop(bool b) {
	diskRight->SetMoveTop(false);
}

void Game::SetDiskLeftMoveTop(bool b) {
	diskLeft->SetMoveTop(false);
}

bool Game::GetSnakeIsBall() {
	return ai->GetSnake()->GetIsBall();
}
void Game::SetSnakeIsBall(bool b) {
	ai->GetSnake()->SetIsBall(b);
}

void Game::Lose() {
	spriteList;
	AnimatorHolder::CleanAnimatorHolder();
	auto i = spriteList.GetList().begin();
	while (!spriteList.GetList().empty() && i != spriteList.GetList().end()) {
		auto prev = i;
		++i;
		if ((*prev)->GetId().compare(0, 4, "cube") && (*prev)->GetId().compare(0, 4, "Disk") && (*prev)->GetId().compare("Qbert")){
			spriteList.Remove(*prev);
		}		
		else if (!((*prev)->GetId().compare("Qbert"))) {
			//(*prev)->SetZOrder(20);
		}
	}
	game->ai->SnakeNull();
	ai->ClearBalls();
	//qbert->moveToStart();
}

void Game::Restart() {
	lose = false;
//	qbert->SetZOrder(20);
}

void Game::SetQbertToStart() {
	qbert->SetZOrder(20);
	qbert->moveToStart();
}

int Game::GetQbertRow() {
	return qbert->GetCurrRow();
}
int Game::GetQbertCol() {
	return qbert->GetCurrCol();
}

//gia thn SpriteList (einai ligo akyrh edw alla den exw allo cpp arxeio na thn balw)
//sort apo to mikrotero zOrder sto megalytero
bool compare(Sprite* s1, Sprite* s2) {
	return s1->GetzOrder() < s2->GetzOrder();
}


// Logo thematos xrhshs twn synarthsewn ston Animator
void AnimatorHolder_Register(Animator* a) {
	AnimatorHolder::Register(a);
}
void AnimatorHolder_Cancel(Animator* a) {
	AnimatorHolder::Cancel(a);
}
void AnimatorHolder_MarkAsRunning(Animator* a) {
	AnimatorHolder::MarkAsRunning(a);
}
void AnimatorHolder_MarkAsSuspended(Animator* a) {
	AnimatorHolder::MarkAsSuspended(a);
}
