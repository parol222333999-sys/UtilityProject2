#include <jni.h>
#include <android/log.h>
#include <unistd.h>
#include <pthread.h>

#define TAG "UtilityCore"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

// Поток для работы утилиты в фоне
void* utility_thread(void*) {
    LOGI("Utility background thread started successfully!");
    
    // Здесь будет выполняться логика твоего мода/утилиты
    int counter = 0;
    while (counter < 3) {
        sleep(5);
        LOGI("Utility is active, tick: %d", counter);
        counter++;
    }
    
    return nullptr;
}

// Автоматический запуск при загрузке библиотеки в память
jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("JNI_OnLoad called! Library loaded into memory.");

    pthread_t thread;
    pthread_create(&thread, nullptr, utility_thread, nullptr);

    return JNI_VERSION_1_6;
}

extern "C" {
    JNIEXPORT void JNICALL
    Java_com_tweaks_utility_MainActivity_nativeInit(JNIEnv* env, jobject thiz) {
        LOGI("nativeInit executed from Java MainActivity!");
    }
}

