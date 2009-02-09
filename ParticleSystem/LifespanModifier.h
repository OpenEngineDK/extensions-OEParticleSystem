#ifndef _LIFESPAN_MODIFIER_H_
#define _LIFESPAN_MODIFIER_H_

#include <ParticleSystem/ParticleCollection.h>

namespace OpenEngine {
namespace ParticleSystem {

template <class T> class LifespanModifier {
private:
public:
    LifespanModifier() { }

    inline void Process(float dt, T& particle) {
        particle.life += dt;
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
