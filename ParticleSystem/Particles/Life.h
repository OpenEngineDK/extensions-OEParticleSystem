#ifndef _LIFE_PARTICLE_
#define _LIFE_PARTICLE_

namespace OpenEngine {
namespace ParticleSystem {
    template <class T> struct Life : T {
        float life;
        float maxlife;
    };
}
}

#endif
