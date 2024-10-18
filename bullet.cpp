#include "raylib.h"

#include "constants.h"

class Bullet{
    private:
        int speed;  // defined in pixels/second

        bool active;

        Vector2 position;
        Vector2 direction;

    public:
        Bullet(){
            speed = 400;
            active = false;
            direction = Vector2(0, 0);
        }

        void draw(){
            DrawRectangle(position.x, position.y, bulletSize, bulletSize, playerColor);
        }

        void update(){
            float dt = GetFrameTime();

            /*
                delta time calculation to normalise game speed irrespective of frame rate

                Equation,
                    position = position + (speed * deltaTime);
                considering no acceleration currently
            */

           position.x += (speed*direction.x*dt);
           position.y += (speed*direction.y*dt);

           if(position.x <= wallWidth || position.x >= screenWidth - wallWidth - bulletSize){
                direction.x *= -1;
           }
           if(position.y <= wallWidth || position.y >= screenHeight - wallWidth - bulletSize){
                direction.y *= -1;
           }
        }

        void setActive(bool choice){
            active = choice;
        }
        bool isActive(){
            return active;
        }

        void setDirection(Vector2 direction){
            this->direction = direction;
        }

        void setPosition(Vector2 position){
            this->position = position;
        }

        Rectangle getRectElement(){
            return Rectangle(position.x, position.y, bulletSize, bulletSize);
        }
};