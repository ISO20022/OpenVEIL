//	Copyright (c) 2017, TecSec, Inc.
//
//	Redistribution and use in source and binary forms, with or without
//	modification, are permitted provided that the following conditions are met:
//	
//		* Redistributions of source code must retain the above copyright
//		  notice, this list of conditions and the following disclaimer.
//		* Redistributions in binary form must reproduce the above copyright
//		  notice, this list of conditions and the following disclaimer in the
//		  documentation and/or other materials provided with the distribution.
//		* Neither the name of TecSec nor the names of the contributors may be
//		  used to endorse or promote products derived from this software 
//		  without specific prior written permission.
//		 
//	ALTERNATIVELY, provided that this notice is retained in full, this product
//	may be distributed under the terms of the GNU General Public License (GPL),
//	in which case the provisions of the GPL apply INSTEAD OF those given above.
//		 
//	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//	DISCLAIMED.  IN NO EVENT SHALL TECSEC BE LIABLE FOR ANY 
//	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//	LOSS OF USE, DATA OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Written by Roger Butler

#include "stdafx.h"

#include "gtest/gtest.h"
#include <climits>
#include <sstream>
#include "Asn1CkmHeader.h"

static const char* TEST_HEADER1 = "30 82 02 61 06 06 2A 86 48 CE 4C 04 02 01 00 02 01 07 81 10 DE 5C AC 8A B1 E3 16 44 B9 72 AF 4E 91 3A 9D 08 18 0F 32 30 31 33 30 39 32 30 30 32 31 31 34 34 5A 30 0D 06 09 60 86 48 01 65 03 04 01 2E 05 00 A2 82 01 CD 30 6C 06 09 67 2A 09 0A 03 00 02 02 06 01 01 FF 04 5C 30 5A 30 58 04 10 D7 F7 F6 6C 84 C8 73 48 91 0D CD 0A D6 BF 21 13 02 01 00 04 41 04 D9 67 6A C7 93 87 78 C7 D4 55 53 24 2E BF 42 FF B1 74 72 75 1F A8 8B 63 0F 93 24 D2 E1 8F C3 74 C3 3B 55 B4 15 B2 89 52 6B 1F 25 BD BD AB 96 E8 E0 B8 9F E4 40 05 45 0E 32 3F 74 85 3B A7 FF 81 30 75 06 09 67 2A 09 0A 03 00 02 02 09 01 01 FF 04 65 30 63 30 61 04 10 AF 01 48 6C 4B 54 30 42 88 AB 7E 9F 36 F3 BA FE 02 01 00 02 01 00 04 47 30 45 02 21 00 B5 12 85 6B FA 70 4F 88 43 5A 90 53 1A 08 AE 40 B9 5B 98 43 80 B9 BC 92 FC FC B8 7B AE 7F 12 FE 02 20 2B 1B B2 27 B9 DC 66 4C 13 DA 23 A1 0B 47 40 44 DB B4 D5 57 E8 06 D9 6D 05 D4 9B E3 1B BD A3 0A 30 1D 06 09 67 2A 09 0A 03 00 02 02 08 04 10 D7 F7 F6 6C 84 C8 73 48 91 0D CD 0A D6 BF 21 13 30 43 06 09 67 2A 09 0A 03 00 02 02 07 01 01 FF 04 33 30 31 A3 2F 30 03 02 01 00 04 28 50 A7 36 34 A9 5A 65 A3 83 98 7E 74 CF 76 C0 46 80 A6 31 0D 18 68 05 44 E2 34 D9 F1 3D C6 69 27 AA 2A B9 5B EB 4C 7E BA 30 1E 06 09 67 2A 09 0A 03 00 02 02 0B 04 11 30 0F 06 09 67 2A 09 0A 03 00 07 01 02 02 02 01 00 30 15 06 09 67 2A 09 0A 03 00 02 02 03 04 08 FF FF FF FF FF FF FF FF 30 1C 06 09 67 2A 09 0A 03 00 02 02 01 01 01 FF 04 0C 8E 41 AB 11 7B 26 CA 98 56 7F 7E 8A 30 18 06 09 67 2A 09 0A 03 00 02 02 10 04 0B 30 09 02 03 4C 4B 40 02 02 20 02 30 13 06 09 67 2A 09 0A 03 00 02 02 05 04 06 4D 65 6D 6F 72 79 A3 0C 06 08 2A 86 48 86 F7 0D 02 0B 05 00 84 40 88 FE B3 A2 EC 3B F2 A1 86 88 1C 01 12 E0 B2 A6 50 21 05 14 A2 14 BA 4B F7 37 FB 06 39 7F DD 75 C2 B4 E4 10 FF A0 CF 62 E3 A1 3F 15 38 28 DC C1 E9 4D 15 20 8E D4 19 DE 02 66 B5 9A AD F8 63 23";
static const char* TEST_SIGNABLE1 = "30 82 02 1F 06 06 2A 86 48 CE 4C 04 02 01 00 02 01 07 81 10 DE 5C AC 8A B1 E3 16 44 B9 72 AF 4E 91 3A 9D 08 18 0F 32 30 31 33 30 39 32 30 30 32 31 31 34 34 5A 30 0D 06 09 60 86 48 01 65 03 04 01 2E 05 00 A2 82 01 CD 30 6C 06 09 67 2A 09 0A 03 00 02 02 06 01 01 FF 04 5C 30 5A 30 58 04 10 D7 F7 F6 6C 84 C8 73 48 91 0D CD 0A D6 BF 21 13 02 01 00 04 41 04 D9 67 6A C7 93 87 78 C7 D4 55 53 24 2E BF 42 FF B1 74 72 75 1F A8 8B 63 0F 93 24 D2 E1 8F C3 74 C3 3B 55 B4 15 B2 89 52 6B 1F 25 BD BD AB 96 E8 E0 B8 9F E4 40 05 45 0E 32 3F 74 85 3B A7 FF 81 30 75 06 09 67 2A 09 0A 03 00 02 02 09 01 01 FF 04 65 30 63 30 61 04 10 AF 01 48 6C 4B 54 30 42 88 AB 7E 9F 36 F3 BA FE 02 01 00 02 01 00 04 47 30 45 02 21 00 B5 12 85 6B FA 70 4F 88 43 5A 90 53 1A 08 AE 40 B9 5B 98 43 80 B9 BC 92 FC FC B8 7B AE 7F 12 FE 02 20 2B 1B B2 27 B9 DC 66 4C 13 DA 23 A1 0B 47 40 44 DB B4 D5 57 E8 06 D9 6D 05 D4 9B E3 1B BD A3 0A 30 1D 06 09 67 2A 09 0A 03 00 02 02 08 04 10 D7 F7 F6 6C 84 C8 73 48 91 0D CD 0A D6 BF 21 13 30 43 06 09 67 2A 09 0A 03 00 02 02 07 01 01 FF 04 33 30 31 A3 2F 30 03 02 01 00 04 28 50 A7 36 34 A9 5A 65 A3 83 98 7E 74 CF 76 C0 46 80 A6 31 0D 18 68 05 44 E2 34 D9 F1 3D C6 69 27 AA 2A B9 5B EB 4C 7E BA 30 1E 06 09 67 2A 09 0A 03 00 02 02 0B 04 11 30 0F 06 09 67 2A 09 0A 03 00 07 01 02 02 02 01 00 30 15 06 09 67 2A 09 0A 03 00 02 02 03 04 08 FF FF FF FF FF FF FF FF 30 1C 06 09 67 2A 09 0A 03 00 02 02 01 01 01 FF 04 0C 8E 41 AB 11 7B 26 CA 98 56 7F 7E 8A 30 18 06 09 67 2A 09 0A 03 00 02 02 10 04 0B 30 09 02 03 4C 4B 40 02 02 20 02 30 13 06 09 67 2A 09 0A 03 00 02 02 05 04 06 4D 65 6D 6F 72 79 A3 0C 06 08 2A 86 48 86 F7 0D 02 0B 05 00";
static const char* TEST_HEADER2 = "30 82 01 ec 06 06 2a 86 48 ce 4c 04 02 01 00 02 01 07 81 10 25 0f 4e 30 e1 cb 84 4e 86 45 d7 0a c4 78 d7 ee 18 0f 32 30 31 34 30 32 31 30 31 38 30 35 30 33 5a 02 01 65 a2 82 01 72 30 1d 06 09 67 2a 09 0a 03 00 02 02 08 04 10 ca b7 f4 e3 fa bb db 46 8e 2f f6 84 91 6c a6 c0 30 1e 06 09 67 2a 09 0a 03 00 02 02 0b 04 11 30 0f 06 09 67 2a 09 0a 03 00 07 01 01 02 02 02 00 30 6e 06 09 67 2a 09 0a 03 00 02 02 06 01 01 ff 04 5e 30 5c 30 5a 30 58 04 10 83 cb 7e dc b2 45 12 43 ba 2a a0 10 aa 3b 5b 54 02 01 00 04 41 04 fb e0 b2 a1 fc 9a 9c b8 7a 60 48 9f ab 37 60 19 42 67 bc e5 58 00 9b 1d ef bf 05 73 6d d6 5f ff 03 02 28 83 16 0d d0 ee 09 33 95 13 9f e7 e3 df 1a a7 40 a4 d3 18 5e 8e bd 78 4e 01 30 57 64 52 30 78 06 09 67 2a 09 0a 03 00 02 02 09 01 01 ff 04 68 30 66 30 64 30 62 04 10 ca b7 f4 e3 fa bb db 46 8e 2f f6 84 91 6c a6 c0 02 01 00 02 01 00 04 48 30 46 02 21 00 d8 c0 7f 5d 20 d0 48 d2 69 59 71 38 d6 85 84 e5 98 db c5 8e 46 1f a1 41 ac ae 20 a5 95 94 ec fd 02 21 00 95 4d 3a 22 9c 3a 24 34 24 44 ac e4 5b 6b fc 72 b8 82 46 69 69 96 13 0e dc 2c f2 e3 d4 c9 eb 90 30 47 06 09 67 2a 09 0a 03 00 02 02 07 01 01 ff 04 37 30 35 30 33 a3 31 30 05 a0 03 80 01 00 04 28 2d e6 c8 b8 e0 ac 04 45 80 ae a9 d1 36 df 6d 59 9f e2 62 09 e8 e0 83 00 63 ba ab ee df 1f 1a 71 55 35 ec 8b e4 00 2e bc 84 40 27 fb 97 2c c2 65 2d 87 ad 20 37 1d 72 ff 15 f4 20 f8 0e 4a a0 c6 7e 75 8d 13 ec 37 09 69 b9 0d 30 c3 04 55 eb 8e 6a 2b ce c7 ab ee 87 5a 4a 36 7d 6b 03 7a 87 7d 0a 89 01 ac 5a f6 04 91 09 75";

