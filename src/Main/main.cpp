// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and Cur#: http://www.viva64.com
//
#include <iostream>
#include <cstring>
#include <memory>

#include "AeoGameFramework.hpp"
#include "Field.hpp"
#include "Player.hpp"
#include "Sprites.hpp"

class LodeRunnerImpl: public AeoGameFramework {
  public:
    explicit LodeRunnerImpl(
        ALSize scene_size,
        ALSize window_size,
        const char* title,
        bool is_fullscreen
    )
    : AeoGameFramework(scene_size, window_size, title, is_fullscreen)
    { }
    
    bool Init() override {
        Sprites::load();
        field.Init();
        player = std::make_shared<Player>();
        field.Load(player);
        return true;
    }
    
    void Close() override {
    
    }
    
    bool Tick() override {
        HandleKeyboardInput();
        field.Update();
        // drawTestBackground();
        field.Draw();
        
        if(player->IsLose()) {
            int lives = player->DecLife();
            if(lives == 0) {
                return true;
            }
            field.Load(player);
        }
        return false;
    }
    
    void OnMouseMove(int x, int y, int xrelative, int yrelative) override {
    
    }
    
    void OnMouseButtonPressed(ALMouseButton button) override {
        if(cur_keyboard_key != ALKey::NONE) return;
        cur_mouse_key = button;
    }

    void OnMouseButtonReleased(ALMouseButton button) override {
        if(button != cur_mouse_key) return;
        if(button == ALMouseButton::LEFT) {
            player->TryFireByView();
        }
        cur_mouse_key = ALMouseButton::NONE;
    }
    
    void OnKeyPressed(ALKey k) override {
        if(cur_keyboard_key == ALKey::NONE) {
            cur_keyboard_key = k;
        }
    }
    
    void OnKeyReleased(ALKey k) override {
        if(k == cur_keyboard_key) {
            cur_keyboard_key = ALKey::NONE;
        }
    }
    
  private:
    void HandleKeyboardInput() {
        if(cur_keyboard_key == ALKey::NONE) return;
        Coord next_move = {0, 0};
        switch(cur_keyboard_key) {
            case ALKey::RIGHT: next_move = {1 ,  0}; break;
            case ALKey::LEFT : next_move = {-1,  0}; break;
            case ALKey::DOWN : next_move = {0 ,  1}; break;
            case ALKey::UP   : next_move = {0 , -1}; break;
            default: break;
        }
        bool is_move_by_x = next_move.y == 0 and next_move.x != 0;
        if(cur_mouse_key == ALMouseButton::LEFT and is_move_by_x) {
            player->TryFire(next_move);
            cur_mouse_key = ALMouseButton::NONE;
        } else {
            player->TryAddNextMove(next_move);
        }
    }
    
  private:
    Field field;
    std::shared_ptr<Character> player;
    ALMouseButton cur_mouse_key = ALMouseButton::NONE;
    ALKey cur_keyboard_key = ALKey::NONE;
};

int main(int argc, char* argv[]) {
    int w = COLS*16, h = ROWS*16;
    bool is_fullscreen = 0;
    if(argc > 1 and strcmp(argv[1], "-window") == 0 and argc >= 4) {
        w = std::stoi(argv[2]);
        h = std::stoi(argv[3]);
    }
    
    return run(new LodeRunnerImpl({w, h}, {800, 600}, "Aeomanate Lode Runner", is_fullscreen));
}
