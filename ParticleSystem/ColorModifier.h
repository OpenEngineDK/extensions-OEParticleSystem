#ifndef _COLOR_MODIFIER_H_
#define _COLOR_MODIFIER_H_

#include "IModifier.h"
#include "ParticleGroup.h"

namespace OpenEngine {
namespace ParticleSystem {

template <class T> class ColorModifier : public IModifier<T> {
private:
public:
    ColorModifier() { }

    void Process(float deltaTime, float percent,
		 ParticleGroup<T>* particleGroup) {
      T* particles = particleGroup->GetParticles();
      for (unsigned int i=0; i<particleGroup->GetNumberOfActiveParticles(); i++) {
	float height = particles[i].position[1];
	float c = 1.0-(height/40.0);
	particles[i].color = Vector<4,float>(c,c/4.0,0.0,c*2.0);
      }
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
