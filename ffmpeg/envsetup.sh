export NDK_HOME=/home/guangliwu/Enviroment/android-ndk-r12b
export PATH=$NDK_HOME:$PATH
export TMPDIR=/home/guangliwu/WorkSpace/MeetingSystem/tmpdir
export NDK=/home/guangliwu/Enviroment/android-ndk-r12b
export SYSROOT=$NDK/platforms/android-15/arch-arm/
export TOOLCHAIN=/home/guangliwu/Enviroment/android-ndk-r12b/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64
export PREFIX=/home/guangliwu/WorkSpace/MeetingSystem/output
export ADDI_CFLAGS="-marm -pie -fPIE"
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
--disable-encoders \
--enable-mediacodec \
--enable-jni \
--enable-small \
--cross-prefix=$TOOLCHAIN/bin/arm-linux-androideabi- \
--target-os=android \
--arch=arm \
--enable-cross-compile \
--sysroot=$SYSROOT \
--extra-cflags="-Os -fpic $ADDI_CFLAGS" \
--extra-ldflags="$ADDI_LDFLAGS" \
$ADDITIONAL_CONFIGURE_FLAG
make clean -j10
make -j10
make install
}
build_one
