// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_DATASTRUCTURES_TESTS_SKIPLISTTESTS_HPP
#define GUARD_ISHIKO_CPP_DATASTRUCTURES_TESTS_SKIPLISTTESTS_HPP

#include <Ishiko/TestFramework/Core.hpp>

class SkipListTests : public Ishiko::TestSequence
{
public:
    SkipListTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void InsertTest1(Ishiko::Test& test);
    static void InsertTest2(Ishiko::Test& test);
    static void InsertTest3(Ishiko::Test& test);
    static void InsertTest4(Ishiko::Test& test);
    static void InsertTest5(Ishiko::Test& test);
    static void InsertTest6(Ishiko::Test& test);
    static void InsertTest7(Ishiko::Test& test);
};

#endif
