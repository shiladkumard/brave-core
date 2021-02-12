/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/server/via_header_util.h"

#include "base/strings/stringprintf.h"
#include "bat/ads/internal/rpill/rpill.h"
#include "bat/ads/internal/user_activity/user_activity_scoring_util.h"

namespace ads {
namespace server {

namespace {

const int kVersion = 2;

enum Flags { kUncertainFuture = 1 << 0, kInactiveUser = 1 << 1 };

}  // namespace

std::string BuildViaHeader() {
  int flags = 0;

  if (IsUncertainFuture()) {
    flags |= kUncertainFuture;
  }

  if (!WasUserActive()) {
    flags |= kInactiveUser;
  }

  return base::StringPrintf(
      "Via: 1.%d brave, 1.1 ads-serve.brave.com (Apache/1.%d)", flags,
      kVersion);
}

}  // namespace server
}  // namespace ads
