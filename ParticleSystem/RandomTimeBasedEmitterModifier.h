#ifndef _RANDOM_BASED_EMITTER_MODIFIER_H_
#define _RANDOM_BASED_EMITTER_MODIFIER_H_

#include "IModifier.h"
#include "ParticleGroup.h"
#include <Core/Exceptions.h>
#include "IEmitter.h"

namespace OpenEngine {
namespace ParticleSystem {

using OpenEngine::Core::Exception;

template <class T>
class RandomTimeBasedEmitterModifier : public IModifier<T> {
private:
    IEmitter* emitter;
    unsigned int ration;
    float timeElapsed, activationTime, percentChanceOfSpawning;
public:
    RandomTimeBasedEmitterModifier(float activationTime, unsigned percentChanceOfSpawning, IEmitter* emitter) : timeElapsed(0.0f) {
        //if (ration==0) throw Exception("ration initialized to zero");
        this->activationTime = activationTime;
        this->percentChanceOfSpawning = percentChanceOfSpawning/100.0;
        this->emitter = emitter;
    }

    void Process(float deltaTime, float percent, ParticleGroup<T>* particleGroup) {
        timeElapsed += deltaTime;

        while (timeElapsed > activationTime &&
            particleGroup->GetNumberOfActiveParticles() < particleGroup->GetNumberOfParticles()) {
            timeElapsed -= activationTime;

            if (percentChanceOfSpawning < 1) {
                float change = (rand()/(float)RAND_MAX);
                if (percentChanceOfSpawning < change) return;
            }

            particleGroup->GetParticles()[particleGroup->GetNumberOfActiveParticles()].position = 
                emitter->GetParticlePosition();
            particleGroup->GetParticles()[particleGroup->GetNumberOfActiveParticles()].orientation = 
                Vector<3,float>(0,0,(rand()/((float)RAND_MAX)-0.5)*0.025*3.14);

	    /*
            float rd = (rand()/(float)RAND_MAX);
            string pic = "";
            if( rd < 0.3333) pic = "Smoke/smoke01.tga";
            else if (rd > 0.6666) pic = "Smoke/smoke03.tga";
            else pic = "Smoke/smoke02.tga";
            particleGroup->GetParticles()[particleGroup->GetNumberOfActiveParticles()].picture = pic;
*/
            unsigned int particleIndex = particleGroup->ActivateNextParticle();
        }
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
