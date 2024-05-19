#include <raylib.h>
#include <iostream>

#include "simulation.hpp"


/* RULES
    Underpopulation : A live cell with fewer than two live neighbors dies
    Stasis : A live cell with two or three live neighbors lives on to the next generation
    Overpopulation : A live cell with more than three live neighbors dies
    Reproduction : A dead cell with exactly three live neighbors becomes a live cell
*/


int main()
{
    Color GREY = {29, 29, 29, 255};
    const int WINDOW_WIDTH = 1920;
    const int WINDOW_HEIGHT = 1080;
    const int CELL_SIZE = 5;
    int FPS = 12;


    InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT, "Game of Life");
    SetTargetFPS(FPS);

    Simulation simulation(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);
    

   // std::cout << simulation.CountLiveNeighbors(5, 29) << std::endl;

    //Simulation Loop
    while(WindowShouldClose() == false)
    {
        //1. Event Handling
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePosition = GetMousePosition();
            int row = mousePosition.y / CELL_SIZE;
            int column = mousePosition.x / CELL_SIZE;
            simulation.ToggleCell(row, column);
        }
        if(IsKeyPressed(KEY_ENTER))
        {
            simulation.Start();
            SetWindowTitle("Game of Life is running . . .");
        }
        else if(IsKeyPressed(KEY_SPACE))
        {
            simulation.Stop();
            SetWindowTitle("Game of life has stopped . . .");
        }
        else if(IsKeyPressed(KEY_F))
        {
            FPS += 2;
            SetTargetFPS(FPS);
        }
        else if(IsKeyPressed(KEY_S))
        {
            if(FPS > 5){
                FPS -= 2;
                SetTargetFPS(FPS);
            }
        }
        else if(IsKeyPressed(KEY_R))
        {
            simulation.CreateRandomState();
        }
        else if(IsKeyPressed(KEY_C))
        {
            simulation.ClearGrid();
        }

        //2. Updating State
        simulation.Update();

        //3. Drawing Objects
        BeginDrawing();
        ClearBackground(GREY);
        simulation.Draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}