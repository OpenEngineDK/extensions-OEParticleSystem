#ifndef _TEXTURE_PARTICLE_
#define _TEXTURE_PARTICLE_

#include <boost/shared_ptr.hpp>

//forward declartion
namespace OpenEngine {
    namespace Resources {
        class ITexture2D;
        typedef boost::shared_ptr<ITexture2D> ITexture2DPtr;
    }
}

using OpenEngine::Resources::ITexture2DPtr;

namespace OpenEngine {
namespace ParticleSystem {
    template <class T> struct Texture : T {
        ITexture2DPtr texture;
        float rotation;
        float spin; // speed of the rotation
    };
}
}

#endif
