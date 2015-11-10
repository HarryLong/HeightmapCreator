#include "utils.h"
#include <fstream>
#include <algorithm>

bool FileUtils::exists(const std::string & filename)
{
    std::ifstream in(filename);
    bool good(in.good());
    in.close();

    return good;
}

// Splits at first occurence
std::vector<std::string> StringUtils::splitAtIndex(const std::string & s, int index)
{
    std::vector<std::string> ret;

    if(index != std::string::npos)
    {
        ret.push_back(s.substr(0,index));
        ret.push_back(s.substr(index+1));
    }
    else
        ret.push_back(s);

    return ret;
}

std::vector<std::string> StringUtils::splitAtFirstOccurence(const std::string & s, char c)
{
    return splitAtIndex(s, s.find_first_of(c));
}

std::vector<std::string> StringUtils::splitAtLastOccurence(const std::string & s, char c)
{
    return splitAtIndex(s, s.find_last_of(c));
}

std::string& StringUtils::trim(std::string & input)
{
    return leftTrim(rightTrim(input));
}

std::string& StringUtils::leftTrim(std::string & input)
{
    input.erase(input.begin(), std::find_if(input.begin(), input.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return input;
}

std::string& StringUtils::rightTrim(std::string & input)
{
    input.erase(std::find_if(input.rbegin(), input.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), input.end());
    return input;
}
