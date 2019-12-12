/**
*
* The Black Codex Library: Chapter: C++ Tools
*
* https://github.com/tbc-beren/BCppTools
*
* Mozilla Public License Version 2.0
* https://github.com/tbc-beren/BCppTools/blob/master/LICENSE
*
*/
#ifndef __bcpptools__math__prime__
#define __bcpptools__math__prime__

namespace bcpptools {
namespace math {

class bcprime
{
public:
    template<typename TNumber>
    static
    bool isPrime(TNumber t) {
        if (2 == t ) {
            return true;
        }
        if (t     == 1 ||
            t % 2 == 0) {
            return false;
        }

        const TNumber MAXDIV = (t/2);
        for (TNumber x=3; x<MAXDIV; x+=2) {
            if (t%x == 0) {
                return false;
            }
        }

        return true;
    }
};

} // namespace math
} // namespace bcpptools


#endif //#ifndef __bcpptools__math__prime__
