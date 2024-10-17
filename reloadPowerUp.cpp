#include "raylib.h"

#include "constants.h"

class ReloadPowerUp{
    private:
        float opacity;
        Vector2 position;
        int size;
        Color color;
        
    public:
        ReloadPowerUp(Vector2 position){
            opacity = 1;

            this->position = position;

            size = bulletSize;

            color = Color(playerColor.r, playerColor.b, playerColor.g, playerColor.a);
        }

        void setOpacity(float opacity){
            this->opacity = opacity;
        }
        
        void draw(){
            color.a = opacity * 255;
            DrawRectangle(position.x, position.y, size, size, color);
        }

        Rectangle getRectElement(){
            return Rectangle(position.x, position.y, size, size);
        }
};