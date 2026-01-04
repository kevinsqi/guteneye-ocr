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

#include "options.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

Options convertRawOptions(std::unordered_map<std::string, std::any>& rawOptions, const std::string& assetDir,
                          const std::string& debugOutputDir) {
  Options options {};

  if (rawOptions.count("isDebug") > 0) {
    options.is_debug = std::any_cast<bool>(rawOptions.at("isDebug"));
  }
  if (rawOptions.count("debugOutputDir") == 0) {
    rawOptions["debugOutputDir"] = debugOutputDir;
  }
  if (rawOptions.count("debugOutputDir") > 0) {
    options.debug_output_dir = std::any_cast<std::string>(rawOptions.at("debugOutputDir"));
    fs::create_directories(options.debug_output_dir);
  }
  if (rawOptions.count("detectionMaxSize") > 0) {
    options.detection_max_size = std::any_cast<double>(rawOptions.at("detectionMaxSize"));
  }
  if (rawOptions.count("detectionThreshold") > 0) {
    options.detection_threshold = std::any_cast<double>(rawOptions.at("detectionThreshold"));
  }
  if (rawOptions.count("detectionBoxThreshold") > 0) {
    options.detection_box_threshold = std::any_cast<double>(rawOptions.at("detectionBoxThreshold"));
  }
  if (rawOptions.count("detectionUnclipRatio") > 0) {
    options.detection_unclip_ratio = std::any_cast<double>(rawOptions.at("detectionUnclipRatio"));
  }
  if (rawOptions.count("detectionUseDilate") > 0) {
    options.detection_use_dilate = std::any_cast<bool>(rawOptions.at("detectionUseDilate"));
  }
  if (rawOptions.count("detectionUsePolygonScore") > 0) {
    options.detection_use_polygon_score = std::any_cast<bool>(rawOptions.at("detectionUsePolygonScore"));
  }
  if (rawOptions.count("recognitionImageHeight") > 0) {
    options.recognition_image_height = static_cast<int>(std::any_cast<double>(rawOptions.at("recognitionImageHeight")));
  }

  // Set default model paths if not provided
  if (rawOptions.count("models") == 0) {
    rawOptions["models"] = std::unordered_map<std::string, std::any> {
        {"detectionPath", assetDir + "/det.onnx"},
        {"recognitionPath", assetDir + "/rec.onnx"},
        {"dictionaryPath", assetDir + "/dict.txt"}};
  }

  auto rawModels = std::any_cast<std::unordered_map<std::string, std::any>>(rawOptions.at("models"));
  auto& models = options.models;

  if (rawModels.count("detectionPath") == 0) {
    models.detection_model_path = assetDir + "/det.onnx";
  } else {
    models.detection_model_path = std::any_cast<std::string>(rawModels.at("detectionPath"));
  }

  if (rawModels.count("recognitionPath") == 0) {
    models.recognition_model_path = assetDir + "/rec.onnx";
  } else {
    models.recognition_model_path = std::any_cast<std::string>(rawModels.at("recognitionPath"));
  }

  if (rawModels.count("dictionaryPath") == 0) {
    models.dictionary_path = assetDir + "/dict.txt";
  } else {
    models.dictionary_path = std::any_cast<std::string>(rawModels.at("dictionaryPath"));
  }

  return options;
}
