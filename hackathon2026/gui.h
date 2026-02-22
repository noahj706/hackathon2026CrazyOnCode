//gui features: header file
//Programmer: Noah Julius

//IMPLAMENT LIKE THIS 
//-----------------------------------
//#define RAYGUI_IMPLEMENTATION
//#include "gui.h"
// 
//buttonMenu();//outputs 1-3 size
//....
//finalMenu();//pair with return 0;

#ifndef GUI_H
#define GUI_H


#define _CRT_SECURE_NO_WARNINGS

#define ADJUST 25
#define WINDOW_W 1000
#define WINDOW_H 625

#include "raylib.h"
#include "raygui.h"

int buttonMenu();
void finalMenu();

#endif