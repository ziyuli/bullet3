#include "LoadMeshFromObj.h"

#include "../../OpenGLWindow/GLInstanceGraphicsShape.h"
#include <stdio.h> //fopen
#include "Bullet3Common/b3AlignedObjectArray.h"
#include <string>
#include <vector>
#include "Wavefront2GLInstanceGraphicsShape.h"
#include "Bullet3Common/b3HashMap.h"

#include <iostream>
#include <fstream>
#include <list>
#include "btBulletCollisionCommon.h"
#include "Bullet3Common/b3FileUtils.h"
#include <string>
#include "../../Utils/b3ResourcePath.h"
#include "../ImportMeshUtility/b3ImportMeshUtility.h"


ATTRIBUTE_ALIGNED16(struct) BulletOBJInternalData
{
    BT_DECLARE_ALIGNED_ALLOCATOR();
    
    std::string m_sourceFile;
    char m_pathPrefix[1024];
    int m_bodyId;
    
    btCollisionShape* m_allocatedCollisionShape;
    
    btTransform m_rootTransformInWorld;
    
    int m_flags;
    
    void setSourceFile(const std::string& relativeFileName, const std::string& prefix)
    {
        m_sourceFile = relativeFileName;
        strncpy(m_pathPrefix, prefix.c_str(), sizeof(m_pathPrefix));
        m_pathPrefix[sizeof(m_pathPrefix)-1] = 0;
    }
    
    BulletOBJInternalData()
    {
        m_flags = 0;
        m_pathPrefix[0] = 0;
    }
};

BulletOBJImporter::BulletOBJImporter(int flags)
{
    m_data = new BulletOBJInternalData;
    m_data->m_flags = flags;
}

BulletOBJImporter::~BulletOBJImporter()
{
    delete m_data;
}

btCollisionShape* BulletOBJImporter::getCollisionShape() const
{
    return m_data->m_allocatedCollisionShape;
}

std::string BulletOBJImporter::getBodyName() const
{
    return m_data->m_sourceFile;
}

bool BulletOBJImporter::getRootTransformInWorld(btTransform& rootTransformInWorld) const
{
    rootTransformInWorld = m_data->m_rootTransformInWorld;
    return true;
}
void BulletOBJImporter::setRootTransformInWorld(const btTransform& rootTransformInWorld)
{
    m_data->m_rootTransformInWorld = rootTransformInWorld;
}

void BulletOBJImporter::getMassAndInertia(int linkIndex, btScalar& mass,btVector3& localInertiaDiagonal, btTransform& inertialFrame) const
{

}

void BulletOBJImporter::getMassAndInertia2(int urdfLinkIndex, btScalar& mass, btVector3& localInertiaDiagonal, btTransform& inertialFrame, int flags) const
{
    mass = 0.f;
    localInertiaDiagonal.setValue(1, 1, 1);
    inertialFrame.setIdentity();
}

// static btCollisionShape* createConcaveFromShape(tinyobj::shape_t& shape, const btVector3& geomScale, int flags)
// {
//     btTriangleMesh* meshInterface = new btTriangleMesh();

    

// }


static btCollisionShape* createConvexHullFromShape(tinyobj::shape_t& shape, const btVector3& geomScale, int flags)
{
    btCompoundShape* compound = new btCompoundShape();
    compound->setMargin(0.001f);
    
    btTransform identity;
    identity.setIdentity();
    
    btConvexHullShape* convexHull = new btConvexHullShape();
    convexHull->setMargin(0.001f);
    int faceCount = shape.mesh.indices.size();
    
    for (int f = 0; f<faceCount; f += 3)
    {
        
        btVector3 pt;
        pt.setValue(shape.mesh.positions[shape.mesh.indices[f] * 3 + 0],
                    shape.mesh.positions[shape.mesh.indices[f] * 3 + 1],
                    shape.mesh.positions[shape.mesh.indices[f] * 3 + 2]);
        
        convexHull->addPoint(pt*geomScale,false);
        
        pt.setValue(shape.mesh.positions[shape.mesh.indices[f + 1] * 3 + 0],
                    shape.mesh.positions[shape.mesh.indices[f + 1] * 3 + 1],
                    shape.mesh.positions[shape.mesh.indices[f + 1] * 3 + 2]);
        convexHull->addPoint(pt*geomScale, false);
        
        pt.setValue(shape.mesh.positions[shape.mesh.indices[f + 2] * 3 + 0],
                    shape.mesh.positions[shape.mesh.indices[f + 2] * 3 + 1],
                    shape.mesh.positions[shape.mesh.indices[f + 2] * 3 + 2]);
        convexHull->addPoint(pt*geomScale, false);
    }
    
    convexHull->recalcLocalAabb();
    convexHull->optimizeConvexHull();
    if (flags & COBJ_INITIALIZE_SAT_FEATURES)
    {
        convexHull->initializePolyhedralFeatures();
    }
    
    compound->addChildShape(identity,convexHull);
    
    return compound;
    
}

