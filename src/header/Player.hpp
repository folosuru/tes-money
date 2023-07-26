#pragma once

#ifndef  TES_PLAYER_HPP
#define TES_PLAYER_HPP
#include <utility>
#include <memory>
#include <unordered_map>
#include "PlayerMoney.hpp"
namespace tes {
class DLL Player {
public:
    PlayerMoney money;

    explicit Player(Types::player_name name_) : name(std::move(name_)) {}

    Player() = delete;

    [[nodiscard]]
    inline Types::country getCounty() const {return country;}

    /**
     * return player data...
     * 
     */
//    T getJson();

    Player & operator = ( const tes::Player & ) = delete;
    Player( const tes::Player & ) = delete;

private:
    Types::country country{};
    Types::player_name name;
};
}


#endif  // TES_PLAYER_HPP
