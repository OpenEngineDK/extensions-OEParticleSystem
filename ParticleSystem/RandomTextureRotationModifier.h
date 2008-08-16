#ifndef _RANDOM_TEXTURE_ROTATION_MODIFIER_H_
#define _RANDOM_TEXTURE_ROTATION_MODIFIER_H_

#include <ParticleSystem/ParticleCollection.h>

namespace OpenEngine {
namespace ParticleSystem {

template <class T> class RandomTextureRotationModifier {
private:
public:
    RandomTextureRotationModifier() { }

    void Process(float deltaTime, T& particle) {
        particle.rotation += ((rand()/((float)RAND_MAX))-1)*deltaTime*0.5;
        
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
