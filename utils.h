/**
  Author: @Harry Long

  Various utility/helper functions
  */
#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <vector>
#include <functional>

namespace FileUtils{
    /**
     * @brief exists
     * @param filename
     * @return  Checks if the given file exists.
     */
    bool exists(const std::string & filename);
}

namespace StringUtils{
    /**
     * @brief splitAtFirstOccurence Splits a string in two at the first occurence of a given character
     * @param s String to split
     * @param c Character at which to split
     * @return Two string instances if character was found, else a copy of the existing string.
     */
    std::vector<std::string> splitAtFirstOccurence(const std::string & s, char c);
    /**
     * @brief splitAtLastOccurence Splits a string in two at the last occurence of a given character
     * @param s String to split
     * @param c Character at which to split
     * @return Two string instances if character was found, else a copy of the existing string.
     */
    std::vector<std::string> splitAtLastOccurence(const std::string & s, char c);
    /**
     * @brief splitAtIndex Splits a string in 2 starting from the specified index
     * @param s String to split
     * @param index Index at which to split
     * @return Two string instances or one if index is equal to std::string::npos
     */
    std::vector<std::string> splitAtIndex(const std::string & s, int index);

    /**
     * @brief trim Trims the given string (removes leading and trailing white spaces)
     * @param input the string to trim
     * @return The trimmed string
     */
    std::string& trim(std::string & input);
    /**
     * @brief leftTrim Trims the leading spaces from the given string
     * @param input the string to trim
     * @return The trimmed string
     */
    std::string& leftTrim(std::string & input);
    /**
     * @brief rightTrim Trims the trailing spaces from the given string
     * @param input the string to trim
     * @return The trimmed string
     */
    std::string& rightTrim(std::string & input);
}

#endif // FILE_UTILS_H
