#ifndef BILLBOARDED_PARTICLE_H_
#define BILLBOARDED_PARTICLE_H_

#include <ParticleSystem/Particle.h>

#include <Scene/GeometryNode.h>
#include <Scene/TransformationNode.h>

#include <Resources/ITextureResource.h>
#include <Renderers/OpenGL/TextureLoader.h>

#include <Math/Matrix.h>

namespace OpenEngine {
namespace ParticleSystem {

using namespace OpenEngine::Scene;
using namespace OpenEngine::Resources;
using namespace OpenEngine::Math;
using OpenEngine::Renderers::OpenGL::TextureLoader;

class BillboardedParticle : public Particle {
public:
    string picture;
    Vector<3,float> direction; //@todo should not be public

    TransformationNode* tnode;
    GeometryNode* gnode;

    BillboardedParticle() {
        this->position = Vector<3,float>(0.0f);
        this->direction = Vector<3,float>(0.0f);
        picture = "";

        gnode = new GeometryNode();
        tnode = new TransformationNode();
        tnode->AddNode(gnode);

    }

    ~BillboardedParticle() {

    }

    TransformationNode* GetBillboard(Vector<3,float> viewingPosition) {
        float scale = position.GetLength()/100.0;
        
        float alphaHeight = 1.0;
        if (position[1]!=0 && position[1] < 40)
            alphaHeight = position[1]/40;
        //Vector<4,float> color(1,1,1, 1 - alphaHeight);
        Vector<4,float> color(1,0.5,0.0, 1 - alphaHeight);

        ITextureResourcePtr texture = ResourceManager<ITextureResource>::Create(picture);
        TextureLoader::LoadTextureResource(texture);


        int textureHosisontalSize = texture->GetHeight();
        int textureVerticalSize = texture->GetWidth();
        float horisontalhalfsize = textureHosisontalSize * 0.5;
        Vector<3,float> center(0.0f);

        FaceSet* faces = new FaceSet();
        Vector<3,float> lowerleft = Vector<3,float>(horisontalhalfsize,-textureVerticalSize*0.5,0) + center;
        Vector<3,float> lowerright = Vector<3,float>(-horisontalhalfsize,-textureVerticalSize*0.5,0) + center;
        Vector<3,float> upperleft = Vector<3,float>(horisontalhalfsize,textureVerticalSize*0.5,0) + center;
        Vector<3,float> upperright = Vector<3,float>(-horisontalhalfsize,textureVerticalSize*0.5,0) + center;
        
        FacePtr leftside = FacePtr(new Face(lowerleft,lowerright,upperleft));
        leftside->norm[0] = leftside->norm[1] = leftside->norm[2] = Vector<3,float>(0,0,-1);
        leftside->CalcHardNorm(); // use new constructor with normals instead

        leftside->colr[0] = leftside->colr[1] = leftside->colr[2] = color;
        leftside->texc[1] = Vector<2,float>(1,0);
        leftside->texc[0] = Vector<2,float>(0,0);
        leftside->texc[2] = Vector<2,float>(0,1);
        faces->Add(leftside);
        
        FacePtr rightside = FacePtr(new Face(lowerright,upperright,upperleft));
        rightside->norm[0] = rightside->norm[1] = rightside->norm[2] = Vector<3,float>(0,0,-1);
        rightside->CalcHardNorm(); // use new constructor with normals instead

        rightside->colr[0] = rightside->colr[1] = rightside->colr[2] = color;
        rightside->texc[2] = Vector<2,float>(0,1);
        rightside->texc[1] = Vector<2,float>(1,1);
        rightside->texc[0] = Vector<2,float>(1,0);
        faces->Add(rightside);
        
        MaterialPtr m = leftside->mat = rightside->mat = MaterialPtr(new Material());
	m->texr = texture;
        
        gnode->SetFaceSet(faces);
        tnode->Rotate(direction[0],direction[1],direction[2]);
        tnode->SetPosition(position);

        Matrix<4,4,float> sc;
        sc(0,0) = sc(1,1) = sc(2,2) = scale;//0.5;
        tnode->SetScale(sc);
        //tnode->Scale(scale,scale,scale);

        return tnode;
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
