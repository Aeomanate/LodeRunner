// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 08.08.2021.
//

#include <string>
#include <filesystem>
#include "Sprites.hpp"

std::unordered_map<std::string, ALSprite> Sprites::smap;

void Sprites::load() {
    namespace fs = std::filesystem;
    for(auto const& dir: {fs::path(R"(..\res\Characters)"), fs::path(R"(..\res\Tiles)")})
        for(auto const& obj_in_dir: fs::directory_iterator(dir)) {
            if(not obj_in_dir.is_regular_file()) continue;
            auto const& filename = obj_in_dir.path().filename();
            std::string name = filename.stem().string();
            
            bool is_need_flip = name.back() == 'F';
            if(not is_need_flip) {
                smap[name].Load((dir / filename).string().c_str());
            } else {
                name.pop_back();
                smap[name + "_left"].Load(((dir / filename).string()).c_str());
                smap.insert({name + "_right", smap[name + "_left"].FlipHorizontal()});
            }
        }
}