bool BulletOBJImporter::loadOBJMesh(const char *filename, const btVector3& scale)
{
    if(strlen(filename)==0)
        return false;
    
    char relativeFileName[1024];
    
    b3FileUtils fu;
    
    bool fileFound = (b3ResourcePath::findResourcePath(filename,relativeFileName,1024))>0;
    
    if (!fileFound){
        b3Warning("OBJ file '%s' not found\n", filename);
        return false;
    } else
    {
        
        char path[1024];
        fu.extractPath(relativeFileName, path, sizeof(path));
        m_data->setSourceFile(relativeFileName, path);
        
        // Load OBJ
        
        // Convex Mesh
        std::vector<tinyobj::shape_t> shapes;
        std::string err = tinyobj::LoadObj(shapes, m_data->m_sourceFile.c_str());
        
        btCollisionShape* shape = 0;
        shape = createConvexHullFromShape(shapes[0], scale, m_data->m_flags);
        
        m_data->m_allocatedCollisionShape = shape;
        return true;
    }
}



void BulletOBJImporter::setBodyUniqueId(int bodyId)
{
    m_data->m_bodyId = bodyId;
}

int BulletOBJImporter::getBodyUniqueId() const
{
    return m_data->m_bodyId;
}


struct CachedObjResult
{
	std::string m_msg;
	std::vector<tinyobj::shape_t> m_shapes;
};

static b3HashMap<b3HashString, CachedObjResult> gCachedObjResults;
static int gEnableFileCaching = 1;

int b3IsFileCachingEnabled()
{
	return gEnableFileCaching;
}
void b3EnableFileCaching(int enable)
{
	gEnableFileCaching  = enable;
	if (enable==0)
	{
		gCachedObjResults.clear();
	}
}


std::string LoadFromCachedOrFromObj(
    std::vector<tinyobj::shape_t>& shapes,   // [output]
    const char* filename,
    const char* mtl_basepath)
{
	CachedObjResult* resultPtr = gCachedObjResults[filename];
	if (resultPtr)
	{
		const CachedObjResult& result = *resultPtr;
		shapes = result.m_shapes;
		return result.m_msg;
	}

	std::string err = tinyobj::LoadObj(shapes, filename, mtl_basepath);
	CachedObjResult result;
	result.m_msg = err;
	result.m_shapes = shapes;
	if (gEnableFileCaching)
	{
		gCachedObjResults.insert(filename,result);
	}
	return err;
}


GLInstanceGraphicsShape* LoadMeshFromObj(const char* relativeFileName, const char* materialPrefixPath)
{
	B3_PROFILE("LoadMeshFromObj");
	std::vector<tinyobj::shape_t> shapes;
	{
		B3_PROFILE("tinyobj::LoadObj2");
		std::string  err  = LoadFromCachedOrFromObj(shapes, relativeFileName, materialPrefixPath);
	}

	{
		B3_PROFILE("btgCreateGraphicsShapeFromWavefrontObj");
		GLInstanceGraphicsShape* gfxShape = btgCreateGraphicsShapeFromWavefrontObj(shapes);
		return gfxShape;
	}
}
