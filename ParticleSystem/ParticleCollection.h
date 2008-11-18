#ifndef _OE_PARTICLE_COLLECTION_H_
#define _OE_PARTICLE_COLLECTION_H_

//#include <ParticleSystem/IParticleIterator.h>

#include <Core/Exceptions.h>
#include <Utils/Convert.h>

namespace OpenEngine {
namespace ParticleSystem {

using OpenEngine::Core::Exception;
using OpenEngine::Utils::Convert;

//class ParticleException : public Exception {};

template<class T>
class ParticleIterator {
private:
    T* particles;
    unsigned int* dead;
    unsigned int index;
    
public:
    ParticleIterator(T* particles, unsigned int* dead) : 
        particles(particles),
        dead(dead),
        index(0) {}
    void Reset() {
        index = 0;
        }
    void Next() {
        index++;
    }
    T& Element() {
        return particles[index];
    }
    bool HasNext() {
        return index < *dead;
    }
    void Delete() {
        particles[index--] = particles[--*dead];
    }
};


template <class T>
class ParticleCollection {
private:
    T* particles;
    unsigned int size;
    unsigned int dead;    
public:

    ParticleIterator<T> iterator;

    ParticleCollection(T* particles, unsigned int size): particles(particles),
                                                         size(size), 
                                                         dead(0),
                                                         iterator(particles,&dead)
    {
    }

    virtual ~ParticleCollection() {
        delete[] particles;
        // @todo: make particlesystem deallocate
    }

    unsigned int GetSize() {
        return size;
    }

    unsigned int GetActiveParticles() {
        return dead;
    }

    T& NewParticle() {
        if (dead < size)
            return particles[dead++];
        throw Exception("Reached allocation limit of "+Utils::Convert::ToString<int>(size));
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
