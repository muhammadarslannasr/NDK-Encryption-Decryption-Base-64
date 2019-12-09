#include <jni.h>
#include <string>
#include "base64.h"
#include <iostream>

std::string jstring_string1(JNIEnv *env, jstring pJstring1);

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_nativetestcpp_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jstring JNICALL


Java_com_example_nativetestcpp_MainActivity_sendYourName(JNIEnv *env, jobject thiz,
                                                         jstring firstName, jstring lastName) {
    char returnString[20];
    const char *fN = env->GetStringUTFChars(firstName, NULL);
    const char *lN = env->GetStringUTFChars(lastName, NULL);

    strcpy(returnString, fN); // copy string one into the result.
    strcat(returnString, lN); // append string two to the result.

    env->ReleaseStringUTFChars(firstName, fN);
    env->ReleaseStringUTFChars(lastName, lN);

    //__android_log_write(ANDROID_LOG_DEBUG, "API123", returnString);

    return env->NewStringUTF(returnString);
}


std::string jstring_strin(JNIEnv *env, jstring jStr) {
    if (!jStr)
        return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes,
                                                                       env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte *pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char *) pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_nativetestcpp_MainActivity_base64Encode(JNIEnv *env, jobject thiz, jstring data) {

    const std::string bvc = jstring_string1(env, data);
    std::string encoded =


            base64_encode(reinterpret_cast<const unsigned char *>(bvc.c_str()), bvc.length());
    return env->NewStringUTF(encoded.c_str());
}

std::string jstring_string1(JNIEnv *env, jstring pJstring1) {
    if (!pJstring1)
        return "";

    const jclass stringClass = env->GetObjectClass(pJstring1);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(pJstring1, getBytes,
                                                                       env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte *pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char *) pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_nativetestcpp_MainActivity_base64Decode(JNIEnv *env, jobject thiz, jstring data) {
    const std::string bvc = jstring_string1(env, data);

    std::string decoded =
            base64_decode(bvc.c_str());
    return env->NewStringUTF(decoded.c_str());
}

