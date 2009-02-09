#ifndef _EULER_MODIFIER_H_
#define _EULER_MODIFIER_H_

#include <ParticleSystem/ParticleCollection.h>

namespace OpenEngine {
namespace ParticleSystem {

template <class T> class EulerModifier {
private:
    Vector<3,float> zero;
public:
    EulerModifier(): zero(Vector<3,float>(0.0,0.0,0.0)) {}
   
    void Process(float dt, T& particle) {
        //float dtsec = dt/1000.0;
        particle.velocity += particle.forces*dt;
        particle.position += particle.velocity*dt;
        particle.forces = zero;
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
