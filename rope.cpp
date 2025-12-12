#include <vector>
#include <cmath>
#include <SDL2/SDL.h>
#include <memory>

#include "vector2.h"
#include "shape.h"
#include "ball.h"
#include "line.h"
#include "rope.h"

Rope::Rope(Vector2 startPos, int numSegments, float segmentLength, bool lockLast) {
    for (int i = 0; i < numSegments; i++) {
        Vector2 p = {startPos.x + i * segmentLength, startPos.y};
        bool locked = (i == 0) || (lockLast && i == numSegments - 1);
        points.push_back({p, p, locked});
    }

    // 2. Create Sticks
    for (int i = 0; i < numSegments - 1; i++) {
        sticks.push_back({&points[i], &points[i + 1], segmentLength});
    }
}

void Rope::update(float dt) {
    //Verlet Integration 
    for (auto& p : points) {
        if (p.locked) continue;
        
        Vector2 velocity = {p.pos.x - p.oldPos.x, p.pos.y - p.oldPos.y};
        p.oldPos = p.pos;
        
        velocity.x *= 0.99f;
        velocity.y *= 0.99f;
        
        p.pos.x += velocity.x;
        p.pos.y += velocity.y + 1070 * dt * dt; 
    }

    for (int i = 0; i < 3; i++) {
        for (auto& s : sticks) {
            float dx = s.pB->pos.x - s.pA->pos.x;
            float dy = s.pB->pos.y - s.pA->pos.y;
            float dist = std::sqrt(dx * dx + dy * dy);
            
            if (dist == 0) continue; // Avoid divide by zero

            float diff = (dist - s.length) / dist; // Error factor
            float offsetX = dx * diff * 0.5f;
            float offsetY = dy * diff * 0.5f;

            if (!s.pA->locked) {
                s.pA->pos.x += offsetX;
                s.pA->pos.y += offsetY;
            }
            if (!s.pB->locked) {
                s.pB->pos.x -= offsetX;
                s.pB->pos.y -= offsetY;
            }
        }
    }
}


void Rope::draw(SDL_Renderer* renderer) const{
    for (const auto& s : sticks) {
        SDL_RenderDrawLine(renderer, s.pA->pos.x, s.pA->pos.y, s.pB->pos.x, s.pB->pos.y);
    }
}

void Rope::checkCollisionWithBall(Ball& ball) {
    for (auto& s : sticks) {
        Line tempLine(Vector2{s.pA->pos.x, s.pA->pos.y}, 
                     Vector2{s.pB->pos.x, s.pB->pos.y});
        ball.checkForCollisionLine(tempLine);
    }
}