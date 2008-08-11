#ifndef _LIFESPAN_PARTICLE_
#define _LIFESPAN_PARTICLE_

namespace OpenEngine {
namespace ParticleSystem {
    template <class T> struct Lifespan : T {
        float lifespan;
    };
}
}

#endif
