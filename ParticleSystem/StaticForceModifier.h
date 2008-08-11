#ifndef _STATIC_FORCE_MODIFIER_H_
#define _STATIC_FORCE_MODIFIER_H_

#include "IModifier.h"
#include "ParticleGroup.h"

namespace OpenEngine {
namespace ParticleSystem {

template <class T> class StaticForceModifier : public IModifier<T> {
private:
    Vector<3,float> force;
public:
    StaticForceModifier(Vector<3,float> force) { this->force = force; }

    void Process(float deltaTime, float percent,
		 ParticleGroup<T>* particleGroup) {
      T* particles = particleGroup->GetParticles();
      for (unsigned int i=0; i<particleGroup->GetNumberOfActiveParticles(); i++)
	particles[i].position += force*deltaTime;
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
