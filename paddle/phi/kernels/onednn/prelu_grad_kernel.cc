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

#include "paddle/phi/kernels/prelu_grad_kernel.h"

#include "paddle/phi/backends/onednn/onednn_reuse.h"
#include "paddle/phi/core/kernel_registry.h"

namespace phi {

template <typename T, typename Context>
void PReluGradKernel(const Context& dev_ctx,
                     const DenseTensor& x,
                     const DenseTensor& alpha,
                     const DenseTensor& out_grad,
                     const std::string& data_format,
                     const std::string& mode,
                     DenseTensor* x_grad,
                     DenseTensor* alpha_grad) {
  bool is_test = dev_ctx.HasDnnAttr("is_test")
                     ? PADDLE_GET_CONST(bool, dev_ctx.GetDnnAttr("is_test"))
                     : false;
  funcs::PReluOneDNNHandler<T> handler(dev_ctx.GetEngine(),
                                       dev_ctx.GetPlace(),
                                       x,
                                       alpha,
                                       mode,
                                       data_format,
                                       is_test);

  auto src_memory_p = handler.AcquireSrcMemory(&x);
  auto weights_memory_p =
      handler.AcquireWeightsMemoryPossiblyWithReorder(&alpha, is_test);
  auto diff_src_memory_p = handler.AcquireDiffSrcMemory(x_grad);
  auto diff_weights_memory_p = handler.AcquireDiffWeightsMemory(alpha_grad);
  auto diff_dst_memory_p = handler.AcquireDiffDstMemory(&out_grad);
  auto prelu_p = handler.AcquireBackwardPrimitive();

  auto& astream = OneDNNContext::tls().get_stream();
  prelu_p->execute(astream,
                   {{DNNL_ARG_SRC, *src_memory_p},
                    {DNNL_ARG_WEIGHTS, *weights_memory_p},
                    {DNNL_ARG_DIFF_DST, *diff_dst_memory_p},
                    {DNNL_ARG_DIFF_SRC, *diff_src_memory_p},
                    {DNNL_ARG_DIFF_WEIGHTS, *diff_weights_memory_p}});
  astream.wait();

  x_grad->set_mem_desc(diff_src_memory_p->get_desc());
}

}  // namespace phi

PD_REGISTER_KERNEL(prelu_grad,
                   OneDNN,
                   ONEDNN,
                   phi::PReluGradKernel,
                   float,
                   phi::dtype::bfloat16) {}
