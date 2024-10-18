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

        void reset(){
            score = 0;
        }

        void draw(Vector2 pos, int font, Color color){
            int offset;
            if(font <= 20){
                offset = 100;
            }else{
                offset = 120;
            }
            DrawText("score : ", pos.x, pos.y, font, color);
            DrawText(std::to_string(score).c_str(), pos.x + offset, pos.y, font, color);
        }
};