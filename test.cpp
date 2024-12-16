//#include <catch2/catch_test_macros.hpp>
//#include <iostream>
//#include "AVL.h"
//#include "AVL.cpp"
//#include "random.h"
//#include <algorithm>
//using namespace std;
//
//TEST_CASE("Test Case 1"){
//    Tree tree;
//
//    //TODO test at least 5 incorrect commands
//
//}
//
//TEST_CASE("Test Case 2"){
//    Tree tree;
//
//    tree.insert("00000100", "a");
//    tree.insert("00000050", "a");
//    tree.insert("00000033", "a");
//    tree.insert("00000067", "a");
//    tree.insert("00000055", "a");
//    tree.insert("00000120", "a");
//
//    // trying to remove a node not in the tree
//    tree.remove("00000000");
//    REQUIRE(tree.printPostorder().size() == 6);
//
//    // inserting a node with a long name
//    tree.insert("00000078", "Sir Edward Jonathan larson Wolfeschlegelsteinhausenbergerdorff "
//                            "XVI doctor in psychology doctor in medicine doctor in "
//                            "psychoanalysis graduated Yale suma cum laude son of the cobbler thomas "
//                            "Wolfeschlegelsteinhausenbergerdorff who was son of the cobbler George "
//                            "Wolfeschlegelsteinhausenbergerdorff writer of the first edition of Botany a guide for "
//                            "those interested in the interesting world of plants");
//    REQUIRE(tree.printPostorder().size() == 7);
//
//    // removing inOrder with N > tree size
//    tree.removeInorder(1000);
//    REQUIRE(tree.printPostorder().size() == 7);
//    //TODO test at least 3 edge cases, including removing a node that does not exist
//
//}
//TEST_CASE("Test Case 3"){
//    Tree tree;
//    //TODO test all 4 rotation cases
//
//    //right rotation
//    tree.insert("00000005", "e");
//    tree.insert("00000003", "c");
//    tree.insert("00000001", "a");
//    vector<string> expected = {"a", "e", "c"};
//    REQUIRE(tree.printPostorder().size() == 3);
//    REQUIRE(tree.printPostorder() == expected);
//
//    //left rotation
//    tree.insert("00000006", "f");
//    tree.insert("00000007", "g");
//    expected = {"a", "e", "g", "f", "c"};
//    REQUIRE(tree.printPostorder().size() == 5);
//    REQUIRE(tree.printPostorder() == expected);
//
//    // right left rotation
//    tree.insert("00000004", "d");
//    expected = {"a", "d", "c", "g", "f", "e"};
//    REQUIRE(tree.printPostorder().size() == 6);
//    REQUIRE(tree.printPostorder() == expected);
//
//    //left right rotation
//    Tree tree2;
//    expected = {"john", "bob", "mary"};
//    tree2.insert("00000008", "bob");
//    tree2.insert("00000003", "john");
//    tree2.insert("00000004", "mary");
//    REQUIRE(tree2.printPostorder().size() == 3);
//    REQUIRE(tree2.printPostorder() == expected);
//}
//
//TEST_CASE("Test Case 4"){
//    //TODO test all 3 deletion cases
//    Tree tree;
//    tree.insert("00000100", "a");
//    tree.insert("00000050", "b");
//    tree.insert("00000033", "c");
//    tree.insert("00000067", "d");
//    tree.insert("00000055", "e");
//    tree.insert("00000120", "f");
//
//    // no child delete
//    vector<string> expected = {"d", "b", "c", "e", "a"};
//    tree.remove("00000120");
//    REQUIRE(tree.printPreorder() == expected);
//    // one child delete
//    expected = {"b", "g", "d", "e", "a"};
//    tree.insert("00000010", "g");
//    tree.remove("00000033");
//    REQUIRE(tree.printPreorder() == expected);
//    // two children delete
//    tree.remove("00000067");
//    expected = {"b", "g", "a", "e"};
//    REQUIRE(tree.printPreorder() == expected);
//}
//
//TEST_CASE("Test Case 5"){
//    Tree tree;   // Create a Tree object
//
//    vector<string> randomIDs = Random::randIDs(1000);
//
//    for (unsigned int i = 0; i < randomIDs.size(); i++)
//    {
//        tree.insert(randomIDs[i], randomIDs[i]);
//    }
//    for (int i = 0; i < 10; i++){
//        int randIndex = Random::Int(0, 900);    //ensure that an index out of range error never occurs
//        tree.remove(randomIDs[randIndex]);
//        randomIDs.erase(randomIDs.begin() + randIndex);
//    }
//    REQUIRE(randomIDs.size() == tree.printPreorder().size());
//    std::sort(randomIDs.begin(), randomIDs.end());
//    REQUIRE(randomIDs == tree.printInorder());
//}
//
//TEST_CASE("Easy Test1", "[AVL]"){
//    Tree tree;   // Create a Tree object
//    tree.insert("3", "bob");
//    tree.insert("2", "tim");
//    tree.insert("1", "john" );
//    std::vector<string> actualOutput = tree.printPreorder();
//
//    std::vector<string> expectedOutput = {"tim", "john", "bob"};
//    REQUIRE(expectedOutput.size() == actualOutput.size());
//    REQUIRE(actualOutput == expectedOutput);
//}
//
//TEST_CASE("Big Test1"){
//    // For testing purposes, a large number of "students" will be generated, each having a random
//    // ID and a name that is the same as their ID.
//    Tree tree;   // Create a Tree object
//
//    vector<string> randomIDs = Random::randIDs(1000);
//    for (unsigned int i = 0; i < randomIDs.size(); i++)
//    {
//        tree.insert(randomIDs[i], randomIDs[i]);
//    }
//    REQUIRE(randomIDs.size() == tree.printPreorder().size());
//    std::sort(randomIDs.begin(), randomIDs.end());
//    REQUIRE(randomIDs == tree.printInorder());
//}
