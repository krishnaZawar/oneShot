#include "raylib.h"
#include<vector>
#include<cstdlib>
#include<time.h>

#include "enemy.cpp"
#include "constants.h"

class EnemyManager{
    private:
        float loadTime;
        float loadTimeLeft;

        Vector2 getInstantiationCoordinates(){
            bool instatiateFromSides = (rand() % 2);

            int x, y;

            if(instatiateFromSides){
                x = (rand() % 2)? 0 : screenWidth;
                y = rand() % screenHeight;
            }
            else{
                y = (rand() % 2)? 0 : screenHeight;
                x = rand() % screenWidth;
            }

            return Vector2(x, y);
        }
    public:
        std::vector<Enemy> enemies;

        EnemyManager(){
            srand(time(0));
            loadTime = loadTimeLeft = 3;
        }

        void update(){
            if(loadTimeLeft < 0){
                loadTimeLeft = loadTime;
                addEnemy();
            }
            else{
                loadTimeLeft -= GetFrameTime();
            }
        }


        void addEnemy(){
            Vector2 instantiationPosition = getInstantiationCoordinates();
            enemies.push_back(Enemy(instantiationPosition));
        }   
};