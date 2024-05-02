#ifndef PLAYER_H
#define PLAYER_H

#include "EngineUtils.h"

class Player {

    private:
        // Position of player (centre)
        Vector2 _position;
        // Points that make up the player (Will be connected by lines)
        std::vector<Vector2> _points;

    public: 
        Player(Vector2 position, std::vector<Vector2> points);

        void setPosition(Vector2 position);
        Vector2 getPosition();

        void drawPlayer();
        void rotatePlayer(int angle);
};

#endif