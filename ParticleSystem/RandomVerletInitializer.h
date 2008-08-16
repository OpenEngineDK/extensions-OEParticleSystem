#ifndef _RANDOM_VERLET_INITIALIZER_H_
#define _RANDOM_VERLET_INITIALIZER_H_

//#include <ParticleSystem/IInitializer.h>

#include <Math/Vector.h>
#include <vector>

namespace OpenEngine {
namespace ParticleSystem {

using OpenEngine::Math::Vector;
using std::vector;

template <class T>
class RandomVerletInitializer { //: public IInitializer<T> {
private:
    Vector<3,float> direction;
    float angle, speed;
public:
    RandomVerletInitializer(Vector<3,float> direction, float angle): direction(direction), angle(angle) {}
    inline void Process(T& particle) {
        float r = (rand()/((float)RAND_MAX))*angle;
        float p = (rand()/((float)RAND_MAX))*2*PI;
        
        Quaternion<float> q(r,p, 0);
        //        q.Normalize();
        
        particle.previousPosition = particle.position - q.RotateVector(direction);
    }

};

} //NS ParticleSystem
} //NS OpenEngine

#endif
