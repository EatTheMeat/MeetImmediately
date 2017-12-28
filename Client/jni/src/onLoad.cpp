
#include <stdlib.h>
#include <android/log.h>

static JavaVM *sVm;

// Throw an exception with the specified class and an optional message.
int jniThrowException(JNIEnv* env, const char* className, const char* msg) 
{
    jclass exceptionClass = env->FindClass(className);
    if (exceptionClass == NULL) 
        return -1;

    if (env->ThrowNew(exceptionClass, msg) != JNI_OK) {
    }

    return 0;
}

JNIEnv* getJNIEnv() 
{
    JNIEnv* env = NULL;
    if (sVm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) 
        return NULL;

    return env;
}


static JNINativeMethod methods[] = {
	{ "native_avcodec_register_all", "()V",  (void*) ffplayAndroid_avcodec_register_all },
	{ "native_av_register_all",      "()V",  (void*) ffplayAndroid_av_register_all },
	{ "nativeInitAudio", "()V", (void*) ffplayAndroid_initAudio},
	{ "nativeInitVideo", "()V", (void*) ffplayAndroid_initVideo},
	{ "nativeEnableErrorCallback", "()V", (void*) ffplayAndroid_enableErrorCallback},
	{ "nativeSetInputFile", "(Ljava/lang/String;)V", (void*) ffplayAndroid_setInputFile },
	{ "nativePause", "(Z)Z", (void*) ffplayAndroid_pause},
	{ "nativeDecodeAudio", "(Z)V", (void*) ffplayAndroid_decodeAudio},
	{ "isDecodingAudio", "()Z", (void*) ffplayAndroid_isDecodingAudio},
	{ "nativePlay", "()V", (void*) ffplayAndroid_play },
	{ "nativeStop", "()V", (void*) ffplayAndroid_stop },
	{ "nativeSetSurface", "(Landroid/view/Surface;)V", (void*) ffplayAndroid_setSurface },
	{ "nativeRelease", "()V", (void*) ffplayAndroid_release },
};

/*
 * Register native JNI-callable methods.
 * "className" looks like "java/lang/String".
 */
int jniRegisterNativeMethods(JNIEnv* env, const char* className, const JNINativeMethod* gMethods, int numMethods)
{
    jclass clazz;

    clazz = env->FindClass(className);
    if (clazz == NULL)
        return -1;

    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0)
        return -1;

    return 0;
}



jint JNI_OnLoad(JavaVM* vm, void* reserved) 
{
    JNIEnv* env = NULL;
    jint result = JNI_ERR;
	sVm = vm;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) 
        return result;
        
    if(jniRegisterNativeMethods(env, "com/ffplay/ffplayAndroid", methods, sizeof(methods)/sizeof(methods[0])) != JNI_OK)
    	goto end;

    result = JNI_VERSION_1_4;

end:
    return result;
}
