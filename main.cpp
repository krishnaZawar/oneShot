#include "raylib.h"
#include "constants.h"
#include "player.cpp"
#include "enemyManager.cpp"
#include "scoreManager.cpp"
#include "powerUpsManager.cpp"
#include "button.cpp"

#include<string>
#include<vector>


int main(){

    InitWindow(screenWidth, screenHeight, "one shot");

    // game state
    std::string state = "homePage";

    // page managers
    bool showGamePage = false;
    bool showHomePage = false;
    bool showScorePage = false;

    // transition manager
    bool isInitialFrameOfPage = true;

    // game managers
    Player player;
    ScoreManager scoreManager;
    EnemyManager enemyManager;
    PowerUpsManager powerUpsManager;

    // buttons
    Button playButton;
    Button homeButton = Button("Home");
    Button exitButton = Button("Exit");


    // build walls
    std::vector<Rectangle>  walls;
    Color wallColor = BLACK;
    walls.push_back(Rectangle(0, 0, screenWidth, wallWidth));
    walls.push_back(Rectangle(0, 0, wallWidth, screenHeight));
    walls.push_back(Rectangle(screenWidth - wallWidth, 0, wallWidth, screenHeight));
    walls.push_back(Rectangle(0, screenHeight - wallWidth, screenWidth, wallWidth));

    // -------------------------------------------------------home page------------------------------------------------------------------------

    homePage:

    state = "homePage";
    isInitialFrameOfPage = true;
    showHomePage = true;

    // init page
    playButton.setText("Play");
    playButton.setSize(buttonWidth, buttonHeight);
    exitButton.setSize(buttonWidth, buttonHeight);

    while(!WindowShouldClose() && showHomePage){
        playButton.onHover();
        exitButton.onHover();

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !isInitialFrameOfPage){
            if(playButton.isClicked()){
                WaitTime(0.5);
                showHomePage = false;
                state = "gamePage";
            }
            if(exitButton.isClicked()){
                showHomePage = false;
                state = "exit";
            }
        }

        BeginDrawing();
            ClearBackground(WHITE);
            DrawRectangle(275, 90, 250, 110, playerColor);
            DrawText("one SHOT", 300, 90, 110, BLACK);
            DrawText("can you survive with one bullet?", 300, 200, 30, BLACK);
            playButton.Draw(Vector2(400, 300), Vector2(475, 325));
            exitButton.Draw(Vector2(400, 400), Vector2(475, 425));
        EndDrawing();

        isInitialFrameOfPage = false;
    }

    if(state == "gamePage"){
        WaitTime(0.2);
        goto gamePage;
    }
    else if(state == "exit"){
        goto exitGame;
    }

    // ---------------------------------------------------------game page------------------------------------------------------------------------

    gamePage:
    
    state = "gamePage";
    isInitialFrameOfPage = true;
    showGamePage = true;

    // init page
    player.load();
    player.setPosition(Vector2(screenWidth/2, screenHeight/2));
    enemyManager.enemies.clear();
    powerUpsManager.powerUps.clear();
    scoreManager.reset();

    while(!WindowShouldClose() && showGamePage){

        // ----------------------------------------------------game logic----------------------------------------------------------------------
        // player shooting
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !isInitialFrameOfPage){
            if(player.isLoaded()){
                player.shoot();
            }
        }
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
                showGamePage = false;
                state = "scorePage";
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
            if(player.isLoaded()){
                break;
            }
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
            
            scoreManager.draw(Vector2(10, 10), 20, WHITE);
        EndDrawing();
        
        isInitialFrameOfPage = false;
    }

    if(state == "scorePage"){
        WaitTime(0.2);
        goto scorePage;
    }

    // ---------------------------------------------------------score page---------------------------------------------------------------------

    scorePage:

    state = "scorePage";
    isInitialFrameOfPage = true;
    showScorePage = true;

    // init page
    playButton.setText("Replay");
    playButton.setSize(buttonWidth, buttonHeight);
    homeButton.setSize(buttonWidth, buttonHeight);
    exitButton.setSize(buttonWidth, buttonHeight);

    while(!WindowShouldClose() && showScorePage){
        playButton.onHover();
        homeButton.onHover();
        exitButton.onHover();

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !isInitialFrameOfPage){
            if(playButton.isClicked()){
                showScorePage = false;
                state = "gamePage";
            }
            if(homeButton.isClicked()){
                showScorePage = false;
                state = "homePage";
            }
            if(exitButton.isClicked()){
                showScorePage = false;
                state = "exit";
            }
        }

        BeginDrawing();
            ClearBackground(WHITE);

            // game state of loss
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

            DrawText("You Died.", 375, 75, 70, BLACK);
            scoreManager.draw(Vector2(425, 175), 30, BLACK);
            playButton.Draw(Vector2(400, 250), Vector2(460, 275));
            homeButton.Draw(Vector2(400, 350), Vector2(475, 375));
            exitButton.Draw(Vector2(400, 450), Vector2(475, 475));
        EndDrawing();

        isInitialFrameOfPage = false;
    }

    if(state == "gamePage"){
        WaitTime(0.2);
        goto gamePage;
    }
    else if(state == "homePage"){
        WaitTime(0.2);
        goto homePage;
    }
    else if(state == "exit"){
        goto exitGame;
    }

    // ---------------------------------------------------------exit game-------------------------------------------------------------------

    exitGame:
        CloseWindow();

    return 0;
}