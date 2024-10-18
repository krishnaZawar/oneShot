#include "raylib.h"

#include<string>

class Button{   
    std::string place_holder;
    int width;
    int height;
    int border;
    int fontSize;

    Vector2 pos;

    Color fill;

    void defaultSetting(){
        fill = WHITE;
        border = 10;
        width = 210;
        height = 60;
        fontSize = 30;
    }

    public:
        Button() {
            defaultSetting();
        }

        Button(std::string place_holder){
            this->place_holder = place_holder;
            defaultSetting();
        }

        void setSize(int width, int height){
            this->width = width;
            this->height = height;
        }

        void setText(std::string text){
            place_holder = text;
        }

        void setFont(int fontSize){
            this->fontSize = fontSize;
        }

        void Draw(Vector2 pos, Vector2 place_holder_pos){
            this->pos = pos;
            DrawRectangle(pos.x, pos.y, width, height, fill);
            
            // border
            DrawRectangle(pos.x, pos.y, width, border, BLACK);
            DrawRectangle(pos.x, pos.y, border, height, BLACK);
            DrawRectangle(pos.x, pos.y + height - border, width, border, BLACK);
            DrawRectangle(pos.x + width - border, pos.y, border, height, BLACK);
            
            DrawText(place_holder.c_str(), place_holder_pos.x, place_holder_pos.y, fontSize, BLACK);
        }

        bool isClicked(){
            Vector2 mousePos = Vector2(GetMouseX(), GetMouseY());

            return CheckCollisionPointRec(mousePos, Rectangle(pos.x, pos.y, width, height));
        }

        void onHover(){
            Vector2 mousePos = Vector2(GetMouseX(), GetMouseY());

            if(CheckCollisionPointRec(mousePos, Rectangle(pos.x, pos.y, width, height))){
                fill = GRAY;
            }
            else{
                fill = WHITE;
            }
        }
};