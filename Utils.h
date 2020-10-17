#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>
#include <cstdlib>
#include <iterator>

class Tokenizer {
public:
    Tokenizer(std::string delim = "= :") :delimiters(delim)
    {
    };

    /*
    * Extract key value from string that separates key and value by delimiters
    * Example: RawMaterial = 100
    *          key=RawMaterial => val=100
    */
    void getKeyVal(std::istream& inStr, std::string& key, int& val)
    {
        std::istreambuf_iterator<char> itr(inStr), end;
        if (itr != end)
        {
            // Get key
            std::insert_iterator<std::string> iiKey(key, key.begin());
            while (isDelimiter(*itr) && (itr != end))
            {
                itr++;
            }
            while (!isDelimiter(*itr) && (itr != end))
            {
                *iiKey++ = *itr++;
            }

            // Get value from remaining string
            std::string value;
            std::insert_iterator<std::string> iiVal(value, value.begin());
            while (isDelimiter(*itr) && (itr != end))
            {
                itr++;
            }
            while (!isDelimiter(*itr) && (itr != end))
            {
                *iiVal++ = *itr++;
            }
            val = atoi(value.c_str());
        }
    }

private:
    std::string delimiters;
    bool isDelimiter(char c)
    {
        return (delimiters.find(c) != std::string::npos);
    }
};
#endif //_UTILS_H_