TEST(CkmHeaderDataTests, Decode_Encode_round_trip)
{
    Asn1::CMS::Ckm7HeaderData header;
    tsData output;

    EXPECT_EQ(true, header.Decode(tsData(TEST_HEADER1, tsData::HEX)));
    EXPECT_EQ(true, header.Encode(output));
    EXPECT_EQ(tsData(TEST_HEADER1, tsData::HEX), output);
}

TEST(CkmHeaderDataTests, Decode_Encode2_round_trip)
{
    Asn1::CMS::Ckm7HeaderData header;
    tsData output;

    EXPECT_EQ(true, header.Decode(tsData(TEST_HEADER2, tsData::HEX)));
    EXPECT_EQ(true, header.Encode(output));
    EXPECT_EQ(tsData(TEST_HEADER2, tsData::HEX), output);
}

TEST(CkmHeaderDataTests, Decode_part)
{
    Asn1::CMS::Ckm7HeaderData header;
    tsData output;

    EXPECT_EQ(true, header.Decode(tsData(TEST_HEADER1, tsData::HEX)));

    EXPECT_EQ(true, header.Encode_Signable(output));
    EXPECT_EQ(tsData(TEST_SIGNABLE1, tsData::HEX), output);

    //Asn1Test::TP_MiniHeader mh;
    //tsData output;

    //setupMiniHeader(mh);

    //EXPECT_EQ(true, mh.Encode(output));
    //EXPECT_EQ(tsData("30 81 FE 02 01 07 02 01 03 04 10 FD 0A 29 73 35 93 46 46 9F 96 55 CB 28 19 0C F7 18 0F 32 30 31 34 30 31 30 31 31 32 33 31 34 39 5A 80 2B 04 91 28 34 79 27 34 98 27 49 82 79 48 72 09 37 40 17 04 71 90 82 37 49 82 37 49 82 73 45 91 30 94 10 97 43 98 27 34 97 23 09 54 01 01 FF 01 01 00 02 02 02 00 04 34 B9 38 74 50 92 38 4A 75 09 23 74 59 02 37 45 92 73 45 97 23 F5 71 A9 23 47 59 03 81 74 59 B2 34 75 98 27 39 45 72 93 04 75 09 23 74 E5 97 34 9F 57 23 49 85 A2 66 30 64 A3 38 30 1F 04 10 29 7F 53 39 FF FE D3 4D 91 9C 08 68 FA BB B6 A6 02 01 59 80 08 30 06 02 01 00 02 01 00 30 15 04 10 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 02 01 00 04 28 54 78 94 39 78 34 57 85 43 78 95 43 89 74 53 78 45 38 79 54 37 89 45 38 97 54 37 89 45 32 78 54 87 94 58 97 89 75 49 54", tsData::HEX), output);

    //mh.clear();
    ////EXPECT_EQ(mh.Decode(output), true);
    ////EXPECT_EQ(true, checkMiniHeader(mh));
    //EXPECT_EQ(true, mh.Decode(tsData("30 81 FE 02 01 07 02 01 03 04 10 FD 0A 29 73 35 93 46 46 9F 96 55 CB 28 19 0C F7 18 0F 32 30 31 34 30 31 30 31 31 32 33 31 34 39 5A 80 2B 04 91 28 34 79 27 34 98 27 49 82 79 48 72 09 37 40 17 04 71 90 82 37 49 82 37 49 82 73 45 91 30 94 10 97 43 98 27 34 97 23 09 54 01 01 FF 01 01 00 02 02 02 00 04 34 B9 38 74 50 92 38 4A 75 09 23 74 59 02 37 45 92 73 45 97 23 F5 71 A9 23 47 59 03 81 74 59 B2 34 75 98 27 39 45 72 93 04 75 09 23 74 E5 97 34 9F 57 23 49 85 A2 66 30 64 A3 38 30 1F 04 10 29 7F 53 39 FF FE D3 4D 91 9C 08 68 FA BB B6 A6 02 01 59 80 08 30 06 02 01 00 02 01 00 30 15 04 10 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 02 01 00 04 28 54 78 94 39 78 34 57 85 43 78 95 43 89 74 53 78 45 38 79 54 37 89 45 38 97 54 37 89 45 32 78 54 87 94 58 97 89 75 49 54", tsData::HEX)));
    //EXPECT_EQ(true, checkMiniHeader(mh));
}

