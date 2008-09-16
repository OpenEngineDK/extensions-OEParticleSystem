#ifndef _TEXTURE_ROTATION_MODIFIER_H_
#define _TEXTURE_ROTATION_MODIFIER_H_

#include <ParticleSystem/ParticleCollection.h>

namespace OpenEngine {
namespace ParticleSystem {

template <class T> class TextureRotationModifier {
private:
public:
    TextureRotationModifier() { }

    void Process(T& particle) {
        particle.rotation = particle.spin * particle.life;
        
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
