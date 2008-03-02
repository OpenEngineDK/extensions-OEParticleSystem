#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <Math/Vector.h>

namespace OpenEngine {
namespace ParticleSystem {

using OpenEngine::Math::Vector;

class Particle {
public:
    Vector<3,float> position; //@todo should not be public

    Particle() {
        this->position = Vector<3,float>(0.0f);
    }

    ~Particle() {

    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
