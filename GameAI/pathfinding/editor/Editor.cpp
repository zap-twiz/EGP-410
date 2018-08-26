#include <fstream>
#include <SDL.h>

#include "Game.h"
#include "Editor.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "Grid.h"
#include "GridVisualizer.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Vector2D.h"

using namespace std;

const int GRID_SQUARE_SIZE = 32;

Editor::Editor()
:Game()
,mpGrid(NULL)
,mpGridVisualizer(NULL)
{
}

Editor::~Editor()
{
	cleanup();
}

bool Editor::init()
{
	bool retVal = Game::init();
	if( retVal == false )
	{

		return false;
	}

	mpGrid = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);

	mpGridVisualizer = new GridVisualizer( mpGrid );

	//load buffers
	mpGraphicsBufferManager->loadBuffer( mBackgroundBufferID, "wallpaper.bmp");

	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer(mBackgroundBufferID);
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, (float)pBackGroundBuffer->getWidth(), (float)pBackGroundBuffer->getHeight() );
	}
	
	mpMasterTimer->start();
	return true;
}

void Editor::cleanup()
{
	delete mpGridVisualizer;
	mpGridVisualizer = NULL;

	delete mpGrid;
	mpGrid = NULL;
}

void Editor::beginLoop()
{
	//should be the first thing done
	Game::beginLoop();
}

const std::string FILE_NAME = "pathgrid.txt";

void Editor::processLoop()
{
	//get input - should be moved someplace better
	SDL_PumpEvents();
	int x, y;

	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		mpGrid->setValueAtPixelXY(x, y, BLOCKING_VALUE);
		mpGridVisualizer->setModified();
	}
	else if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		mpGrid->setValueAtPixelXY(x, y, CLEAR_VALUE);
		mpGridVisualizer->setModified();
	}

	//get input - should be moved someplace better
	//all this should be moved to InputManager!!!
	{
		//get keyboard state
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		//if escape key was down then exit the loop
		if (state[SDL_SCANCODE_ESCAPE])
		{
			markForExit();
		}
		else if (state[SDL_SCANCODE_S])
		{
			Editor* pEditor = dynamic_cast<Editor*>(gpGame);
			if (pEditor != NULL)
			{
				ofstream theStream(FILE_NAME);
				pEditor->saveGrid(theStream);
				theStream.close();
				cout << "Grid saved!\n";
				Sleep(1000);//very bogus
			}
		}
		else if (state[SDL_SCANCODE_L])
		{
			Editor* pEditor = dynamic_cast<Editor*>(gpGame);
			if (pEditor != NULL)
			{
				ifstream theStream(FILE_NAME);
				pEditor->loadGrid(theStream);
				theStream.close();
				pEditor->getGridVisualizer()->setModified();
				cout << "Grid loaded!\n";
				Sleep(1000);//very bogus
			}

		}

	}

	//copy to back buffer
	mpGridVisualizer->draw(*(mpGraphicsSystem->getBackBuffer()));

	//should be last thing in processLoop
	Game::processLoop();
}

bool Editor::endLoop()
{
	return Game::endLoop();
}

void Editor::saveGrid( ofstream& theStream )
{
	mpGrid->save( theStream );
}

void Editor::loadGrid( std::ifstream& theStream )
{
	mpGrid->load(theStream);
}
