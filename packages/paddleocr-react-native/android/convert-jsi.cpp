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

#include "convert-jsi.h"

// Runtime, Object, Array, Value, String
using namespace facebook::jsi;

// any string vector unordered_map
using namespace std;

vector<any> convertJsiArray(Runtime& runtime, const Array& arr) {
  vector<any> vector;
  size_t length = arr.size(runtime);
  for (size_t i = 0; i < length; i++) {
    vector.push_back(convertJsiValue(runtime, arr.getValueAtIndex(runtime, i)));
  }
  return vector;
}

unordered_map<string, any> convertJsiObject(Runtime& runtime, const Object& obj) {
  auto map = make_shared<unordered_map<string, any>>();
  auto propertyNames = obj.getPropertyNames(runtime);
  for (size_t i = 0; i < propertyNames.size(runtime); i++) {
    auto nameValue = propertyNames.getValueAtIndex(runtime, i).asString(runtime);
    string key = nameValue.utf8(runtime);
    Value propValue = obj.getProperty(runtime, nameValue);
    (*map)[key] = convertJsiValue(runtime, propValue);
  }
  return *map;
}

any convertJsiValue(Runtime& runtime, const Value& value) {
  if (value.isString()) {
    return value.asString(runtime).utf8(runtime);
  } else if (value.isNumber()) {
    return value.asNumber();
  } else if (value.isBool()) {
    return value.getBool();
  } else if (value.isNull() || value.isUndefined()) {
    return nullptr;
  } else if (value.isObject()) {
    auto obj = value.asObject(runtime);
    if (obj.isArray(runtime)) {
      return convertJsiArray(runtime, obj.asArray(runtime));
    } else {
      return convertJsiObject(runtime, obj);
    }
  } else {
    throw JSError(runtime, "convertJsiValue type is not supported");
  }
}
