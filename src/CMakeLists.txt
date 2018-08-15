
IF(BUILD_BULLET3)
	SUBDIRS(  Bullet3OpenCL Bullet3Serialize/Bullet2FileLoader Bullet3Dynamics Bullet3Collision Bullet3Geometry )
ENDIF(BUILD_BULLET3)


SUBDIRS(   BulletInverseDynamics BulletSoftBody BulletCollision BulletDynamics LinearMath Bullet3Common)


IF(INSTALL_LIBS)
	#INSTALL of other files requires CMake 2.6
	IF (${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 2.5)
		IF (APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			# Don't actually need to install any common files, the frameworks include everything
		ELSE (APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			INSTALL(FILES btBulletCollisionCommon.h btBulletDynamicsCommon.h  DESTINATION ${INCLUDE_INSTALL_DIR})
		ENDIF (APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
	ENDIF (${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 2.5)
ENDIF(INSTALL_LIBS)

INCLUDE_DIRECTORIES(
		${BULLET_PHYSICS_SOURCE_DIR}/src
		${BULLET_PHYSICS_SOURCE_DIR}/examples
		${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs
		${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/enet/include
                ${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/clsocket/src
		${PYTHON_INCLUDE_DIRS}
)

SET(c_api_SRCS
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/IKTrajectoryHelper.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/IKTrajectoryHelper.h
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/plugins/tinyRendererPlugin/TinyRendererVisualShapeConverter.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/plugins/tinyRendererPlugin/TinyRendererVisualShapeConverter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/plugins/tinyRendererPlugin/tinyRendererPlugin.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/plugins/tinyRendererPlugin/tinyRendererPlugin.h
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/OpenGLWindow/SimpleCamera.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/OpenGLWindow/SimpleCamera.h
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/TinyRenderer/geometry.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/TinyRenderer/model.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/TinyRenderer/tgaimage.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/TinyRenderer/our_gl.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/TinyRenderer/TinyRenderer.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/InProcessMemory.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsClient.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsClient.h
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsServer.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsServer.h
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsServerSharedMemory.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsServerSharedMemory.h
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsDirect.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsDirect.h
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsDirectC_API.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsDirectC_API.h
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsServerCommandProcessor.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsServerCommandProcessor.h
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsClientSharedMemory.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsClientSharedMemory.h
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsClientSharedMemory_C_API.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsClientSharedMemory_C_API.h
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsClientC_API.cpp

		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsClientC_API.h
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/SharedMemoryPublic.h

		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/Win32SharedMemory.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/Win32SharedMemory.h
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PosixSharedMemory.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PosixSharedMemory.h
       
        	${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/b3PluginManager.h
        	${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/b3PluginManager.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/plugins/pdControlPlugin/pdControlPlugin.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/plugins/pdControlPlugin/pdControlPlugin.h

		${CMAKE_CURRENT_SOURCE_DIR}/../examples/Utils/b3ResourcePath.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/Utils/b3ResourcePath.h
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/Utils/RobotLoggingUtil.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/Utils/RobotLoggingUtil.h
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/Utils/b3Clock.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/Utils/b3ResourcePath.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/Utils/b3ERPCFMHelper.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/Utils/b3ReferenceFrameHelper.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/Utils/ChromeTraceUtil.cpp

		${CMAKE_CURRENT_SOURCE_DIR}/../examples/ThirdPartyLibs/tinyxml2/tinyxml2.cpp

		${CMAKE_CURRENT_SOURCE_DIR}/../examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.h

		${CMAKE_CURRENT_SOURCE_DIR}/../examples/ThirdPartyLibs/stb_image/stb_image.cpp

		${CMAKE_CURRENT_SOURCE_DIR}/../examples/ThirdPartyLibs/BussIK/Jacobian.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/ThirdPartyLibs/BussIK/LinearR2.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/ThirdPartyLibs/BussIK/LinearR3.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/ThirdPartyLibs/BussIK/LinearR4.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/ThirdPartyLibs/BussIK/MatrixRmn.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/ThirdPartyLibs/BussIK/Misc.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/ThirdPartyLibs/BussIK/Node.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/ThirdPartyLibs/BussIK/Tree.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/ThirdPartyLibs/BussIK/VectorRn.cpp

		${CMAKE_CURRENT_SOURCE_DIR}/../examples/Importers/ImportColladaDemo/LoadMeshFromCollada.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/Importers/ImportObjDemo/LoadMeshFromObj.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/Importers/ImportObjDemo/Wavefront2GLInstanceGraphicsShape.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/Importers/ImportMJCFDemo/BulletMJCFImporter.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/Importers/ImportURDFDemo/BulletUrdfImporter.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/Importers/ImportURDFDemo/MyMultiBodyCreator.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/Importers/ImportURDFDemo/URDF2Bullet.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/Importers/ImportURDFDemo/UrdfParser.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/Importers/ImportURDFDemo/urdfStringSplit.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/Importers/ImportMeshUtility/b3ImportMeshUtility.cpp

		${CMAKE_CURRENT_SOURCE_DIR}/../examples/MultiThreading/b3PosixThreadSupport.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/MultiThreading/b3Win32ThreadSupport.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/MultiThreading/b3ThreadSupportInterface.cpp

		${CMAKE_CURRENT_SOURCE_DIR}/../Extras/InverseDynamics/btMultiBodyTreeCreator.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../Extras/InverseDynamics/CloneTreeCreator.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../Extras/InverseDynamics/CoilCreator.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../Extras/InverseDynamics/DillCreator.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../Extras/InverseDynamics/IDRandomUtil.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../Extras/InverseDynamics/invdyn_bullet_comparison.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../Extras/InverseDynamics/MultiBodyNameMap.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../Extras/InverseDynamics/MultiBodyTreeCreator.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../Extras/InverseDynamics/MultiBodyTreeDebugGraph.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../Extras/InverseDynamics/RandomTreeCreator.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../Extras/InverseDynamics/SimpleTreeCreator.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../Extras/InverseDynamics/User2InternalIndex.cpp

		${CMAKE_CURRENT_SOURCE_DIR}/../Extras/Serialize/BulletFileLoader/bFile.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../Extras/Serialize/BulletFileLoader/bDNA.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../Extras/Serialize/BulletFileLoader/bChunk.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../Extras/Serialize/BulletFileLoader/btBulletFile.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../Extras/Serialize/BulletWorldImporter/btBulletWorldImporter.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../Extras/Serialize/BulletWorldImporter/btWorldImporter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Extras/Serialize/BulletWorldImporter/btMultiBodyWorldImporter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../Extras/Serialize/BulletWorldImporter/btMultiBodyWorldImporter.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/b3RobotSimulatorClientAPI_NoDirect.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/b3RobotSimulatorClientAPI_NoDirect.h
)

ADD_DEFINITIONS(-DPHYSICS_SERVER_DIRECT)

ADD_LIBRARY(PhysicsClientC_API ${c_api_SRCS})

SET_TARGET_PROPERTIES(PhysicsClientC_API PROPERTIES VERSION ${BULLET_VERSION})
SET_TARGET_PROPERTIES(PhysicsClientC_API PROPERTIES SOVERSION ${BULLET_VERSION})

TARGET_LINK_LIBRARIES(PhysicsClientC_API BulletSoftBody BulletDynamics BulletCollision BulletInverseDynamics LinearMath Bullet3Common)

IF (INSTALL_LIBS)
	INSTALL(FILES
	  ${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsClientC_API.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsClientSharedMemory_C_API.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsClientSharedMemory2_C_API.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsDirectC_API.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/PhysicsClientUDP_C_API.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/SharedMemoryInProcessPhysicsC_API.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/../examples/SharedMemory/SharedMemoryPublic.h
	  DESTINATION include/bullet
	  )
	INSTALL(TARGETS
	  PhysicsClientC_API
	  LIBRARY DESTINATION lib${LIB_SUFFIX}
	  ARCHIVE DESTINATION lib${LIB_SUFFIX}
	  )
ENDIF (INSTALL_LIBS)
