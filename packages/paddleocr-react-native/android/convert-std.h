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

#include <jsi/jsi.h>
#include <string>
#include <vector>
#include "shared.h"

using namespace facebook::jsi;
using namespace std;

String convertStdString(Runtime& runtime, const string& stdString);

Array convertStdVector(Runtime& runtime, const vector<string>& stdVector);

Array convertStdVectorTextLine(Runtime& runtime, const vector<TextLine>& stdVector);
