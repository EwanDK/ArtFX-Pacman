#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <iostream>

typedef struct Player {
    Vector2 position;
    bool isEnergized;
    float energizedTime=0.f;
    float movX=0.f;
    float movY=0.f;
    int dirCh = 0;
    Color color = YELLOW;
} Player;

typedef struct Ennemy {
    Vector2 position;
    Color color;
    Color oColor;
    float movX=0.f;
    float movY=0.f;
    int dir=0;
} Ennemy;

int grid[31][28]={{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,1,1,1,1,1,1,1,1,1,1,1,1,3,3,1,1,1,1,1,1,1,1,1,1,1,1,3},
    {3,1,3,3,3,3,1,3,3,3,3,3,1,3,3,1,3,3,3,3,3,1,3,3,3,3,1,3},
    {3,2,3,3,3,3,1,3,3,3,3,3,1,3,3,1,3,3,3,3,3,1,3,3,3,3,2,3},
    {3,1,3,3,3,3,1,3,3,3,3,3,1,3,3,1,3,3,3,3,3,1,3,3,3,3,1,3},
    {3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
    {3,1,3,3,3,3,1,3,3,1,3,3,3,3,3,3,3,3,1,3,3,1,3,3,3,3,1,3},
    {3,1,3,3,3,3,1,3,3,1,3,3,3,3,3,3,3,3,1,3,3,1,3,3,3,3,1,3},
    {3,1,1,1,1,1,1,3,3,1,1,1,1,3,3,1,1,1,1,3,3,1,1,1,1,1,1,3},
    {3,3,3,3,3,3,1,3,3,3,3,3,0,3,3,0,3,3,3,3,3,1,3,3,3,3,3,3},
    {0,0,0,0,0,3,1,3,3,3,3,3,0,3,3,0,3,3,3,3,3,1,3,0,0,0,0,0},
    {0,0,0,0,0,3,1,3,3,0,0,0,0,0,0,0,0,0,0,3,3,1,3,0,0,0,0,0},
    {0,0,0,0,0,3,1,3,3,0,3,3,3,4,4,3,3,3,0,3,3,1,3,0,0,0,0,0},
    {3,3,3,3,3,3,1,3,3,0,3,0,0,0,0,0,0,3,0,3,3,1,3,3,3,3,3,3},
    {4,0,0,0,0,0,1,0,0,0,3,0,0,0,0,0,0,3,0,0,0,1,0,0,0,0,0,4},
    {3,3,3,3,3,3,1,3,3,0,3,0,0,0,0,0,0,3,0,3,3,1,3,3,3,3,3,3},
    {0,0,0,0,0,3,1,3,3,0,3,3,3,3,3,3,3,3,0,3,3,1,3,0,0,0,0,0},
    {0,0,0,0,0,3,1,3,3,0,0,0,0,0,0,0,0,0,0,3,3,1,3,0,0,0,0,0},
    {0,0,0,0,0,3,1,3,3,0,3,3,3,3,3,3,3,3,0,3,3,1,3,0,0,0,0,0},
    {3,3,3,3,3,3,1,3,3,0,3,3,3,3,3,3,3,3,0,3,3,1,3,3,3,3,3,3},
    {3,1,1,1,1,1,1,1,1,1,1,1,1,3,3,1,1,1,1,1,1,1,1,1,1,1,1,3},
    {3,1,3,3,3,3,1,3,3,3,3,3,1,3,3,1,3,3,3,3,3,1,3,3,3,3,1,3},
    {3,1,3,3,3,3,1,3,3,3,3,3,1,3,3,1,3,3,3,3,3,1,3,3,3,3,1,3},
    {3,2,1,1,3,3,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,3,3,1,1,2,3},
    {3,3,3,1,3,3,1,3,3,1,3,3,3,3,3,3,3,3,1,3,3,1,3,3,1,3,3,3},
    {3,3,3,1,3,3,1,3,3,1,3,3,3,3,3,3,3,3,1,3,3,1,3,3,1,3,3,3},
    {3,1,1,1,1,1,1,3,3,1,1,1,1,3,3,1,1,1,1,3,3,1,1,1,1,1,1,3},
    {3,1,3,3,3,3,3,3,3,3,3,3,1,3,3,1,3,3,3,3,3,3,3,3,3,3,1,3},
    {3,1,3,3,3,3,3,3,3,3,3,3,1,3,3,1,3,3,3,3,3,3,3,3,3,3,1,3},
    {3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}};
int score=244;    

void UpdatePlayer(Player *player,Ennemy *ennemies,float delta,bool &lost,bool &win);
void UpdateEnnemies(Player *player, Ennemy *ennemies,float delta,bool &lost);

int main(void){

    const int screenwidth = 448;
    const int screenheight = 576;

    InitWindow(screenwidth,screenheight,"Pacman");
    SetTargetFPS(16);

    Player player = {{ 224, 23.1*16 },0,false};
    Ennemy ennemies[4]={{{224,176},RED,RED},
    {{224,224},PINK,PINK},
    {{192,224},GREEN,GREEN},
    {{256,224},ORANGE,ORANGE}};
    Camera2D camera = { 0 };
    camera.target = (Vector2){ screenwidth/2.0f, screenheight/2.0f };
    camera.offset = (Vector2){ screenwidth/2.0f, screenheight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    bool lost = false;
    bool win = false;

    while (!WindowShouldClose())
    {
        while(!lost&&!win){
            
            if(IsKeyPressed(KEY_UP)&&player.dirCh==0){
                player.dirCh=1;
                player.movY=-1.f;
            }
            if(IsKeyPressed(KEY_DOWN)&&player.dirCh==0){
                player.dirCh=3;
                player.movY=1.f;
            }
            if(IsKeyPressed(KEY_LEFT)&&player.dirCh==0){
                player.dirCh=4;
                player.movX=-1.f;
            }
            if(IsKeyPressed(KEY_RIGHT)&&player.dirCh==0){
                player.dirCh=2;
                player.movX=1.f;
            }

            float deltaTime = GetFrameTime();
            UpdatePlayer(&player,ennemies,deltaTime,lost,win);
            UpdateEnnemies(&player,ennemies,deltaTime,lost);

            BeginDrawing();
                ClearBackground(BLACK);
                BeginMode2D(camera);

                        for(int i=0;i<31;i++){
                            for(int j=0;j<28;j++){
                                if(grid[i][j]==1){
                                    DrawCircle(j*16.f+8,i*16.f+8,3,WHITE);
                                }
                                if(grid[i][j]==2){
                                    DrawCircle(j*16.f+8,i*16.f+8,5,WHITE);
                                }
                                if(grid[i][j]==3){
                                    DrawRectangleRec({j*16.f,i*16.f,16,16},BLUE);
                                }
                                if(grid[i][j]==4){
                                    DrawRectangleRec({j*16.f,i*16.f,16,16},WHITE);
                                }
                            }
                        }
                        DrawCircle(player.position.x,player.position.y,8,player.color);
                        for(int i=0;i<4;i++){
                            DrawRectangleRec({ennemies[i].position.x,ennemies[i].position.y,14,14},ennemies[i].color);
                        }
                    EndMode2D();
            EndDrawing();
        }    
        BeginDrawing();
        BeginMode2D(camera);
        if(win){
            DrawText("Victoire",510,20,20,RED);
        }else DrawText("Défaite",510,20,20,RED);
        EndMode2D();
        EndDrawing();

    }

    CloseWindow();
    return 0;
    
}
void UpdatePlayer(Player *player,Ennemy *ennemies,float delta,bool &lost,bool &win){
    if(player->isEnergized){
        player->energizedTime-=delta;
        if(player->energizedTime<=0.f){
            player->isEnergized=false;
            player->energizedTime=0.f;
            for(int i=0;i<4;i++){
                ennemies[i].color=ennemies[i].oColor;
            }
        }
    }
    if(player->dirCh%2==1){
        if(fmod(player->position.x,16.f)<7.f){
            player->movX=1.f;
        }else if(fmod(player->position.x,16.f)>9.f){
            player->movX=-1.f;
        }else{
            player->position.x=floor(player->position.x/16.f)*16.f+8.f;
            player->movX=0.f;
            player->dirCh=0;
        }
    }else if(player->dirCh!=0){
        if(fmod(player->position.y,16.f)<7.f){
            player->movY=1.f;
        }else if(fmod(player->position.y,16.f)>9.f){
            player->movY=-1.f;
        }else {
            player->position.y=floor(player->position.y/16.f)*16.f+8.f;
            player->movY=0.f;
            player->dirCh=0;
        }
    }
    player->position.y+=player->movY*32*delta;//speed here
    player->position.x+=player->movX*32*delta;
    int posY=(int)floor(player->position.y/16);
    int posX=(int)floor(player->position.x/16);
    if(grid[posY][posX]==1){
        grid[posY][posX]=0;
        score--;
    }
    if(grid[posY][posX]==2){
        grid[posY][posX]=0;
        score--;
        player->isEnergized=true;
        player->energizedTime=20.f;
        for(int i=0;i<4;i++){
            ennemies[i].color=SKYBLUE;
        }
    }
    if(score==0){
        win=true;
    }
    if(grid[posY][posX]==3){
        lost=true;
    }
}

void UpdateEnnemies(Player *player, Ennemy *ennemies,float delta,bool &lost){
    int pPosX=(int)floor(player->position.x/16);
    int pPosY=(int)floor(player->position.y/16);

    for(int i=0;i<4;i++){
        int ePosX=(int)floor(ennemies[i].position.x/16);
        int ePosY=(int)floor(ennemies[i].position.y/16);
        if(pPosX==ePosX&&pPosY==ePosY){
            if(player->isEnergized){
                ennemies[i].position=(Vector2){224,224};
            }else lost=true;
        }
        //CAUSES CRASH
        /*while(!(ennemies[i].movX != 0.f)||(ennemies[i].movY!=0.f)){
            if(grid[ePosY-1][ePosX]<3){
                ennemies[i].movY=-1.f;
            }else if(grid[ePosY+1][ePosX]<3){
                ennemies[i].movY=1.f;
            }else if(grid[ePosY][ePosX-1]<3){
                ennemies[i].movX=-1.f;
            }else if(grid[ePosY][ePosX+1]<3){
                ennemies[i].movX=1.f;
            }
        }*/
        ennemies[i].position.y+=ennemies[i].movY*30*delta;
        ennemies[i].position.x+=ennemies[i].movX*30*delta;
    }
}