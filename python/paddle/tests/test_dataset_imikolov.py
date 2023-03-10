# Copyright (c) 2020 PaddlePaddle Authors. All Rights Reserved.
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

import numpy as np

from paddle.text.datasets import Imikolov


class TestImikolovTrain(unittest.TestCase):
    def test_main(self):
        imikolov = Imikolov(mode='train', data_type='NGRAM', window_size=2)
        self.assertTrue(len(imikolov) == 929589)

        # traversal whole dataset may cost a
        # long time, randomly check 1 sample
        idx = np.random.randint(0, 929589)
        data = imikolov[idx]
        self.assertTrue(len(data) == 2)


class TestImikolovTest(unittest.TestCase):
    def test_main(self):
        imikolov = Imikolov(mode='test', data_type='NGRAM', window_size=2)
        self.assertTrue(len(imikolov) == 82430)

        # traversal whole dataset may cost a
        # long time, randomly check 1 sample
        idx = np.random.randint(0, 82430)
        data = imikolov[idx]
        self.assertTrue(len(data) == 2)


if __name__ == '__main__':
    unittest.main()
