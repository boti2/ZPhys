#pragma once
#include <vector>
#include <ZPhys/body.h>

namespace ZPhys {
    class PhysicsWorld {
        public:
            double gravity;
            double rate;
            std::vector<Body> bodies;

            PhysicsWorld(double g = 9.8, double r = 0.016);
            void step();
            void step(double dt);

        private:
            void resolveCollisions();
    };
}
