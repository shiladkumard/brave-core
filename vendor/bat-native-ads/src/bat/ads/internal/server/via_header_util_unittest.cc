/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/server/via_header_util.h"

#include "base/strings/stringprintf.h"
#include "bat/ads/internal/unittest_base.h"
#include "bat/ads/internal/unittest_util.h"

// npm run test -- brave_unit_tests --filter=BatAds*

namespace ads {

namespace {

struct PermutationInfo {
  bool uncertain_future;
  bool inactive_user;
  int version;
};

const PermutationInfo kTests[] = {{false, false, 0},
                                  {false, true, 1},
                                  {true, false, 2},
                                  {true, true, 3}};

}  // namespace

class BatAdsViaHeaderUtilTest
    : public UnitTestBase,
      public ::testing::WithParamInterface<PermutationInfo> {
 protected:
  BatAdsViaHeaderUtilTest() = default;

  ~BatAdsViaHeaderUtilTest() override = default;
};

TEST_P(BatAdsViaHeaderUtilTest, BuildViaHeader) {
  // Arrange

  const PermutationInfo info = GetParam();

  if (info.uncertain_future) {
    SysInfo sys_info;
    sys_info.manufacturer = "VMWare";
    sys_info.model = "Virtual Platform";
    SetSysInfo(sys_info);
  }

  if (!info.inactive_user) {
    UserActivity::Get()->RecordEvent(UserActivityEventType::kOpenedNewTab);
  }

  // Act
  const std::string via_header = server::BuildViaHeader();

  // Assert
  const std::string expect_via_header = base::StringPrintf(
      "Via: 1.%d brave, 1.1 ads-serve.brave.com (Apache/1.2)", info.version);

  EXPECT_EQ(expect_via_header, via_header);
}

static std::string GetTestCaseName(
    ::testing::TestParamInfo<PermutationInfo> info) {
  const std::string uncertain_future =
      info.param.uncertain_future ? "UncertainFuture" : "";

  const std::string inactive_user =
      info.param.inactive_user ? "InactiveUser" : "";

  return base::StringPrintf("For%s%s", uncertain_future.c_str(),
                            inactive_user.c_str());
}

INSTANTIATE_TEST_SUITE_P(BuildViaHeaders,
                         BatAdsViaHeaderUtilTest,
                         ::testing::ValuesIn(kTests),
                         GetTestCaseName);

}  // namespace ads
