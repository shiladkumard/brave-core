/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/security/security_util.h"

#include "base/base64.h"
// TODO(Moritz Haller): Or access via security::?
#include "bat/ads/internal/security/conversion_id_info.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- brave_unit_tests --filter=BatAds*

namespace ads {
namespace security {

const char kAlgorithm[] = "x25519-xsalsa20-poly1305";

TEST(BatAdsSecurityUtilsTest, Sign) {
  // Arrange
  const std::map<std::string, std::string> headers = {
      {"digest", "SHA-256=qj7EBzMRSsGh4Rfu8Zha6MvPB2WftfJNeF8gt7hE9AY="}};

  const std::string key_id = "primary";

  const std::string secret_key =
      "e9b1ab4f44d39eb04323411eed0b5a2ceedff01264474f86e29c707a56615650"
      "33cea0085cfd551faa170c1dd7f6daaa903cdd3138d61ed5ab2845e224d58144";

  // Act
  const std::string signature = security::Sign(headers, key_id, secret_key);

  // Assert
  const std::string expected_signature =
      R"(keyId="primary",algorithm="ed25519",headers="digest",signature="m5CxS9uqI7DbZ5UDo51bcLRP2awqcUSU8tfc4t/ysrH47B8OJUG1roQyi6/pjSZj9VJuj296v77c/lxBlCn2DA==")";

  EXPECT_EQ(expected_signature, signature);
}

TEST(BatAdsSecurityUtilsTest, SignWithInvalidheaders) {
  // Arrange
  const std::map<std::string, std::string> headers = {};

  const std::string key_id = "primary";

  const std::string secret_key =
      "e9b1ab4f44d39eb04323411eed0b5a2ceedff01264474f86e29c707a56615650"
      "33cea0085cfd551faa170c1dd7f6daaa903cdd3138d61ed5ab2845e224d58144";

  // Act
  const std::string signature = security::Sign(headers, key_id, secret_key);

  // Assert
  const std::string expected_signature = "";

  EXPECT_EQ(expected_signature, signature);
}

TEST(BatAdsSecurityUtilsTest, SignWithInvalidKeyId) {
  // Arrange
  const std::map<std::string, std::string> headers = {
      {"digest", "SHA-256=qj7EBzMRSsGh4Rfu8Zha6MvPB2WftfJNeF8gt7hE9AY="}};

  const std::string key_id = "";

  const std::string secret_key =
      "e9b1ab4f44d39eb04323411eed0b5a2ceedff01264474f86e29c707a56615650"
      "33cea0085cfd551faa170c1dd7f6daaa903cdd3138d61ed5ab2845e224d58144";

  // Act
  const std::string signature = security::Sign(headers, key_id, secret_key);

  // Assert
  const std::string expected_signature = "";

  EXPECT_EQ(expected_signature, signature);
}

TEST(BatAdsSecurityUtilsTest, SignWithInvalidSecretKey) {
  // Arrange
  const std::map<std::string, std::string> headers = {
      {"digest", "SHA-256=qj7EBzMRSsGh4Rfu8Zha6MvPB2WftfJNeF8gt7hE9AY="}};

  const std::string key_id = "primary";

  const std::string secret_key = "";

  // Act
  const std::string signature = security::Sign(headers, key_id, secret_key);

  // Assert
  const std::string expected_signature = "";

  EXPECT_EQ(expected_signature, signature);
}

TEST(BatAdsSecurityUtilsTest, Sha256) {
  // Arrange
  const std::string body = R"(
    {
      "blindedTokens" : [
        "iiafV6PGoG+Xz6QR+k1WaYllcA+w0a1jcDqhbpFbvWw=",
        "8g7v9CDoZuOjnABr8SYUJmCIRHlwkFpFBB6rLfEJlz0=",
        "chNIADY97/IiLfWrE/P5T3p3SQIPZAc4fKkB8/4byHE=",
        "4nW47xQoQB4+uEz3i6/sbb+FDozpdiOTG53E+4RJ9kI=",
        "KO9qa7ZuGosA2xjM2+t3rn7/7Oljga6Ak1fgixjtp2U=",
        "tIBcIB2Xvmx0S+2jwcYrnzPvf20GTconlWDSiWHqR3g=",
        "aHtan+UcZF0II/SRoYm7bK27VJWDabNKjXKSVaoPPTY=",
        "6jggPJK8NL1AedlRpJSrCC3+reG2BMGqHOmIPtAsmwA=",
        "7ClK9P723ff+dOZxOZ0jSonmI5AHqsQU2Cn8FVAHID4=",
        "zkm+vIFM0ko74m+XhnZirCh7YUc9ucDtQTC+kwhWvzQ=",
        "+uoLhdsMEg42PRYiLs0lrAiGcmsPWX2D6hxmrcLUgC8=",
        "GNE2ISRb52HSPq0maJ9YXmbbkzUpo5dSNIM9I1eD+F4=",
        "iBx49OAb3LWQzKko8ZeVVAkwdSKRbDHViqR6ciBICCw=",
        "IBC208b0z56kzjG2Z/iTwriZfMp2cqoQgk4vyJAKJy8=",
        "Vq4l6jx8vSCmvTVFMg3Wz04Xz/oomFq4QRt26vRhDWg=",
        "5KIAJPFrSrVW92FJXP7WmHLc7d5a4lfTrXTRKC9rYQg=",
        "/s/SELS2gTDt1Rt7XaJ54RaGLQUL85cLpKW2mBLU2HU=",
        "HkJpt3NbymO56XbB2Tj4S4xyIKSjltFTjn1QdC1rLnM=",
        "/CQIGwgHAX2kFmaJ+65YtAbO4eSfUvMojVxZLq/p/AE=",
        "8N33oYwImtxf9rbrAQ1v8VlRD4iHDVR11yhYCKKKGFs=",
        "6EjTK0lYDGwFPrtMyTjiYIPV4OK7beMBTV6qrgFCwDw=",
        "5LzZynN+sxbIfQKc92V3dC82x4e99oxChk7fFNvJHmM=",
        "uEW1D0SU8VU5UGPOnkrCv3I+NFNa1fNPSjDy4gjvIm0=",
        "aIEvt2dBwTp1vuxNYjLaP25YdV3FjCG23NDxZG+MXxg=",
        "DIhrKTcba0NNoEKQAsSb1t9R3KVrkwX8fpLlOOLcMkI=",
        "vNaRbm7RPEkFvNNdLKaNhyd7gkM+kNt23G0N4sLnLhU=",
        "4MXZ/1hM6+xVzyYWY14tjIxCaisfrTgAUD3LLJHSd14=",
        "6hsMVd3VIjKUhHmHQRQRKr7duSiKzL36b/J+Mc4DPHM=",
        "OCe1Vv0l86izNn1PHw+yLw5e37J/Ab3oVyTPgFlS4Wc=",
        "hu5fi5YMxsWfmK3uTspjcjwguBDeiYMGuV+vIzC8jlg=",
        "Vs+EZRjtF+xUC3sYUZsvpND8ugLPz6Yl0jCcv4HO2Co=",
        "7Pxgek1VUU+93o6PWUdKgQW7IkDmLsotSEg8H7xj93U=",
        "avRL8coOl6cWJxKlvY9mHfw1FWIF14JnhNdxW00fqAM=",
        "Vvo4hscwrZgOIuwkgUaxzyrcGQbUS1vCWcNgjEkhfUg=",
        "ChsgA1m1hmWFt3r6xQqNCZVqx/tMMzEdpy++uccB3Cs=",
        "MImbGYf4TyE9WW/jx381Spk0B9boASAyehwz1om9Ong=",
        "ksPN5jCF2uN8d1io+xXVJhJXZs/DpQsPsoCZl8L9EgA=",
        "4AApGEJLMC3rgYgUABQp9nTXeikDmS29a2wkUOXIQXU=",
        "JOcObac9kXq8eD0aIU5S5DKWiA/Ggf4tBC58KD2xtRs=",
        "CBHMKoOwelZhfmupH1bH5Yo6BxDSkT8G2Jfk4xKsgyU=",
        "Al/1AAI4W68MEk6+Ay0xIGjxzvlX6IdnPV9KgO1RU0c=",
        "MtKvUJzIOOvOw8y+XzBbUrgyPxvE/DID2qvB3VsmVEs=",
        "oIaCqLv0kIG9BDZz5u0xj0/ZQqZQMCn7gkgIHVioSFc=",
        "8N1j1xiNm8dY90J9HQaeKyG861i2AN0w9nkF4cieZzw=",
        "wDMa7tUhloYanmLOivcgHyjCLr/OMaKtWdqbhadEmRM=",
        "bCquxc5v8J/P2pqay5fpzcLkTqSVvwdZrAbbIOF8Lhs=",
        "ODPBJiCcOMv48YS9QIcD0dH4bsfD2zQVsWkwBef1ci4=",
        "eA9Yt1HOkDNvDT6+kq0093d7WI/L78/Gj9nAlmSYwzE=",
        "wqt3REJpnoxOCSdHcJEiOsdBWb5yQD5jaTahFz40Tkc=",
        "tLdemf03DyE7OkTS8QCZS8OT0JflCVO1CmCbA8i2SXI="
      ]
    }
  )";

