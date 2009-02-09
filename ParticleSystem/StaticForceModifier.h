#ifndef _STATIC_FORCE_MODIFIER_H_
#define _STATIC_FORCE_MODIFIER_H_

#include <ParticleSystem/ParticleCollection.h>
#include <Math/Vector.h>

using OpenEngine::Math::Vector;

namespace OpenEngine {
namespace ParticleSystem {

template <class T> class StaticForceModifier {
private:
    Vector<3,float> force;
public:
    StaticForceModifier(Vector<3,float> force): force(force) {}

    inline void Process(float dt, T& particle) {
        particle.forces += force;
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
