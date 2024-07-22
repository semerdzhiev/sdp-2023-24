#include "catch2/catch_all.hpp"
#include "Dictionary.h"

// IMPORTANT: Do not modify this file.
// If you want to add additional unit test,
// create a new file in the same directory,
// ot use the supplied `test-Additional.cpp` file.

TEST_CASE("Dictionary::isCorrectWord() returns true for a correct word")
{
    REQUIRE(Dictionary::isCorrectWord("a"));
    REQUIRE(Dictionary::isCorrectWord("abcdefghijklmnopqrstuvwxyz"));
    REQUIRE(Dictionary::isCorrectWord("abcde"));
    REQUIRE(Dictionary::isCorrectWord("Abcde"));
    REQUIRE(Dictionary::isCorrectWord("AbCdE"));
    REQUIRE(Dictionary::isCorrectWord("aBcDe"));
    REQUIRE(Dictionary::isCorrectWord("ABCDE"));
}

TEST_CASE("Dictionary::isCorrectWord() returns false for nullptr")
{
    REQUIRE_FALSE(Dictionary::isCorrectWord(nullptr));
}

TEST_CASE("Dictionary::isCorrectWord() returns false for an empty word")
{
    REQUIRE_FALSE(Dictionary::isCorrectWord(""));
}

TEST_CASE("Dictionary::isCorrectWord() returns false for a string of whitespace characters")
{
    REQUIRE_FALSE(Dictionary::isCorrectWord(" "));
    REQUIRE_FALSE(Dictionary::isCorrectWord("\t"));
    REQUIRE_FALSE(Dictionary::isCorrectWord("\n"));
    REQUIRE_FALSE(Dictionary::isCorrectWord(" \r\n\t"));
}

TEST_CASE("Dictionary::isCorrectWord() returns false for an incorrect word")
{
    REQUIRE_FALSE(Dictionary::isCorrectWord("hello world"));
    REQUIRE_FALSE(Dictionary::isCorrectWord("hello,world"));
    REQUIRE_FALSE(Dictionary::isCorrectWord("hello123"));
    REQUIRE_FALSE(Dictionary::isCorrectWord("123world"));
    REQUIRE_FALSE(Dictionary::isCorrectWord(" hello"));
    REQUIRE_FALSE(Dictionary::isCorrectWord("hello "));
}

TEST_CASE("Dictionary::Dictionary() creates an empty dictionary")
{
    Dictionary dict;
    CHECK(dict.size() == 0);
}

TEST_CASE("Dictionary::insert() inserts a word into the dictionary")
{
    Dictionary dict;
    dict.insert("hello");
    REQUIRE(dict.size() == 1);
    REQUIRE(dict.contains("hello"));
}

TEST_CASE("Dictionary::insert() throws an exception if the word is incorrect")
{
    Dictionary dict;
    CHECK_THROWS_AS(dict.insert(nullptr), incorrect_word_exception);
    CHECK_THROWS_AS(dict.insert(""), incorrect_word_exception);
    CHECK_THROWS_AS(dict.insert(" "), incorrect_word_exception);
    CHECK_THROWS_AS(dict.insert("\t"), incorrect_word_exception);
    CHECK_THROWS_AS(dict.insert("\n"), incorrect_word_exception);
    CHECK_THROWS_AS(dict.insert(" \r\n\t"), incorrect_word_exception);
    CHECK_THROWS_AS(dict.insert("hello world"), incorrect_word_exception);
    CHECK_THROWS_AS(dict.insert("hello,world"), incorrect_word_exception);
    CHECK_THROWS_AS(dict.insert("hello123"), incorrect_word_exception);
    CHECK_THROWS_AS(dict.insert("123world"), incorrect_word_exception);
    CHECK_THROWS_AS(dict.insert(" hello"), incorrect_word_exception);
    CHECK_THROWS_AS(dict.insert("hello "), incorrect_word_exception);
}

TEST_CASE("Dictionary::erase() erases a word from the dictionary")
{
    Dictionary dict;
    dict.insert("hello");
    dict.erase("hello");
    REQUIRE(dict.size() == 0);
    REQUIRE_FALSE(dict.contains("hello"));
}

TEST_CASE("Dictionary::erase() does not raise an error if the word is not in the dictionary")
{
    Dictionary dict;
    dict.insert("hello");
    dict.erase("world");
    REQUIRE(dict.size() == 1);
    REQUIRE(dict.contains("hello"));
}

TEST_CASE("Dictionary::erase() does not raise an error for nullptr")
{
    Dictionary dict;
    dict.insert("hello");
    dict.erase(nullptr);
    REQUIRE(dict.size() == 1);
    REQUIRE(dict.contains("hello"));
}

TEST_CASE("Dictionary::contains() returns true if the word is in the dictionary")
{
    Dictionary dict;
    dict.insert("hello");
    REQUIRE(dict.contains("hello"));
}

TEST_CASE("Dictionary::contains() returns false if the word is not in the dictionary")
{
    Dictionary dict;
    REQUIRE_FALSE(dict.contains("hello"));
}

TEST_CASE("Dictionary::contains() returns false for nullptr")
{
    Dictionary dict;
    REQUIRE_FALSE(dict.contains(nullptr));
}

TEST_CASE("Dictionary::size() returns the number of words in the dictionary")
{
    Dictionary dict;
    dict.insert("hello");
    dict.insert("world");
    REQUIRE(dict.size() == 2);
}

