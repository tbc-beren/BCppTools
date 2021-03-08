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

#include <bcpptools/core/bctypes.h>

#include <cstdint>

namespace bcpptools {
namespace multimedia {
namespace image {

    class bccolor_t
    {
    private:
        bcpixel_t   m_pixel;

        static uint8_t  _low_byte(uint32_t value)  {   return (value & 0xFF);      }

    public:
        bccolor_t()
            : m_pixel(0)
        {}

        bccolor_t(const bcpixel_t   pixel)
            : m_pixel(pixel)
        {}

        bccolor_t(const uint8_t r, const uint8_t g, const uint8_t b)
            : m_pixel( bccolor_t::build_pixel(r, g, b) )
        { }

        bccolor_t(const uint8_t a, const uint8_t r, const uint8_t g, const uint8_t b)
            : m_pixel( bccolor_t::build_pixel(a, r, g, b) )
        { }

        static const bcpixel_t WHITE = 0xFFFFFFFF;
        static const bcpixel_t RED   = 0xFF0000FF;
        static const bcpixel_t GREEN = 0xFF00FF00;
        static const bcpixel_t BLUE  = 0xFFFF0000;

        static bcpixel_t build_pixel(const uint8_t r, const uint8_t g, const uint8_t b) {
            return ((bcpixel_t)
                ((r&0xFF)    )|
                ((g&0xFF)<< 8)|
                ((b&0xFF)<<16));
        }
        static bcpixel_t build_pixel(const uint8_t a, const uint8_t r, const uint8_t g, const uint8_t b) {
            return ((a&0xFF)<<24) | bccolor_t::build_pixel(r, g, b);
        }
        static uint8_t      get_alpha(bcpixel_t pixel)                                                          {   return bccolor_t::_low_byte(pixel >> 24);                                                               }
        static uint8_t      get_red(bcpixel_t pixel)                                                            {   return bccolor_t::_low_byte(pixel);                                                                     }
        static uint8_t      get_green(bcpixel_t pixel)                                                          {   return bccolor_t::_low_byte(pixel >> 8);                                                                }
        static uint8_t      get_blue(bcpixel_t pixel)                                                           {   return bccolor_t::_low_byte(pixel >> 16);                                                               }

        void                rgb(const uint8_t r, const uint8_t g, const uint8_t b)                                   {   this->m_pixel = bccolor_t::build_pixel(r, g, b);                                                        }
        void                argb(const uint8_t a, const uint8_t r, const uint8_t g, const uint8_t b)                {   this->m_pixel = bccolor_t::build_pixel(a, r, g,                     b);                                                     }

        bcpixel_t           get(void) const     {   return this->m_pixel;                                                                                               }
        uint8_t             get_a(void) const   {   return bccolor_t::get_alpha(this->m_pixel);                                                                        }
        uint8_t             get_r(void) const   {   return bccolor_t::get_red(this->m_pixel);                                                               }
        uint8_t             get_g(void) const   {   return bccolor_t::get_green(this->m_pixel);                                                             }
        uint8_t             get_b(void) const   {   return bccolor_t::get_blue(this->m_pixel);                                                              }

        void get_rgb(uint8_t& r, uint8_t& g, uint8_t& b) const {
            r = this->get_r();
            g = this->get_g();
            b = this->get_b();
        }

        bcpixel_t get_abgr(void) const {
            bccolor_t px(this->get_a(),
                         this->get_b(),
                         this->get_g(),
                         this->get_r());

            return px.get();
        }

        uint8_t get_luma() {
            return (this->get_r()+this->get_g()+this->get_b())/3;
        }
    };

} // namespace image
} // namespace multimedia
} // namespace bcpptools
