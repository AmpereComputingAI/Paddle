//   Copyright (c) 2018 PaddlePaddle Authors. All Rights Reserved.
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

#include "paddle/fluid/operators/assign_value_op.h"

#include <string>

#include "paddle/fluid/framework/infershape_utils.h"
#include "paddle/phi/core/infermeta_utils.h"
#include "paddle/phi/infermeta/nullary.h"

namespace paddle {
namespace framework {
class InferShapeContext;
class OpDesc;
template <typename T>
class EmptyGradOpMaker;
}  // namespace framework
namespace imperative {
class OpBase;
}  // namespace imperative
}  // namespace paddle

namespace paddle {
namespace operators {

class AssignValueOp : public framework::OperatorWithKernel {
 public:
  AssignValueOp(const std::string &type,
                const framework::VariableNameMap &inputs,
                const framework::VariableNameMap &outputs,
                const framework::AttributeMap &attrs)
      : OperatorWithKernel(type, inputs, outputs, attrs) {}

 protected:
  phi::KernelKey GetExpectedKernelType(
      const framework::ExecutionContext &ctx) const override {
    return phi::KernelKey(
        framework::proto::VarType::Type(ctx.Attr<int>("dtype")),
        ctx.GetPlace());
  }
};

class AssignValueOpMaker : public framework::OpProtoAndCheckerMaker {
 public:
  void Make() override {
    AddOutput("Out", "(Tensor) Output tensor of assign_value operator.");
    AddAttr<std::vector<int>>("shape",
                              "(vector<int>) "
                              "Shape of values.");
    AddAttr<int>("dtype", "data type of values")
        .InEnum({framework::proto::VarType::BOOL,
                 framework::proto::VarType::INT32,
                 framework::proto::VarType::FP32,
                 framework::proto::VarType::INT64});
    AddAttr<std::vector<int>>("bool_values", "store the bool values")
        .SetDefault({});
    AddAttr<std::vector<float>>("fp32_values", "store the float32 values")
        .SetDefault({});
    AddAttr<std::vector<int>>("int32_values", "store the int32 values")
        .SetDefault({});
    AddAttr<std::vector<int64_t>>("int64_values", "store the int64 values")
        .SetDefault({});
    AddComment(R"DOC(
AssignValue operator

$$Out = values$$
)DOC");
  }
};

}  // namespace operators
}  // namespace paddle

namespace ops = paddle::operators;

DECLARE_INFER_SHAPE_FUNCTOR(assign_value,
                            AssignValueInferShapeFunctor,
                            PD_INFER_META(phi::AssignValueInferMeta));
REGISTER_OPERATOR(
    assign_value,
    ops::AssignValueOp,
    ops::AssignValueOpMaker,
    paddle::framework::EmptyGradOpMaker<paddle::framework::OpDesc>,
    paddle::framework::EmptyGradOpMaker<paddle::imperative::OpBase>,
    AssignValueInferShapeFunctor);
