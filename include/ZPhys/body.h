#pragma once
#include <vector>
#include <ZPhys/shapes.h>

namespace ZPhys {
    class Body {
        public:
            Vec2 vel;  // Body's velocity
            std::vector<Circle> circles;  // Circles in the body
            std::vector<Polygon> loops;  // Multiple closed polygon loops

            // Add circle to body
            void addCircle(const Circle &c);

            // Add loop (polygon) to body
            void addLoop(const std::vector<Vec2> &loop);

            // Resolve collisions for all components
            void resolveCollisions();
    };
}
