#ifndef _PARTICLE_SET_H_
#define _PARTICLE_SET_H_

#include <ParticleSystem/IParticleSet.h>

#include <list>
#include <Math/Vector.h>
#include <ParticleSystem/IModifier.h>

namespace OpenEngine {
namespace ParticleSystem {

using OpenEngine::Math::Vector;
using std::list;

template <class T>
class ParticleSet : public IParticleSet {
private:
    unsigned int numberOfParticles, numberActiveOfParticles;
    T* particles; //static allocated array
    list<IModifier<T>*> modifiers;

public:
    ParticleSet(unsigned int numberOfParticles) {
        this->numberOfParticles = numberOfParticles;
        numberActiveOfParticles = 0;
        particles = new T[numberOfParticles];
    }

    ~ParticleSet() {
        delete[] particles;
    }

    void Process(const float deltaTime, const float percent) {
        // error when compiling with gcc
        // http://archives.devshed.com/forums/development-94/parsed-as-non-type-error-2198494.html

        typename list< IModifier<T>* > ::iterator itr;
        for (itr = modifiers.begin(); itr != modifiers.end(); itr++) {
            IModifier<T>* modifier = *itr;
            modifier->Process(deltaTime,percent,this);
        }
    }

    unsigned int GetNumberOfParticles() {
        return numberOfParticles;
    }

    unsigned int GetNumberOfActiveParticles() {
        return numberActiveOfParticles;
    }

    T* GetParticles() {
        return particles;
    }

    void AddModifier(IModifier<T>* modifier) {
        modifiers.push_back(modifier);
    }
/*
    void CreateParticle(float creationTime, Vector<3,float> position) {
        particles[numberActiveOfParticles].position = position;
        numberActiveOfParticles += 1;
    }
*/
    void ActivateParticle(unsigned int index) {
        if (index > numberOfParticles) return; // max number of active particles reached
        if (index < numberActiveOfParticles)
            return; // particle is already active
        else if (index == numberActiveOfParticles)
            numberActiveOfParticles += 1; // this is the first deactive particle so activate it
        else { // particle is not the first deactive, so swap them
            T p = particles[numberActiveOfParticles];
            particles[numberActiveOfParticles] = particles[index];
            particles[index] = p;
            numberActiveOfParticles += 1;
        }
    }

    void DeactivateParticle(unsigned int index) {
        if (index > numberActiveOfParticles)
            return; // pariticle already deactive
        else if (index == numberActiveOfParticles)
            numberActiveOfParticles -= 1;
        else {
            T p = particles[numberActiveOfParticles-1];
            particles[numberActiveOfParticles-1] = particles[index];
            particles[index] = p;
            numberActiveOfParticles -= 1;
        }
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
