#ifndef _ORIENTATION_MODIFIER_H_
#define _ORIENTATION_MODIFIER_H_

#include "IModifier.h"
#include "ParticleGroup.h"

namespace OpenEngine {
namespace ParticleSystem {

template <class T> class OrientationModifier : public IModifier<T> {
private:
public:
    OrientationModifier() { }

    void Process(float deltaTime, float percent,
		 ParticleGroup<T>* particleGroup) {
      T* particles = particleGroup->GetParticles();
      for (unsigned int i=0; i<particleGroup->GetNumberOfActiveParticles(); i++) {
          particles[i].orientation[2] += (rand()/((float)RAND_MAX))*10;
      }
      
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
