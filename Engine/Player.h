#ifndef PLAYER_H
#define PLAYER_H

#include "EngineUtils.h"

class Player {

    private:
        // Position of player (centre)
        Vector2 _position;
        // Points that make up the player (Will be connected by lines)
        std::vector<Vector2> _points = {{0,0}, {-10, 10}, {10, 10}};

        bool _alive = true;

    public: 
        Player(Vector2 position);

        Vector2 getPosition();
        void setPosition(Vector2 position);

        void drawPlayer(N5110 &screen);
        void rotatePlayer(float angle);

        bool getAlive();
        void setAlive(bool status);
};

#endif