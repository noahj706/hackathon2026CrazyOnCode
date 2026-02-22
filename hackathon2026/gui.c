//gui features: definitions file
//Programmer: Noah Julius

#include "gui.h"

int buttonMenu()
{
    InitWindow(WINDOW_W, WINDOW_H, "Lorum-Ipsum-Project-File-Generator");
    SetTargetFPS(60);
    GuiSetStyle(LABEL, TEXT_COLOR_NORMAL, 0x008181FF);

    int output = 0;
    bool selectionMade = false;

    while (!WindowShouldClose())
    {
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        if (selectionMade == false)
        {
            GuiSetStyle(DEFAULT, TEXT_SIZE, 41);
            GuiLabel((Rectangle) { (WINDOW_W / 2) - 440, 100, 1000, 50 }, "How large would you like your \"Projekt\" to look?");
            //small button
            GuiSetStyle(DEFAULT, TEXT_SIZE, 64);
            GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x90EE90FF);
            GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, 0xA6F1A6FF);
            if (GuiButton((Rectangle) { (WINDOW_W / 2) - 275 / 2 - 250 - 30 - ADJUST, 200, 250, 200 }, "#2#SMALL"))
            {
                output = 1;
                selectionMade = true;
            }
            //medium button
            GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0xFDFD96FF);
            GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, 0xFFFFE0FF);
            if (GuiButton((Rectangle) { (WINDOW_W / 2) - 275 / 2 - ADJUST, 200, 275, 225 }, "#2#MEDIUM"))
            {
                output = 2;
                selectionMade = true;
            }
            //large button
            GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0xFF7F7FFF);
            GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, 0xFF7276FF);
            if (GuiButton((Rectangle) { (WINDOW_W / 2) + 275 / 2 + 30 - ADJUST, 200, 300, 250 }, "#2#LARGE"))
            {
                output = 3;
                selectionMade = true;
            }
            EndDrawing();
        }
        else
        {
            EndDrawing();
           
            return output;
        }

       
    }

   
    return output;
}

void finalMenu()
{
    //make window
    InitWindow(WINDOW_W, WINDOW_H, "Lorum-Ipsum-Project-File-Generator-end");
    SetTargetFPS(60);
    GuiSetStyle(LABEL, TEXT_COLOR_NORMAL, 0x008181FF);

   
    for (; !WindowShouldClose();)
    {
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        GuiSetStyle(DEFAULT, TEXT_SIZE, 50);
        GuiLabel((Rectangle) { (WINDOW_W / 2) - 350, (WINDOW_H / 2) - 90, 1000, 50 }, "Your \"Projekt\" has been made :D");
        EndDrawing();
    }
    CloseWindow();
}
