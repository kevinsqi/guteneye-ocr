// Copyright (c) 2021 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <android/log.h>
#include <jni.h>
#include <jsi/jsi.h>
#include <iostream>
#include "convert-jsi.h"
#include "convert-std.h"
#include "native-paddleocr.h"

#define LOG_TAG "RNPaddleOcrModule"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

using namespace facebook::jsi;

std::unique_ptr<NativePaddleOcr> _ocr;
std::string _assetDir;
std::string _debugOutputDir;

void install(Runtime &runtime) {
  auto create = Function::createFromHostFunction(
      runtime, PropNameID::forAscii(runtime, "create"), 1,
      [](Runtime &runtime, const Value &thisValue, const Value *arguments, size_t count) -> Value {
        if (count != 1 || !arguments[0].isObject()) {
          throw JSError(runtime, "PaddleOcr.create: Expected a single options argument");
        }
        Object obj = arguments[0].asObject(runtime);
        auto options = convertJsiObject(runtime, obj);
        _ocr = std::make_unique<NativePaddleOcr>(options, _assetDir, _debugOutputDir);
        return Value::undefined();
      });
  runtime.global().setProperty(runtime, "create", std::move(create));

  auto detect = Function::createFromHostFunction(
      runtime, PropNameID::forAscii(runtime, "detect"), 1,
      [](Runtime &runtime, const Value &thisValue, const Value *arguments, size_t count) -> Value {
        if (count != 1 || !arguments[0].isString()) {
          throw JSError(runtime, "paddleOcr.detect: Expected a single imagePath argument");
        }
        auto imagePath = arguments[0].asString(runtime).utf8(runtime);
        auto lines = _ocr->detect(imagePath);
        return convertStdVectorTextLine(runtime, lines);
      });
  runtime.global().setProperty(runtime, "detect", std::move(detect));
}

extern "C" JNIEXPORT void JNICALL Java_com_paddleocr_RNPaddleOcrModule_nativeInstall(JNIEnv *env, jobject thiz, jlong jsi,
                                                                                      jstring assetDir, jstring debugOutputDir) {
  auto runtime = reinterpret_cast<Runtime *>(jsi);
  install(*runtime);

  const char *cAssetDir = env->GetStringUTFChars(assetDir, nullptr);
  const char *cDebugOuputDir = env->GetStringUTFChars(debugOutputDir, nullptr);
  _assetDir = std::string(cAssetDir);
  _debugOutputDir = std::string(cDebugOuputDir);
  env->ReleaseStringUTFChars(assetDir, cAssetDir);
  env->ReleaseStringUTFChars(debugOutputDir, cDebugOuputDir);
}
