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

#include <any>
#include <string>
#include <unordered_map>

struct OptionModels {
  std::string detection_model_path {};
  std::string recognition_model_path {};
  std::string dictionary_path {};
};

struct Options {
  bool is_debug {false};
  std::string debug_output_dir {};
  double detection_max_size {960};  // -1 to disable resize
  double detection_threshold {0.3};
  double detection_box_threshold {0.5};
  double detection_unclip_ratio {1.6};
  bool detection_use_dilate {false};
  bool detection_use_polygon_score {true};
  int recognition_image_height {48};  // PP-OCRv5 uses 48
  OptionModels models {};
};

Options convertRawOptions(std::unordered_map<std::string, std::any>& rawOptions, const std::string& assetDir,
                          const std::string& debugOutputDir);
