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

#pragma once

#include <iostream>
#include <vector>

struct ImageRaw {
  std::vector<float> data {};
  int64_t width {};
  int64_t height {};
  int64_t channels {};
};

struct ModelPerformance {
  float total_time {};
  float preprocess_time {};
  float predict_time {};
  float postprocess_time {};
};

struct Frame {
  int top {};
  int left {};
  int width {};
  int height {};
};

std::ostream& operator<<(std::ostream& os, const Frame& frame);

struct TextLine {
  std::string text {};
  float score {};
  Frame frame {};
};
