// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 10.08.2021.
//

#include "CharacterLose.hpp"

CharacterLose::CharacterLose(Character* character, std::string character_name)
: EntityState(character, std::move(character_name))
{}

bool CharacterLose::IsLoseState() const {
    return true;
}
