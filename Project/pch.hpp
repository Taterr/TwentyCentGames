#ifndef PCH_H
#define PCH_H

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <random>
#include "AEEngine.h"
#include "Systems.hpp"
#include "Characters.hpp"
#include "Maze.hpp"
#include "Combat.hpp"
#include "Input.hpp"
#include "GameStateList.hpp"
#include "GameStateManager.hpp"
#include "Menu.hpp"

#define GRID_NUM 5;

#define DT (f32)AEFrameRateControllerGetFrameTime();

extern s8 fontId;

//
//Maze_Struct* Maze;
//int maze_init_flag =0;

#endif	//PCH.H

