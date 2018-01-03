export NDK_HOME=$HOME/Enviroment/android-ndk-r12b
export SYSROOT=$NDK_HOME/platforms/android-15/arch-arm/
export TOOLCHAIN=$HOME/Enviroment/android-ndk-r12b/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64

function build_one
{
./configure \
--prefix=$(pwd)/output/android/arm \
--host=arm-linux \
--enable-pic \
--enable-shared \
--enable-static \
--cross-prefix=$TOOLCHAIN/bin/arm-linux-androideabi- \
--sysroot=$SYSROOT \
--disable-asm \
--disable-cli \

make clean -j10
make -j10
make install
}
build_one
