#ifndef CHARACTER_H
#define CHARACTER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "shotfired.h"
#include "resource-manager.h"
#include <vector>
#include <memory>
#include "SDL2/SDL_ttf.h"

class Character {
  public:
    enum class Direction {kUp, kDown, kLeft, kRight};
    std::vector<ShotFired> vecShotFired;
    int score = 0;
    int health_ = 5;
    double energy = 100;
    int max_health = 5;
    int max_energy = 100;
    int mousex = 0;
    int mousey = 0;
    const float defaultspeed = 2;

    Character();
    std::vector<std::unique_ptr<Renderable>>&& Shoot(std::vector<std::unique_ptr<Renderable>> &&FiredShots);
    void Update(Direction direction);
    void Update();
    void Sprint(int speed);
    void Render(SDL_Renderer* renderer, ResourceManager &resources);
    void TakeDamage(int damage) {health_ -= damage;};
    void LoadResources(SDL_Renderer *renderer, ResourceManager &resources);
    void Reset();
    SDL_Rect hitBox_;

    // Returns character's angle
    float GetAngle() {
      return angle;
    };

    // Returns character's x position
    float GetX() {
      return pos_x;
    };

    // Returns character's y position
    float GetY() {
      return pos_y;
    };

    // Returns character width
    float GetWidth() {
      return width;
    };
    
    // Returns character height
    float GetHeight() {
      return height;
    };

    // Returns isAlive_ bool for character
    bool IsAlive(){
      return isAlive_;
    }

    /**
     * 0 means collision on right
     * -1 means collision on left
     * 1 means no collision
    */
    void SetXCollisionSpeed(float speed) {
      if(speed == 0){
        x_right_collision_speed = 0;
      }
      if(speed == -1){
        x_left_collision_speed = 0;
      }
      if (speed == 1){
        x_right_collision_speed = 1;
        x_left_collision_speed = 1;
      }
    };
    
    /**
     * 0 means collision on top
     * -1 means collision on bottom
     * 1 means no collision
    */
    void SetYCollisionSpeed(float speed) {
      if(speed == 0){
        y_up_collision_speed = 0;
      } 
      if(speed == -1){
        y_down_collision_speed = 0;
      }
      if (speed == 1){
        y_up_collision_speed = 1;
        y_down_collision_speed = 1;
      }
    };

    /**
     * Moves character's x position by offset amount
    */
    void SetXOffset(int offset){
      pos_x = hitBox_.x - offset;
    };

    /**
     * Moves character's y position by offset amount
    */
    void SetYOffset(int offset){
      pos_y = hitBox_.y - offset;
    };

    //Sets character speed
    void SetSpeed(int speed){speed_ = speed;};

  private:
    bool isAlive_ = true;
    Direction direction = Direction::kUp;
    float speed_ = 2;
    float angle = 0, rotationSpeed = 3.5;
    float width = 64, height = 64;
    float pos_x = 512, pos_y = 512;
    float hand_angle_ = (((angle - 2.8)* 3.1415926535) / 180.0);
    float hand_distance_ = (width * .33);
    float x_left_collision_speed = 1;
    float x_right_collision_speed = 1;
    float y_up_collision_speed = 1;
    float y_down_collision_speed = 1;

    uint32_t shoot_timer_ = SDL_GetTicks();
    uint32_t sprint_timer_ = SDL_GetTicks();
    uint32_t energy_timer_ = SDL_GetTicks();



};

#endif