/**
*
* The Black Codex Library: Chapter: C++ Tools
*
* https://github.com/tbc-beren/BCppTools
*
* Mozilla Public License Version 2.0
* https://github.com/tbc-beren/BCppTools/blob/master/LICENSE
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* https://mozilla.org/MPL/2.0/.
*
*/
#pragma once

namespace bcpptools {
namespace math {

    template<typename T>
    class bcvector3_t
    {
    private:
        T mX, mY, mZ;

    public:
        bcvector3_t()
        {}
        bcvector3_t(T x, T y, T z)
        : mX(x)
        , mY(y)
        , mZ(z)
        {}

        T   getX() const {
            return mX;
        }
        T   getY() const {
            return mY;
        }
        T   getZ() const {
            return mZ;
        }
        bcvector3_t<T> operator+(const bcvector3_t<T>& src) {
            bcvector3_t<T> v(   mX + src.mX,
                                mY + src.mY,
                                mZ + src.mZ);
            return v;
        }
        bcvector3_t<T> operator-(const bcvector3_t<T>& src) {
            bcvector3_t<T> v(   mX - src.mX,
                                mY - src.mY,
                                mZ - src.mZ);
            return v;
        }
    };

    typedef bcvector3_t<float>      bcvector3f_t;
    typedef bcvector3_t<double>     bcvector3d_t;

} // namespace math
} // namespace bcpptools
