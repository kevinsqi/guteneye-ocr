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

#include <onnxruntime_cxx_api.h>
#include <vector>

struct ModelOutput {
  std::vector<float> data {};
  std::vector<int64_t> shape {};
};

using AllocatedStringPtr = std::unique_ptr<char, Ort::detail::AllocatedFree>;

class Onnx {
public:
  Onnx(const std::string &model_path);
  ModelOutput run(std::vector<float> &input, const std::vector<int64_t> &input_shape);

private:
  Ort::Env m_env;
  Ort::Session m_session;
  std::vector<const char *> m_input_names {};
  std::vector<const char *> m_output_names {};
  Ort::AllocatorWithDefaultOptions m_allocator;
  std::vector<AllocatedStringPtr> m_input_name_allocated;
  std::vector<AllocatedStringPtr> m_output_name_allocated;
};
