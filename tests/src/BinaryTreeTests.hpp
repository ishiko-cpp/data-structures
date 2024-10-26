// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_DATASTRUCTURES_TESTS_BINARYTREETESTS_HPP
#define GUARD_ISHIKO_CPP_DATASTRUCTURES_TESTS_BINARYTREETESTS_HPP

#include <Ishiko/TestFramework/Core.hpp>

class BinaryTreeTests : public Ishiko::TestSequence
{
public:
    BinaryTreeTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void ConstructorTest2(Ishiko::Test& test);
    static void SetRootTest1(Ishiko::Test& test);
    static void SetRootTest2(Ishiko::Test& test);
    static void SetRootTest3(Ishiko::Test& test);
    static void SetRootTest4(Ishiko::Test& test);
    static void InsertLeftTest1(Ishiko::Test& test);
    static void InsertLeftTest2(Ishiko::Test& test);
    static void InsertRightTest1(Ishiko::Test& test);
    static void InsertRightTest2(Ishiko::Test& test);
    static void DoInorderTraversalTest1(Ishiko::Test& test);
    static void DoInorderTraversalTest2(Ishiko::Test& test);
    static void DoInorderTraversalTest3(Ishiko::Test& test);
    static void RotateLeftTest1(Ishiko::Test& test);
    static void RotateLeftTest2(Ishiko::Test& test);
    static void RotateRightTest1(Ishiko::Test& test);
    static void RotateRightTest2(Ishiko::Test& test);
};

#endif
