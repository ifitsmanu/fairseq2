// Copyright (c) Meta Platforms, Inc. and affiliates.
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include "fairseq2/native/data/batched_data_source.h"

#include <vector>

namespace fairseq2::detail {

std::optional<data>
batched_data_source::next()
{
    std::vector<data> output{};

    output.reserve(batch_size_);

    for (std::size_t i = 0; i < batch_size_; i++) {
        std::optional<data> d = inner_->next();
        if (!d)
            break;

        output.push_back(*std::move(d));
    }

    if (output.empty())
        return std::nullopt;

    if (drop_remainder_ && output.size() < batch_size_)
        return std::nullopt;

    return data{std::move(output)};
}

void
batched_data_source::reset()
{
    inner_->reset();
}

void
batched_data_source::record_position(tape &t) const
{
    inner_->record_position(t);
}

void
batched_data_source::reload_position(tape &t)
{
    inner_->reload_position(t);
}

}  // namespace fairseq2::detail
