/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_IPFS_IPFS_ONBOARDING_PAGE_H_
#define BRAVE_COMPONENTS_IPFS_IPFS_ONBOARDING_PAGE_H_

#include <memory>
#include <string>

#include "base/memory/weak_ptr.h"
#include "base/values.h"
#include "components/security_interstitials/content/security_interstitial_page.h"
#include "url/gurl.h"

namespace content {
class WebContents;
}  // namespace content

namespace security_interstitials {
class SecurityInterstitialControllerClient;
}  // namespace security_interstitials

namespace ipfs {

class IpfsService;

// IPFSOnboardingPage is the interstitial page which will be shown when the
// browser tries to access IPFS contents if ASK mode is selected in settings.
class IPFSOnboardingPage
    : public security_interstitials::SecurityInterstitialPage {
 public:
  // Interstitial type, used in tests.
  static const security_interstitials::SecurityInterstitialPage::TypeID
      kTypeForTesting;

  // Commands from a page which means whether we launch a local node
  // or we should redirect user to a public gateway.
  enum IPFSOnboardingCommandId {
    USE_LOCAL_NODE = 0,
    USE_PUBLIC_GATEWAY = 1,
    LEARN_MORE = 2,
    OPEN_SETTINGS = 3,
  };

  // In case of an error when starting a local node, we notify a page.
  enum IPFSOnboardingResponse { LOCAL_NODE_ERROR = 0 };

  explicit IPFSOnboardingPage(
      IpfsService* ipfs_service,
      content::WebContents* web_contents,
      const GURL& request_url,
      std::unique_ptr<
          security_interstitials::SecurityInterstitialControllerClient>
          controller);
  ~IPFSOnboardingPage() override;

  IPFSOnboardingPage(const IPFSOnboardingPage&) = delete;
  IPFSOnboardingPage& operator=(const IPFSOnboardingPage&) = delete;

  // SecurityInterstitialPage::
  void OnInterstitialClosing() override {}
  void CommandReceived(const std::string& command) override;
  security_interstitials::SecurityInterstitialPage::TypeID GetTypeForTesting()
      override;
  void OnIpfsLaunched(bool result);
  void Proceed();

 protected:
  // SecurityInterstitialPage::
  void PopulateInterstitialStrings(
      base::DictionaryValue* load_time_data) override;
  int GetHTMLTemplateId() override;

 private:
  friend class IpfsNavigationThrottleBrowserTest;

  void RespondToPage(IPFSOnboardingResponse command);
  void UseLocalNode();
  void UsePublicGateway();

  IpfsService* ipfs_service_ = nullptr;
  base::WeakPtrFactory<IPFSOnboardingPage> weak_ptr_factory_{this};
};

}  // namespace ipfs

#endif  // BRAVE_COMPONENTS_IPFS_IPFS_ONBOARDING_PAGE_H_
