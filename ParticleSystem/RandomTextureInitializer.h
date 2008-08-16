#ifndef _RANDOM_TEXTURE_INITIALIZER_H_
#define _RANDOM_TEXTURE_INITIALIZER_H_

//#include "IInitializer.h"
//#include "ParticleGroup.h"
#include <Core/Exceptions.h>

#include <Math/Vector.h>
#include <vector>

namespace OpenEngine {
namespace ParticleSystem {

using OpenEngine::Math::Vector;
using std::vector;

template <class T>
    class RandomTextureInitializer { //: public IInitializer<T> {
private:
        Vector<3,float> position;
        vector<ITextureResourcePtr> textures;
public:
    RandomTextureInitializer() {
    }
    
    void Process(T& particle) {
        if (!textures.empty())
            particle.texture = textures[int((rand()/(float)RAND_MAX)*textures.size() - 1)]; 
    }
    
    void AddTextureResource(ITextureResourcePtr texture) {
        textures.push_back(texture);
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
