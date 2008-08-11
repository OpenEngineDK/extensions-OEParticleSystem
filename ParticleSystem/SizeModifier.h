#ifndef _SIZE_MODIFIER_H_
#define _SIZE_MODIFIER_H_

#include "IModifier.h"
#include "ParticleGroup.h"

namespace OpenEngine {
namespace ParticleSystem {

template <class T> class SizeModifier : public IModifier<T> {
private:
    float timePassed;
public:
    SizeModifier() { timePassed = 0.0; }

    void Process(float deltaTime, float percent,
		 ParticleGroup<T>* particleGroup) {
      timePassed += deltaTime;

      T* particles = particleGroup->GetParticles();
      for (unsigned int i=0; i<particleGroup->GetNumberOfActiveParticles(); i++) {
	float height = particles[i].position[1];
	particles[i].size = 1.0 + height/20.0;
      }
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
