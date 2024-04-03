#include <jni.h>
#include <stdio.h>
#include <android/log.h>
// 完整的包名 + 类名 + 方法名

static const char* kClassName = "com/waylon/myapplication/MyNativeLibrary";
static const char* kMethodName = "myNativeMethod";
static const char* kMethodSignature = "()V";
void myNativeMethod(JNIEnv* env, jclass clazz) {
    // 实现方法内容
    __android_log_print(ANDROID_LOG_INFO, "MyNativeLibrary", "Native method called");
}
jint get_add_result(JNIEnv *env,jclass clazz,int a,int b)//这是add方法的具体实现
{
    return a+b;
}
static const JNINativeMethod jniNativeMethods[] = {
        {
                "myNativeMethod", // Java代码中声明的Native方法名
                "()V", // 方法签名
                (void *) myNativeMethod // testDynamicRegister关联的本地函数指针
        },
        {
                "get_add_result",
                "(II)I",
            (void *)get_add_result
        }
};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env = nullptr;
    if (vm->GetEnv((void**) &env, JNI_VERSION_1_6) != JNI_OK) {
        return -1; // 表示加载失败
    }

    jclass clazz = env->FindClass(kClassName);
    if (clazz == nullptr) {
        return -1; // 类未找到
    }

    jmethodID methodId = env->GetStaticMethodID(clazz, kMethodName, kMethodSignature);
    if (methodId == nullptr) {
        return -1; // 方法未找到
    }

    // 注册native方法
    if (env->RegisterNatives(clazz, jniNativeMethods, 2) < 0) {
        return -1; // 注册失败
    }

    // 成功加载
    return JNI_VERSION_1_6; // 返回支持的JNI版本
}

