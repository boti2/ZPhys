#include <ZPhys/physics.h>

namespace ZPhys {
    PhysicsWorld::PhysicsWorld(double g, double r) : gravity(g), rate(r) {}

    void PhysicsWorld::step() {
        step(rate);
    }

    void PhysicsWorld::step(double dt) {
        for(auto &b : bodies) {
            // Apply gravity to body
            for(auto &c : b.circles) c.pos.y += gravity * dt;
            for(auto &p : b.loops) for(auto &v : p.verts) v.y += gravity * dt;

            // Move body components
            for(auto &c : b.circles) c.pos += b.vel * dt;
            for(auto &p : b.loops) {
                for(auto &v : p.verts) v += b.vel * dt;
            }
        }

        resolveCollisions();
    }

    void PhysicsWorld::resolveCollisions() {
        for(auto &b : bodies) {
            b.resolveCollisions();
        }
    }
}
