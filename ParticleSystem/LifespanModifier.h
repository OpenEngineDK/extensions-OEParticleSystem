#ifndef _LIFESPAN_MODIFIER_H_
#define _LIFESPAN_MODIFIER_H_

#include "IModifier.h"
#include "ParticleGroup.h"

namespace OpenEngine {
namespace ParticleSystem {

template <class T> class LifespanModifier : public IModifier<T> {
private:
public:
    LifespanModifier() { }

    void Process(float deltaTime, float percent,
		 ParticleGroup<T>* particleGroup) {
      T* particles = particleGroup->GetParticles();
      for (unsigned int i=0; i<particleGroup->GetNumberOfActiveParticles(); i++) {
          particles[i].lifespan -= deltaTime;
          if (particles[i].lifespan <= 0) 
              particleGroup->DeactivateParticle(i);
      }
      
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
