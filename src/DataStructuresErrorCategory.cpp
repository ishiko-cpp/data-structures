// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "DataStructuresErrorCategory.hpp"

using namespace Ishiko;

const DataStructuresErrorCategory& DataStructuresErrorCategory::Get() noexcept
{
    static DataStructuresErrorCategory the_category;
    return the_category;
}

const char* DataStructuresErrorCategory::name() const noexcept
{
    return "Ishiko::DataStructuresErrorCategory";
}

const char* DataStructuresErrorCategory::message(int ev, char* buffer, size_t len) const noexcept
{
    switch (static_cast<Value>(ev))
    {
    case Value::generic_error:
        return "generic error";

    case Value::node_does_not_exist:
        return "node does not exist";

    default:
        return "unknown value";
    }
}

void Ishiko::Fail(DataStructuresErrorCategory::Value value, const std::string& message, const char* file, int line,
    Error& error) noexcept
{
    error.fail(DataStructuresErrorCategory::Get(), static_cast<int>(value), message, file, line);
}