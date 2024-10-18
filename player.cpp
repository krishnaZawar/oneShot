#include "raylib.h"
#include<math.h>

#include "constants.h"
#include "bullet.cpp"

class Player{
    private:
        Vector2 position;
        
        int size;
        int skinWidth;

        int speed;  // defined in pixels/second

        bool loaded;
        float reloadTimeLeft;
        float reloadTime;

        Bullet bullet;
    
        void setDefaultSettings(){
            size = 30;
            skinWidth = (size - bulletSize) / 2;

            speed = 200;

            loaded = true;
            reloadTime = reloadTimeLeft = 0.5;

            bullet = Bullet();
        }

    public:
        Player(){
            setDefaultSettings();
            position = Vector2(screenWidth/2, screenHeight/2);
        }
        Player(Vector2 initialPosition){
            setDefaultSettings();
            position = initialPosition;
        }

        void draw(){
            if(bullet.isActive()){
                bullet.draw();
            }

            if(isLoaded()){
                DrawRectangle(position.x, position.y, size, size, playerColor);
            }
            else{
                DrawRectangle(position.x, position.y, size, skinWidth, playerColor);
                DrawRectangle(position.x, position.y, skinWidth, size, playerColor);
                DrawRectangle(position.x + size - skinWidth, position.y, skinWidth, size, playerColor);
                DrawRectangle(position.x, position.y + size - skinWidth, size, skinWidth, playerColor);
            }
        }

        // ------------------------------------------------------------handle movements--------------------------------------------------------

        void updatePosition(){            
            // calculating delta time
            float dt = GetFrameTime();

            /*
                delta time calculation to normalise game speed irrespective of frame rate

                Equation,
                    position = position + (speed * deltaTime);
                considering no acceleration currently                
            */

            if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)){
                position.y -= (speed * dt);
            }
            if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
                position.y += (speed*dt);    
            }
            if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)){
                position.x -= (speed*dt);
            }
            if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)){
                position.x += (speed*dt);
            }

            // confining the player
            if(position.x + size > screenWidth - wallWidth){
                position.x = screenWidth - wallWidth - size;
            }
            if(position.x < wallWidth){
                position.x = wallWidth;
            }
            if(position.y < wallWidth){
                position.y = wallWidth;
            }
            if(position.y + size > screenHeight - wallWidth){
                position.y = screenHeight - wallWidth - size;
            }
        }

        void setPosition(Vector2 position){
            this->position = position;
        }

        Vector2 getDirection(){
             /*
                calculating direction of firing
                    1. get mousePosition
                    2. store mousePosition - playerPosition
                    3. normalise
            */
            
            Vector2 mousePosition = GetMousePosition();

            Vector2 direction = Vector2(mousePosition.x - position.x, mousePosition.y - position.y);

            float length = sqrt(direction.x*direction.x + direction.y*direction.y);
            
            if(length){
                direction.x /= length;
                direction.y /= length;
            }

            return direction;
        }

        // -----------------------------------------------------shooting mechanism----------------------------------------------------------

        void shoot(){
            bullet.setDirection(getDirection());
            bullet.setPosition(position);
            bullet.setActive(true);

            loaded = false;
        }
        void load(){
            bullet.setActive(false);

            loaded = true;
            reloadTimeLeft = reloadTime;
        }

        bool isLoaded(){
            return loaded;
        }

        // ---------------------------------------------------update functions----------------------------------------------------------------

        void update(){
            updatePosition();

            if(!isLoaded()){
                bullet.update();
                reloadTimeLeft -= (1.0 / GetFPS());
                if(reloadTimeLeft < 0){
                    if(CheckCollisionRecs(Rectangle(position.x, position.y, size, size), bullet.getRectElement())){
                        load();
                    }
                }
            }
        }

        // --------------------------------------------------------get functions-------------------------------------------------------------

        Vector2 getPosition(){
            return position;
        }

        Bullet getBullet(){
            return bullet;
        }

        Rectangle getRectElement(){
            return Rectangle(position.x, position.y, size, size);
        }
};