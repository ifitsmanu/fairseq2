// Copyright (c) Meta Platforms, Inc. and affiliates.
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <utility>
#include <variant>
#include <vector>

#include <ATen/Tensor.h>

#include "fairseq2/native/py.h"
#include "fairseq2/native/data/immutable_string.h"

namespace fairseq2 {

class data {
public:
    data() noexcept = default;

    data(const data &) = default;
    data &operator=(const data &) = default;

    data(data &&other) noexcept = default;
    data &operator=(data &&other) noexcept = default;

   ~data() = default;

    // bool
    data(bool value) noexcept
        : payload_{value}
    {}

    bool
    is_bool() const noexcept
    {
        return is<bool>();
    }

    bool
    as_bool() const noexcept
    {
        return as<bool>();
    }

    // int
    data(std::int64_t value) noexcept
        : payload_{value}
    {}

    bool
    is_int() const noexcept
    {
        return is<std::int64_t>();
    }

    std::int64_t
    as_int() const noexcept
    {
        return as<std::int64_t>();
    }

    // double
    data(double value) noexcept
        : payload_{value}
    {}

    bool
    is_double() const noexcept
    {
        return is<double>();
    }

    double
    as_double() const noexcept
    {
        return as<double>();
    }

    // string
    data(const char *value)
        : payload_{immutable_string{value}}
    {}

    data(const std::string &value)
        : payload_{immutable_string{value}}
    {}

    data(std::string_view value)
        : payload_{immutable_string{value}}
    {}

    data(const immutable_string &value) noexcept
        : payload_{value}
    {}

    data(immutable_string &&value) noexcept
        : payload_{std::move(value)}
    {}

    bool
    is_string() const noexcept
    {
        return is<immutable_string>();
    }

    immutable_string &
    as_string() & noexcept
    {
        return as<immutable_string>();
    }

    const immutable_string &
    as_string() const & noexcept
    {
        return as<immutable_string>();
    }

    immutable_string &&
    as_string() && noexcept
    {
        return move_as<immutable_string>();
    }

    // Tensor
    data(const at::Tensor &value)
        : payload_{value}
    {}

    data(at::Tensor &&value)
        : payload_{std::move(value)}
    {}

    bool
    is_tensor() const noexcept
    {
        return is<at::Tensor>();
    }

    at::Tensor &
    as_tensor() & noexcept
    {
        return as<at::Tensor>();
    }

    const at::Tensor &
    as_tensor() const & noexcept
    {
        return as<at::Tensor>();
    }

    at::Tensor &&
    as_tensor() && noexcept
    {
        return move_as<at::Tensor>();
    }

    // list
    data(const std::vector<data> &value)
        : payload_{value}
    {}

    data(std::vector<data> &&value)
        : payload_{std::move(value)}
    {}

    bool
    is_list() const noexcept
    {
        return is<std::vector<data>>();
    }

    std::vector<data> &
    as_list() & noexcept
    {
        return as<std::vector<data>>();
    }

    const std::vector<data> &
    as_list() const & noexcept
    {
        return as<std::vector<data>>();
    }

    std::vector<data> &&
    as_list() && noexcept
    {
        return move_as<std::vector<data>>();
    }

    // py_object
    data(const py_object &value) noexcept
        : payload_{value}
    {}

    data(py_object &&value) noexcept
        : payload_{std::move(value)}
    {}

    bool
    is_py() const noexcept
    {
        return is<py_object>();
    }

    py_object &
    as_py() & noexcept
    {
        return as<py_object>();
    }

    const py_object &
    as_py() const & noexcept
    {
        return as<py_object>();
    }

    py_object &&
    as_py() && noexcept
    {
        return move_as<py_object>();
    }

private:
    template <typename T>
    bool
    is() const noexcept
    {
        return std::holds_alternative<T>(payload_);
    }

    template <typename T>
    T &
    as() noexcept
    {
        return *std::get_if<T>(&payload_);
    }

    template <typename T>
    const T &
    as() const noexcept
    {
        return *std::get_if<T>(&payload_);
    }

    template <typename T>
    T &&
    move_as() noexcept
    {
        return std::move(as<T>());
    }

private:
    std::variant<bool,
                 std::int64_t,
                 double,
                 immutable_string,
                 at::Tensor,
                 std::vector<data>,
                 py_object> payload_{};
};

}  // namespace fairseq2