#ifndef _PARTICLE_GROUP_H_
#define _PARTICLE_GROUP_H_

#include <ParticleSystem/IParticleGroup.h>

#include <list>
#include <Math/Vector.h>
#include <ParticleSystem/IModifier.h>

namespace OpenEngine {
namespace ParticleSystem {

using OpenEngine::Math::Vector;
using std::list;

template <class T>
class ParticleGroup : public IParticleGroup {
private:
    unsigned int numberOfParticles, numberOfActiveParticles;
    T* particles; //static allocated array
    list<IModifier<T>*> modifiers;

public:
    ParticleGroup(unsigned int numberOfParticles) {
        this->numberOfParticles = numberOfParticles;
        numberOfActiveParticles = 0;
        particles = new T[numberOfParticles];
    }

    ~ParticleGroup() {
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
        return numberOfActiveParticles;
    }

    T* GetParticles() {
        return particles;
    }

    void AddModifier(IModifier<T>* modifier) {
        modifiers.push_back(modifier);
    }

    unsigned int ActivateNextParticle() {
      numberOfActiveParticles++;
      return numberOfActiveParticles-1;
    }

    void DeactivateParticle(unsigned int index) {
        if (index >= numberOfParticles)
	    throw Exception("index out of bound");

        if (index > numberOfActiveParticles)
            return; // pariticle already deactive
        else if (index == numberOfActiveParticles)
            numberOfActiveParticles -= 1;
        else {
            T p = particles[numberOfActiveParticles-1];
            particles[numberOfActiveParticles-1] = particles[index];
            particles[index] = p;
            numberOfActiveParticles -= 1;
        }
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
