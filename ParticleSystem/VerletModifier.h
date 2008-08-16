#ifndef _VERLET_MODIFIER_H_
#define _VERLET_MODIFIER_H_

#include <ParticleSystem/ParticleCollection.h>

namespace OpenEngine {
namespace ParticleSystem {

template <class T> class VerletModifier {
private:
public:

    void Process(float deltaTime, T& particle) {
        Vector<3,float> tmp = particle.position;
        particle.position += (particle.position-particle.previousPosition)*0.99;
        particle.previousPosition = tmp;
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
