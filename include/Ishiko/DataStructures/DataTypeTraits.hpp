// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_DATASTRUCTURES_DATATYPETRAITS_HPP
#define GUARD_ISHIKO_CPP_DATASTRUCTURES_DATATYPETRAITS_HPP

#include <Ishiko/Errors.hpp>
#include <type_traits>

namespace Ishiko
{
    template<typename DataType, typename Enable = void>
    class DataTypeTraits
    {
    };

    template<typename DataType>
    class DataTypeTraits<DataType, typename std::enable_if<std::is_nothrow_copy_constructible<DataType>::value>::type>
    {
    public:
        static DataType Copy(const DataType& source, Error& error);
    };
}

template<typename DataType>
DataType
Ishiko::DataTypeTraits<DataType, typename std::enable_if<std::is_nothrow_copy_constructible<DataType>::value>::type>::
Copy(const DataType& source, Error& error)
{
    return DataType(source);
}

#endif
