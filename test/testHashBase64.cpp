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
#include <bcpptools/hash/bcbase64.hpp>

#include <gtest/gtest.h>

#include <string>
#include <vector>

TEST(Base64, decodeInvalidLen) {
    using namespace bcpptools::hash;
    EXPECT_FALSE(BCBase64().decode("X"));
    EXPECT_FALSE(BCBase64().decode("XX"));
    EXPECT_FALSE(BCBase64().decode("XXX"));
    EXPECT_TRUE (BCBase64().decode("XXXX"));
    EXPECT_FALSE(BCBase64().decode("XXXXX"));
}
TEST(Base64, decodeInvalidChar) {
    using namespace bcpptools::hash;
    EXPECT_FALSE(BCBase64().decode("----"));
}
TEST(Base64, encodeAndDecode) {
    std::vector<std::pair<std::string, std::string>> testEntries = {
        {"\370\017\301",        "+A/B"},
        {"x",                   "eA=="},
        {"Message-Hash",        "TWVzc2FnZS1IYXNo"},
        {"MessageToHash",       "TWVzc2FnZVRvSGFzaA=="},
        {"MessageForHashing",   "TWVzc2FnZUZvckhhc2hpbmc="},
    };

    for (const auto& item: testEntries) {
        bcpptools::hash::BCBase64 b64;
        b64.encode(item.first);

        const std::string output = b64.hash();
        EXPECT_EQ(item.second, output);

        b64.clear();
        b64.decode(output);
        EXPECT_EQ(item.first, b64.hash());
    }
}
TEST(Base64, encodeAndDecodeURL) {
    using namespace bcpptools::hash;

    BCBase64 b;
    b.decode("+===");
    std::string out = b.hash();

    uint8_t txt[5];
    txt[0] = out[0];
    txt[1] = out[1];
    txt[2] = out[2];
    txt[3] = out[3];
    txt[4] = 0;

    (void)txt;

    std::vector<std::pair<std::string, std::string>> testEntries = {
        {"1",                   "MQ"},
        {"12",                  "MTI"},
        {"123",                 "MTIz"},
        {"\370\017\301",        "-A_B"},
        {"x",                   "eA"},
    };

    for (const auto& item: testEntries) {
        const std::string encodedB64 = BCBase64::encodeAll(item.first);

        std::string output(encodedB64);
        BCBase64::toURL(output);
        EXPECT_EQ(item.second, output);

        BCBase64::fromURL(output);
        EXPECT_EQ(encodedB64, output);

        BCBase64 b64;
        b64.decode(output);
        EXPECT_EQ(item.first, b64.hash());
    }
}
