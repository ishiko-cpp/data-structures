// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "BinaryTreeTests.hpp"
#include "DoublyLinkedListTests.hpp"
#include "RedBlackTreeTests.hpp"
#include "SinglyLinkedListTests.hpp"
#include "SkipListTests.hpp"
#include "Ishiko/DataStructures/linkoptions.hpp"
#include <Ishiko/TestFramework/Core.hpp>
#include <exception>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    try
    {
        TestHarness::CommandLineSpecification command_line_spec;
        Configuration configuration = command_line_spec.createDefaultConfiguration();
        CommandLineParser::parse(command_line_spec, argc, argv, configuration);

        TestHarness the_test_harness("Ishiko/C++ DataStructures Library Tests", configuration);

        TestSequence& the_tests = the_test_harness.tests();
        the_tests.append<SinglyLinkedListTests>();
        the_tests.append<DoublyLinkedListTests>();
        the_tests.append<SkipListTests>();
        the_tests.append<BinaryTreeTests>();
        the_tests.append<RedBlackTreeTests>();

        return the_test_harness.run();
    }
    catch (const std::exception& e)
    {
        return TestApplicationReturnCode::exception;
    }
    catch (...)
    {
        return TestApplicationReturnCode::exception;
    }
}
