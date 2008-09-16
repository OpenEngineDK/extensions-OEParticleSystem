#ifndef _LINEAR_COLOR_MODIFIER_H_
#define _LINEAR_COLOR_MODIFIER_H_

#include <ParticleSystem/ParticleCollection.h>

namespace OpenEngine {
namespace ParticleSystem {

template <class T> class LinearColorModifier {
private:
public:
    LinearColorModifier() { }

    inline void Process(T& particle) {
        particle.color = (particle.startColor*(1-(particle.life / particle.maxlife))) + (particle.endColor *(particle.life / particle.maxlife));
        //logger.info << "pcol: " << particle.color << logger.end;
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
