# Copyright (c) 2021 PaddlePaddle Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import unittest
import warnings

import paddle


class TestTensorTypePromotion(unittest.TestCase):
    def setUp(self):
        self.x = paddle.to_tensor([2, 3])
        self.y = paddle.to_tensor([1.0, 2.0])

    def add_operator(self):
        with warnings.catch_warnings(record=True) as context:
            warnings.simplefilter("always")
            self.x + self.y

    def sub_operator(self):
        with warnings.catch_warnings(record=True) as context:
            warnings.simplefilter("always")
            self.x - self.y

    def mul_operator(self):
        with warnings.catch_warnings(record=True) as context:
            warnings.simplefilter("always")
            self.x * self.y

    def div_operator(self):
        with warnings.catch_warnings(record=True) as context:
            warnings.simplefilter("always")
            self.x / self.y

    def test_operator(self):
        self.setUp()
        self.add_operator()
        self.sub_operator()
        self.mul_operator()
        self.div_operator()


if __name__ == '__main__':
    unittest.main()
