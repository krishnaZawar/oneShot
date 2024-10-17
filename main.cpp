#include "raylib.h"
#include "constants.h"
#include "player.cpp"
#include "enemyManager.cpp"
#include "scoreManager.cpp"
#include "powerUpsManager.cpp"

#include<string>
#include<vector>


int main(){

    InitWindow(screenWidth, screenHeight, "one shot");

    bool gameIsRunning = true;

    Player player;
    ScoreManager scoreManager;
    EnemyManager enemyManager;
    PowerUpsManager powerUpsManager;

    // build walls
    std::vector<Rectangle>  walls;
    Color wallColor = BLACK;
    walls.push_back(Rectangle(0, 0, screenWidth, wallWidth));
    walls.push_back(Rectangle(0, 0, wallWidth, screenHeight));
    walls.push_back(Rectangle(screenWidth - wallWidth, 0, wallWidth, screenHeight));
    walls.push_back(Rectangle(0, screenHeight - wallWidth, screenWidth, wallWidth));


    while(!WindowShouldClose() && gameIsRunning){

        // ----------------------------------------------------game logic----------------------------------------------------------------------
        
        // update functions
        player.update();
        enemyManager.update();
        powerUpsManager.update();

        // enemy follow
        Vector2 curPlayerPosition = player.getPosition();
        for(Enemy& enemy : enemyManager.enemies){
            enemy.moveTowards(curPlayerPosition);
        }

        // check enemy kills
        for(int i = 0; i < (int)enemyManager.enemies.size(); i++){
            // detect player collision to handle death
            if(enemyManager.enemies[i].collidedWith(player.getRectElement())){
                gameIsRunning = false;
            }
            // handle enemy death on being shot
            if(!player.isLoaded()){
                if(enemyManager.enemies[i].collidedWith(player.getBullet().getRectElement())){
                    powerUpsManager.addPowerUp(enemyManager.enemies[i].getPosition());
                    enemyManager.enemies.erase(enemyManager.enemies.begin() + i);
                    i--;
                    scoreManager.incrementScore();
                }
            }
        }

        // handle powerUps
        for(int i = 0; i < (int)powerUpsManager.powerUps.size(); i++){
            if(CheckCollisionRecs(player.getRectElement(), powerUpsManager.powerUps[i].getRectElement())){
                powerUpsManager.powerUps.erase(powerUpsManager.powerUps.begin() + i);
                i--;
                player.load();
            }
        }

        //-----------------------------------------------------game rendering-------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(WHITE);

            player.draw();
            
            for(Enemy &enemy : enemyManager.enemies){
                enemy.draw();
            }

            for(ReloadPowerUp    &powerUp : powerUpsManager.powerUps){
                powerUp.draw();
            }

            for(Rectangle& wall : walls){
                DrawRectangleRec(wall, wallColor);
            }
            
            scoreManager.draw();
        EndDrawing();

    }

    // close window and other contents
    CloseWindow();

    return 0;
}