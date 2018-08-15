build_dir=build_cmake/src
install_dir=$HOME/work/xrobot_suncg/lib
# install_dir = $HOME/ziyuli/Desktop/xrobot_suncg/lib
cp $build_dir/Bullet3Collision/*.so* $install_dir/
cp $build_dir/Bullet3OpenCL/*.so* $install_dir/
cp $build_dir/BulletInverseDynamics/*.so* $install_dir/
cp $build_dir/LinearMath/*.so* $install_dir/
cp $build_dir/Bullet3Common/*.so* $install_dir/    
cp $build_dir/Bullet3Serialize/Bullet2FileLoader/*.so* $install_dir/
cp $build_dir/BulletSoftBody/*.so* $install_dir/
cp $build_dir/Bullet3Dynamics/*.so* $install_dir/
cp $build_dir/BulletCollision/*.so* $install_dir/
cp $build_dir/Bullet3Geometry/*.so* $install_dir/
cp $build_dir/BulletDynamics/*.so* $install_dir/
cp $build_dir/libPhysicsClientC_API.so* $install_dir/
cp -r $build_dir/../../src/* $install_dir/../bullet/
cp -r $build_dir/../../examples/SharedMemory/Physics*_API.h $install_dir/../bullet/
cp -r $build_dir/../../examples/SharedMemory/SharedMemory*.h $install_dir/../bullet/