  // Act
  const std::vector<uint8_t> sha256 = security::Sha256Hash(body);
  const std::string sha256_base64 = base::Base64Encode(sha256);

  // Assert
  const std::string expected_sha256_base64 =
      "CLhef3V+rztnAAf7WyUhoyfhRbD2MXKhgtpzivvJJC0=";

  EXPECT_EQ(expected_sha256_base64, sha256_base64);
}

TEST(BatAdsSecurityUtilsTest, Sha256WithEmptyString) {
  // Arrange
  const std::string body = "";

  // Act
  const std::vector<uint8_t> sha256 = security::Sha256Hash(body);

  // Assert
  EXPECT_TRUE(sha256.empty());
}

TEST(BatAdsSecurityUtilsTest, ConversionEnvelopeAlgorithm) {
  // Arrange
  const std::string advertiser_pk_base64 =
      "ofIveUY/bM7qlL9eIkAv/xbjDItFs1xRTTYKRZZsPHI=";
  const std::string advertiser_sk_base64 =
      "Ete7+aKfrX25gt0eN4kBV1LqeF9YmB1go8OqnGXUGG4=";
  const std::string message = "smartbrownfoxes16";

  // Act
  ConversionIdInfo conversion_id_info =
      EncryptAndEncodeConversionId(message, advertiser_pk_base64);

  // Assert
  EXPECT_EQ(conversion_id_info.algorithm, kAlgorithm);
}

TEST(BatAdsSecurityUtilsTest, ConversionEnvelopeWithShortMessage) {
  // Arrange
  const std::string advertiser_pk_base64 =
      "ofIveUY/bM7qlL9eIkAv/xbjDItFs1xRTTYKRZZsPHI=";
  const std::string advertiser_sk_base64 =
      "Ete7+aKfrX25gt0eN4kBV1LqeF9YmB1go8OqnGXUGG4=";
  const std::string message = "shortmessage";

  // Act
  ConversionIdInfo conversion_id_info =
      EncryptAndEncodeConversionId(message, advertiser_pk_base64);
  std::string result =
      DecodeAndDecryptConversionId(conversion_id_info, advertiser_sk_base64);

  // Assert
  EXPECT_TRUE(result.empty());
}

TEST(BatAdsSecurityUtilsTest, ConversionEnvelopeWithLongMessage) {
  // Arrange
  const std::string advertiser_pk_base64 =
      "ofIveUY/bM7qlL9eIkAv/xbjDItFs1xRTTYKRZZsPHI=";
  const std::string advertiser_sk_base64 =
      "Ete7+aKfrX25gt0eN4kBV1LqeF9YmB1go8OqnGXUGG4=";
  const std::string message = "thismessageistoolongthismessageistoolong";

  // Act
  ConversionIdInfo conversion_id_info =
      EncryptAndEncodeConversionId(message, advertiser_pk_base64);
  std::string result =
      DecodeAndDecryptConversionId(conversion_id_info, advertiser_sk_base64);

  // Assert
  EXPECT_TRUE(result.empty());
}

TEST(BatAdsSecurityUtilsTest, ConversionEnvelopeWithInvalidMessage) {
  // Arrange
  const std::string advertiser_pk_base64 =
      "ofIveUY/bM7qlL9eIkAv/xbjDItFs1xRTTYKRZZsPHI=";
  const std::string advertiser_sk_base64 =
      "Ete7+aKfrX25gt0eN4kBV1LqeF9YmB1go8OqnGXUGG4=";
  const std::string message = "smart brown foxes 16";

  // Act
  ConversionIdInfo conversion_id_info =
      EncryptAndEncodeConversionId(message, advertiser_pk_base64);
  std::string result =
      DecodeAndDecryptConversionId(conversion_id_info, advertiser_sk_base64);

  // Assert
  EXPECT_TRUE(result.empty());
}

TEST(BatAdsSecurityUtilsTest, ConversionEnvelopeWithInvalidPublicKey) {
  // Arrange
  const std::string message = "smartbrownfoxes42";
  const std::string advertiser_pk_base64 =
      "ofIveUY/bM7qlL9eIkAv/xbjDItFs1xRTTYKRZZsPHI@";
  const std::string advertiser_sk_base64 =
      "Ete7+aKfrX25gt0eN4kBV1LqeF9YmB1go8OqnGXUGG4=";

  // Act
  ConversionIdInfo envelope =
      EncryptAndEncodeConversionId(message, advertiser_pk_base64);
  std::string result =
      DecodeAndDecryptConversionId(envelope, advertiser_sk_base64);

  // Assert
  EXPECT_TRUE(result.empty());
}

TEST(BatAdsSecurityUtilsTest, ConversionEnvelope) {
  // Arrange
  const std::string message = "smartbrownfoxes42";
  const std::string advertiser_pk_base64 =
      "ofIveUY/bM7qlL9eIkAv/xbjDItFs1xRTTYKRZZsPHI=";
  const std::string advertiser_sk_base64 =
      "Ete7+aKfrX25gt0eN4kBV1LqeF9YmB1go8OqnGXUGG4=";

  // Act
  ConversionIdInfo envelope =
      EncryptAndEncodeConversionId(message, advertiser_pk_base64);
  std::string result =
      DecodeAndDecryptConversionId(envelope, advertiser_sk_base64);

  // Assert
  EXPECT_EQ(message, result);
}

}  // namespace security
}  // namespace ads
