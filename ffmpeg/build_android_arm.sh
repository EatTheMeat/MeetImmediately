export NDK_HOME=$HOME/Enviroment/android-ndk-r12b
export PATH=$NDK_HOME:$PATH
export TMPDIR=$PWD/tmpdir
export NDK=$HOME/Enviroment/android-ndk-r12b
export SYSROOT=$NDK/platforms/android-15/arch-arm/
export TOOLCHAIN=$HOME/Enviroment/android-ndk-r12b/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64
export PREFIX=$PWD/output
export ADDI_CFLAGS="-marm"
export ADDI_LDFLAGS=""
export CPU=arm

function build_one
{
./configure \
--prefix=$PREFIX \
--enable-shared \
--disable-static \
--disable-doc \
--disable-ffplay \
--disable-ffprobe \
--disable-ffserver \
--disable-doc \
--disable-symver \
--enable-small \
--enable-pic \
--cross-prefix=$TOOLCHAIN/bin/arm-linux-androideabi- \
--target-os=android \
--arch=arm \
--enable-cross-compile \
--sysroot=$SYSROOT \
--extra-cflags="-Os $ADDI_CFLAGS" \
--extra-ldflags="$ADDI_LDFLAGS" \
--extra-ldexeflags="-pie"
$ADDITIONAL_CONFIGURE_FLAG
make clean -j10
make -j10
make install
}
build_one
