// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_DATASTRUCTURES_DATASTRUCTURESERRORCATEGORY_HPP
#define GUARD_ISHIKO_CPP_DATASTRUCTURES_DATASTRUCTURESERRORCATEGORY_HPP

#include <Ishiko/Errors.hpp>

namespace Ishiko
{
    class DataStructuresErrorCategory : public ErrorCategory
    {
    public:
        enum class Value
        {
            generic_error = -1,
            node_does_not_exist = -2
        };

        static const DataStructuresErrorCategory& Get() noexcept;

        const char* name() const noexcept override;
        const char* message(int ev, char* buffer, size_t len) const noexcept override;

    private:
        DataStructuresErrorCategory() noexcept = default;
    };

    void Fail(DataStructuresErrorCategory::Value value, const std::string& message, const char* file, int line,
        Error& error) noexcept;
}

#endif
