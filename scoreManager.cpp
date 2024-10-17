#include "raylib.h"
#include<string>


class ScoreManager{
    private:
        int score;

    public:
        ScoreManager(){
            score = 0;
        }

        void incrementScore(){
            score++;
        }

        void draw(){
            DrawText("score: ", 10, 10, 20, WHITE);
            DrawText(std::to_string(score).c_str(), 100, 10, 20, WHITE);
        }
};