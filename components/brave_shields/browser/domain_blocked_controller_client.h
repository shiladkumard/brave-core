/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_SHIELDS_BROWSER_DOMAIN_BLOCKED_CONTROLLER_CLIENT_H_
#define BRAVE_COMPONENTS_BRAVE_SHIELDS_BROWSER_DOMAIN_BLOCKED_CONTROLLER_CLIENT_H_

#include <memory>
#include <string>

#include "components/security_interstitials/content/security_interstitial_controller_client.h"
#include "url/gurl.h"

namespace content {
class WebContents;
}  // namespace content

namespace security_interstitials {
class MetricsHelper;
}  // namespace security_interstitials

namespace brave_shields {

class AdBlockCustomFiltersService;

class DomainBlockedControllerClient
    : public security_interstitials::SecurityInterstitialControllerClient {
 public:
  static std::unique_ptr<security_interstitials::MetricsHelper>
  GetMetricsHelper(const GURL& url);

  DomainBlockedControllerClient(
      content::WebContents* web_contents,
      const GURL& request_url,
      AdBlockCustomFiltersService* ad_block_custom_filters_service,
      PrefService* prefs,
      const std::string& locale);
  ~DomainBlockedControllerClient() override = default;

  DomainBlockedControllerClient(const DomainBlockedControllerClient&) = delete;
  DomainBlockedControllerClient& operator=(
      const DomainBlockedControllerClient&) = delete;

  void SetDontWarnAgain(bool value);

  // security_interstitials::SecurityInterstitialControllerClient:
  void GoBack() override;
  void Proceed() override;

 private:
  const GURL request_url_;
  AdBlockCustomFiltersService* ad_block_custom_filters_service_;
  bool dont_warn_again_;
};

}  // namespace brave_shields

#endif  // BRAVE_COMPONENTS_BRAVE_SHIELDS_BROWSER_DOMAIN_BLOCKED_CONTROLLER_CLIENT_H_
