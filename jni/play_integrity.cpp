#include <jni.h>
#include <string>

#include "IntegrityManagerFactory.hpp"
#include "IntegrityTokenResponse.hpp"
#include "android/content/Context.hpp"
#include "gni/task.hpp"
#include "gni/gni.hpp"
#include "gni/gni.h"
#include "gni/common/logger.h"

using namespace com::google::android::play::core::integrity;

namespace {
    const constexpr char *kLogTag = "integrity_demo";
}

void RequestIntegrityTokenCallback(gni::Task *task, void *user_data) {
    if (task->IsSuccessful()) {
        IntegrityTokenResponse response(task->GetResultObject());
        gni::common::LogD(kLogTag, "Received the token: %s", response.token());
    } else {
        const char *error_message = task->GetErrorMessage();
        gni::common::LogE(kLogTag, "Couldn't receive the token. Error message: %s", error_message);
        GniString_destroy(error_message);
    }

    delete task;
}

extern "C" void requestIntegrityToken(
    const char* nonce, JNIEnv *env, jobject main_activity) {
    gni::common::LogD(kLogTag, "Requesting integrtity token...");

    JavaVM *java_vm;
    env->GetJavaVM(&java_vm);
    gni::GniCore::Init(java_vm, main_activity);

    android::content::Context context(main_activity);

    IntegrityManager &integrity_manager = IntegrityManagerFactory::create(context);
    gni::Task &request_integrity_token_task = integrity_manager.requestIntegrityToken(
            IntegrityTokenRequest::builder().setNonce(nonce).build());
    request_integrity_token_task.AddOnCompleteCallback(RequestIntegrityTokenCallback, nullptr);
}
