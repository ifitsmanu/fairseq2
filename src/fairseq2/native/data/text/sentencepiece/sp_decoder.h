// Copyright (c) Meta Platforms, Inc. and affiliates.
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#include <memory>
#include <vector>

#include <ATen/Tensor.h>

#include "fairseq2/native/api.h"
#include "fairseq2/native/span.h"
#include "fairseq2/native/data/data.h"
#include "fairseq2/native/data/data_processor.h"

namespace fairseq2 {
namespace detail {

class decoder_op;

}

class sp_model;

class FAIRSEQ2_API sp_decoder final : public data_processor {
    friend class detail::decoder_op;

public:
    explicit
    sp_decoder(
        std::shared_ptr<const sp_model> m,
        bool reverse = false,
        bool disable_parallelism = false) noexcept;

    data
    process(data &&d) const override;

private:
    std::vector<data>
    decode(at::Tensor &&t) const;

private:
    std::shared_ptr<const sp_model> model_;
    bool reverse_;
    bool disable_parallelism_;
};

}  // namespace fairseq2
