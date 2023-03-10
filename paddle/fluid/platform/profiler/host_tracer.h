// Copyright (c) 2022 PaddlePaddle Authors. All Rights Reserved.
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

#include "paddle/fluid/platform/profiler/tracer_base.h"
#include "paddle/phi/api/profiler/host_tracer.h"

namespace paddle {
namespace platform {

using HostTraceLevel = phi::HostTraceLevel;
using HostTracerOptions = phi::HostTracerOptions;

class HostTracer : public TracerBase {
 public:
  explicit HostTracer(const HostTracerOptions& options) : options_(options) {}

  void PrepareTracing() override;

  void StartTracing() override;

  void StopTracing() override;

  void CollectTraceData(TraceEventCollector* collector) override;

 private:
  HostTracerOptions options_;
};

}  // namespace platform
}  // namespace paddle
