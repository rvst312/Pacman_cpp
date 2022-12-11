//
//  main.cpp
//  pacmanPart1
//
//  Created by aaron franco fernadez on 30/11/22.
//

#include <iostream>

#define MAP_VERTICAL 22
#define MAP_HORIZONTAL 70
#define PERSONAJE 'O'

enum TILES {EMPTY = ' ', WALL = '#', POINT = '.'};
TILES map[MAP_VERTICAL][MAP_HORIZONTAL];
bool run = true;

enum INPUT {QUIT, UP, DOWN, LEFT, RIGHT, UNKNOWN };
INPUT currentInput = INPUT::UNKNOWN;

int personaje_x;
int personaje_y;
int puntuacion_actual = 0;
int puntuacion_total;

//Rellenar mapa
void Setup() {
    personaje_x = MAP_HORIZONTAL / 2;
    personaje_y = MAP_VERTICAL / 2;
    for (size_t i = 0; i < MAP_VERTICAL; i++)
    {
        for (size_t j = 0; j < MAP_HORIZONTAL; j++)
        {
            if (i == 0 || j == 0 || i == MAP_VERTICAL - 1 || j == MAP_HORIZONTAL - 1) {
                map[i][j] = TILES::WALL;
            }
            else {
                map[i][j] = TILES::EMPTY;
            }
        }
    }
    
    //Points
    map[10][10] = TILES::POINT;
    map[10][11] = TILES::POINT;
    map[10][12] = TILES::POINT;
    
    //Agujeros vertical
    map[8][0] = TILES::EMPTY;
    map[9][0] = TILES::EMPTY;
    map[10][0] = TILES::EMPTY;
    map[11][0] = TILES::EMPTY;
    
    map[8][MAP_HORIZONTAL-1] = TILES::EMPTY;
    map[9][MAP_HORIZONTAL-1] = TILES::EMPTY;
    map[10][MAP_HORIZONTAL-1] = TILES::EMPTY;
    map[11][MAP_HORIZONTAL-1] = TILES::EMPTY;
    
    //Agujeros horizontal
    map[0][31] = TILES::EMPTY;
    map[0][32] = TILES::EMPTY;
    map[0][33] = TILES::EMPTY;
    map[0][34] = TILES::EMPTY;
    map[0][35] = TILES::EMPTY;
    map[0][36] = TILES::EMPTY;
    map[0][37] = TILES::EMPTY;
    map[0][38] = TILES::EMPTY;
    
    map[MAP_VERTICAL-1][31] = TILES::EMPTY;
    map[MAP_VERTICAL-1][32] = TILES::EMPTY;
    map[MAP_VERTICAL-1][33] = TILES::EMPTY;
    map[MAP_VERTICAL-1][34] = TILES::EMPTY;
    map[MAP_VERTICAL-1][35] = TILES::EMPTY;
    map[MAP_VERTICAL-1][36] = TILES::EMPTY;
    map[MAP_VERTICAL-1][37] = TILES::EMPTY;
    map[MAP_VERTICAL-1][38] = TILES::EMPTY;
    
    //Puntuacion total
    for (size_t i = 0; i < MAP_VERTICAL; i++)
    {
        for (size_t j = 0; j < MAP_HORIZONTAL; j++)
        {
            if (map[i][j] == TILES::POINT)
            {
                puntuacion_total++;
            }
        }
    }
}

void Input() {
    char input;
    std::cin >> input;
    switch (input)
    {
    case 'w':
    case 'W':
        currentInput = INPUT::UP;
        break;
    case 's':
    case 'S':
        currentInput = INPUT::DOWN;
        break;
    case 'a':
    case 'A':
        currentInput = INPUT::LEFT;
        break;
    case 'd':
    case 'D':
        currentInput = INPUT::RIGHT;
        break;
    case 'q':
    case 'Q':
        currentInput = INPUT::QUIT;
        break;
    default:
        currentInput = INPUT::UNKNOWN;
        break;
    }
}

void Logic() {
    int personaje_y_new = personaje_y;
    int personaje_x_new = personaje_x;
    //Movimiento
    switch (currentInput)
    {
    case QUIT:
        run = false;
        break;
    case UP:
            personaje_y_new--;
        break;
    case DOWN:
            personaje_y_new++;
        break;
    case LEFT:
            personaje_x_new--;
        break;
    case RIGHT:
            personaje_x_new++;
        break;
    }
    
    //Teletransporte
    if (personaje_x_new < 0){
        personaje_x_new = MAP_HORIZONTAL - 1;
    }
    personaje_x_new = personaje_x_new % MAP_HORIZONTAL;
    
    if (personaje_y_new < 0){
        personaje_y_new = MAP_VERTICAL - 1;
    }
    personaje_y_new = personaje_y_new % MAP_VERTICAL;
    
    //Fisicas
    switch (map[personaje_y_new][personaje_x_new]){
        case TILES::WALL:
            break;
        case TILES::POINT:
            puntuacion_actual++;
            map[personaje_y_new][personaje_x_new] = TILES::EMPTY;
        default:
            personaje_y = personaje_y_new;
            personaje_x = personaje_x_new;
            break;
    }
    
}

//Imprimir mapa
void Draw() {
    system("clear");
    for (size_t i = 0; i < MAP_VERTICAL; i++)
    {
        for (size_t j = 0; j < MAP_HORIZONTAL; j++)
        {
            if(i == personaje_y && j == personaje_x){
                std::cout << PERSONAJE;
                
            }
            else{
                std::cout << (char)map[i][j];
            }
        }
        std::cout << std::endl;
    }
//Contador
    std::cout << puntuacion_actual << '/' << puntuacion_total;
}

//Preview
int main()
{
    Setup();
    Draw();
    while (run) {
        Input();
        Logic();
        Draw();
    }
}
