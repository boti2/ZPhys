#include <ZPhys/body.h>
#include <ZPhys/collision.h>

namespace ZPhys {
    void Body::addCircle(const Circle &c) {
        circles.push_back(c);
    }

    void Body::addLoop(const std::vector<Vec2> &loop) {
        Polygon poly;
        poly.addLoop(loop);
        loops.push_back(poly);
    }

    void Body::resolveCollisions() {
        // Circle-Circle collisions
        for(size_t i=0; i<circles.size(); i++) {
            for(size_t j=i+1; j<circles.size(); j++) {
                circleCircleCollision(circles[i], circles[j]);
            }
        }

        // Circle-Polygon collisions (triangles inside polygons)
        for(auto &c : circles) {
            for(auto &p : loops) {
                for(auto &t : p.triangles) {
                    circleTriangleCollision(c, t);
                }
            }
        }

        // Polygon-Polygon collisions (triangle-triangle)
        for(size_t i=0; i<loops.size(); i++) {
            for(size_t j=i+1; j<loops.size(); j++) {
                for(auto &t1 : loops[i].triangles) {
                    for(auto &t2 : loops[j].triangles) {
                        if(triangleTriangleCollision(t1, t2)) {
                            std::swap(t1.vel, t2.vel);
                        }
                    }
                }
            }
        }
    }
}
