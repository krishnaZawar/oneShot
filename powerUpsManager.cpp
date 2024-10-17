#include "raylib.h"
#include<vector>
#include<cstdlib>
#include<time.h>

#include "reloadPowerUp.cpp"

class PowerUpsManager{
    private:
        float opacity;
        bool increaseOpacity;

        int minPercentage;

    public:
        std::vector<ReloadPowerUp> powerUps;

        PowerUpsManager(){
            srand(time(0));

            minPercentage = 80;

            opacity = 1;
            increaseOpacity = false;
        }

        void update(){
            if(increaseOpacity){
                opacity += GetFrameTime();
            }else{
                opacity -= GetFrameTime();
            }

            if(opacity <= 0.5){
                increaseOpacity = true;
                opacity = 0.5;
            }else if(opacity >= 1){
                increaseOpacity = false;
                opacity = 1;
            }

            for(ReloadPowerUp &powerUp : powerUps){
                powerUp.setOpacity(opacity);
            }
        }

        void addPowerUp(Vector2 position){
            int percentage = rand() % 101;

            if(percentage < minPercentage){
                return;
            }   
            powerUps.push_back(ReloadPowerUp(position));
        }
};