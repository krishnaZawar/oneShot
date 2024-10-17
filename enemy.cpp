#include "raylib.h"
#include<math.h>
#include<string>

#include "constants.h"

class Enemy{
    private:
        int size;

        int speed;  // defined in pixels/second

        Vector2 position;

        void defaultSettings(){
            size = 20;
            speed = 100;
        }

    public:
        Enemy(){
            defaultSettings();
            position = Vector2(100, 100);
        }
        Enemy(Vector2 initialPosition){
            defaultSettings();
            position = initialPosition;
        }

        void moveTowards(Vector2 target){
            float dt = GetFrameTime();

             /*
                calculating direction of movement
                    1. get targetPosition
                    2. store targetPosition - playerPosition
                    3. normalise
            */
            Vector2 direction = Vector2(target.x - position.x, target.y - position.y);
            float length = sqrt(direction.x*direction.x + direction.y*direction.y);

            if(length){
                direction.x /= length;
                direction.y /= length;
            }

            /*
                delta time calculation to normalise game speed irrespective of frame rate

                Equation,
                    position = position + (speed * deltaTime);
                considering no acceleration currently                
            */
            position.x += (speed * direction.x * dt);
            position.y += (speed * direction.y * dt);
        }
    
        void draw(){
            DrawRectangle(position.x, position.y, size, size, enemyColor);
        }

        bool collidedWith(Rectangle rect){
            return CheckCollisionRecs(rect, Rectangle(position.x, position.y, size, size));
        }
};