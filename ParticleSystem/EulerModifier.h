#ifndef _EULER_MODIFIER_H_
#define _EULER_MODIFIER_H_

#include <ParticleSystem/ParticleCollection.h>

namespace OpenEngine {
namespace ParticleSystem {

template <class T> class EulerModifier {
public:
    EulerModifier() {}
   
    void Process(float dt, T& particle) {
        particle.velocity += particle.forces * dt ;
        particle.position += particle.velocity * dt;
        particle.forces = Vector<3,float>();
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
