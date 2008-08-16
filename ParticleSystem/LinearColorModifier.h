#ifndef _LINEAR_COLOR_MODIFIER_H_
#define _LINEAR_COLOR_MODIFIER_H_

#include <ParticleSystem/ParticleCollection.h>

namespace OpenEngine {
namespace ParticleSystem {

template <class T> class LinearColorModifier {
private:
public:
    LinearColorModifier() { }

    void Process(float deltaTime, T& particle) {
        //T& particle = iterator.Element();
        if (particle.color == particle.endColor)
            return;
        Vector<4,float> dist = (particle.endColor - particle.startColor)*deltaTime/1000;
        if (dist.GetLength() < 0.001) 
            particle.color = particle.endColor;
        else particle.color += dist;
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
