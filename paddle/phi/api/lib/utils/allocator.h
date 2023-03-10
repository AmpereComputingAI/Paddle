/* Copyright (c) 2021 PaddlePaddle Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#pragma once

#include "paddle/phi/common/memory_utils.h"
#include "paddle/phi/common/place.h"
#include "paddle/phi/core/allocator.h"

namespace paddle {
namespace experimental {

class DefaultAllocator : public phi::Allocator {
 public:
  explicit DefaultAllocator(const phi::Place& place) : place_(place) {}

  AllocationPtr Allocate(size_t bytes_size) override {
    return phi::memory_utils::Alloc(place_, bytes_size);
  }

 private:
  phi::Place place_;
};

}  // namespace experimental
}  // namespace paddle
