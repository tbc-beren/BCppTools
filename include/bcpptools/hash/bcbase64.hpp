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

#include <algorithm>
#include <cstdint>
#include <string>

namespace bcpptools {
namespace hash {

    class BCBase64
    {
    private:
        std::string mHash;

    public:
        static void fromURL(std::string& base64url) {
            std::replace(base64url.begin(), base64url.end(), '-', '+');
            std::replace(base64url.begin(), base64url.end(), '_', '/');
            auto extra = base64url.size() % 4;
            while(0 != extra--) {
                base64url.push_back('=');
            }
        }
        static void toURL(std::string& base64url) {
            std::replace(base64url.begin(), base64url.end(), '+', '-');
            std::replace(base64url.begin(), base64url.end(), '/', '_');
            while(0 < base64url.size() &&
                  base64url.back() == '=') {
                base64url.pop_back();
            }
        }
        static std::string encodeAll(const std::string& input) {
            BCBase64 me;
            me.encode(input);
            return me.hash();
        }

        void clear() {
            mHash.clear();
        }
        void encode(const std::string& data) {
            encode(castChar(data.c_str()), data.size());
        }
        bool decode(const std::string& data) {
            return decode(castChar(data.c_str()), data.size());
        }
        const std::string& hash() const {
            return mHash;
        }
        void encode(const uint8_t* buffer, size_t size) {
            uint8_t tmp[3];
            char     out[5];

            out[4] = 0;

            while(size > 0) {
                int off = 0;
                while (size > 0 && off < 3) {
                    tmp[off++]=*buffer++;
                    --size;
                }

                out[0] = (tmp[0] & 0xFC) >> 2;
                out[1] = (tmp[0] & 0x03) << 4;
                out[2] = 64;
                out[3] = 64;

                if (off > 1) {
                    out[1] |= (tmp[1] & 0xF0) >> 4;
                    out[2] =  (tmp[1] & 0x0F) << 2;
                }

                if (off > 2) {
                    out[2] |= (tmp[2] & 0xC0) >> 6;
                    out[3] = (tmp[2] & 0x3F);
                }

                out[0] = charToHash(out[0]);
                out[1] = charToHash(out[1]);
                out[2] = charToHash(out[2]);
                out[3] = charToHash(out[3]);

                mHash.append(out);
            }
        }
        bool decode(const uint8_t* buffer, size_t size) {
            uint8_t tmp[5];
            char    out[4];

            if (size%4 != 0) {
                return false;
            }

            out[3]=0;

            while(size > 0) {
                int off = 0;
                while (size > 0 && off < 4) {
                    char chr = *buffer++;
                    char val = chr == '='? 0 : charHash(chr);
                    if (val == -1) {
                        return false;
                    }
                    tmp[off++]=val;
                    --size;
                }

                out[0] = ((tmp[0] & 0x3F) << 2) | ((tmp[1] & 0x30)>>4);
                out[1] = ((tmp[1] & 0x0F) << 4) | ((tmp[2] & 0x3C)>>2);
                out[2] = ((tmp[2] & 0x03) << 6) | tmp[3];

                this->mHash.append(out);
            }

            return true;
        }
    private:
        const uint8_t* castChar(const char* data) {
            return reinterpret_cast<const uint8_t*>(data);
        }
        static const std::string& hashTranslateTable() {
            static const std::string hashTable = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
            return hashTable;
        }
        static char charHash(char v) {
            const auto& hashTable = hashTranslateTable();
            auto pos = hashTable.find_first_of(v);
            if (hashTable.npos == pos) {
                return -1;
            }
            return pos & 0xFF;
        }
        static char charToHash(uint8_t chr) {
            return hashTranslateTable().at(chr);
        }
    };

} // namespace hash
} // namespace bcpptools
