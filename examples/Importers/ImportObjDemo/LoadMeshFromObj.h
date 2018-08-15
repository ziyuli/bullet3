#ifndef LOAD_MESH_FROM_OBJ_H
#define LOAD_MESH_FROM_OBJ_H


struct GLInstanceGraphicsShape;

#include"../../ThirdPartyLibs/Wavefront/tiny_obj_loader.h"

#include <string>
#include "LinearMath/btAlignedObjectArray.h"
#include "LinearMath/btTransform.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h"
#include "BulletCollision/CollisionShapes/btSdfCollisionShape.h"

enum ConvertOBJFlags {
    COBJ_INITIALIZE_SAT_FEATURES=1,
};

class BulletOBJImporter
{
    struct BulletOBJInternalData* m_data;
    
public:
    
    BulletOBJImporter(int flags = 0);
    
    virtual ~BulletOBJImporter();
    
    virtual bool loadOBJMesh(const char * filename, const btVector3& scale);
    
    virtual std::string getBodyName() const;
    
    virtual btCollisionShape* getCollisionShape() const;
    
    virtual void setBodyUniqueId(int bodyId);
    virtual int getBodyUniqueId() const;
    
    virtual bool getRootTransformInWorld(btTransform& rootTransformInWorld) const;
    virtual void setRootTransformInWorld(const btTransform& rootTransformInWorld);

    virtual void  getMassAndInertia(int linkIndex, btScalar& mass,btVector3& localInertiaDiagonal, btTransform& inertialFrame) const;
    virtual void  getMassAndInertia2(int urdfLinkIndex, btScalar& mass, btVector3& localInertiaDiagonal, btTransform& inertialFrame, int flags) const;

    
};

int b3IsFileCachingEnabled();
void b3EnableFileCaching(int enable);

std::string LoadFromCachedOrFromObj(
    std::vector<tinyobj::shape_t>& shapes,   // [output]
    const char* filename,
    const char* mtl_basepath);

GLInstanceGraphicsShape* LoadMeshFromObj(const char* relativeFileName, const char* materialPrefixPath);

#endif //LOAD_MESH_FROM_OBJ_H

