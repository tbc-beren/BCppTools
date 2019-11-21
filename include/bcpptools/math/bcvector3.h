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
#ifndef __bcpptools__math__vector3__
#define __bcpptools__math__vector3__

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


#endif //#ifndef __bcpptools__math__vector3__
