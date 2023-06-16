// Copyright (c) Meta Platforms, Inc. and affiliates.
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#include "fairseq2/native/api.h"
#include "fairseq2/native/data/data_processor.h"

namespace fairseq2 {

class FAIRSEQ2_API text_splitter final : public data_processor {
public:
    explicit
    text_splitter(char separator = '\t') noexcept
        : separator_{separator}
    {}

    data
    operator()(data &&d) const override;

private:
    char separator_;
};

}  // namespace fairseq2
