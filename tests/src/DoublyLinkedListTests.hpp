// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_DATASTRUCTURES_TESTS_DOUBLYLINKEDLISTTESTS_HPP
#define GUARD_ISHIKO_CPP_DATASTRUCTURES_TESTS_DOUBLYLINKEDLISTTESTS_HPP

#include <Ishiko/TestFramework/Core.hpp>

class DoublyLinkedListTests : public Ishiko::TestSequence
{
public:
    DoublyLinkedListTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
};

#endif
