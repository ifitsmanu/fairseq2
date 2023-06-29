// Copyright (c) Meta Platforms, Inc. and affiliates.
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include "fairseq2/native/extension/module.h"

namespace py = pybind11;

namespace fairseq2 {

void
def_data(py::module_ &base)
{
    py::module_ m = base.def_submodule("data");

    def_data_pipeline(m);

    def_memory(m);

    def_processors(m);

    def_string(m);

    def_text(m);
}

}  // namespace fairseq2
