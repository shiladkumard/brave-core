/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_BROWSER_SPEEDREADER_SPEEDREADER_TAB_HELPER_H_
#define BRAVE_BROWSER_SPEEDREADER_SPEEDREADER_TAB_HELPER_H_

#include "components/dom_distiller/content/browser/distillable_page_utils.h"
#include "content/public/browser/navigation_details.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

namespace content {
class NavigationHandle;
class WebContents;
}  // namespace content

namespace speedreader {

// Determines if speedreader should be active for a given top-level navigation.
class SpeedreaderTabHelper
    : public dom_distiller::DistillabilityObserver,
      public content::WebContentsObserver,
      public content::WebContentsUserData<SpeedreaderTabHelper> {
 public:
  ~SpeedreaderTabHelper() override;

  SpeedreaderTabHelper(const SpeedreaderTabHelper&) = delete;
  SpeedreaderTabHelper& operator=(SpeedreaderTabHelper&) = delete;

  bool IsActiveForMainFrame() const { return speedreader_active_; }
  bool IsDistilled() const;

 private:
  friend class content::WebContentsUserData<SpeedreaderTabHelper>;
  explicit SpeedreaderTabHelper(content::WebContents* web_contents);

  void UpdateActiveState(content::NavigationHandle* handle);

  // content::WebContentsObserver
  void WebContentsDestroyed() override;
  void DidStartNavigation(
      content::NavigationHandle* navigation_handle) override;
  void DidRedirectNavigation(
      content::NavigationHandle* navigation_handle) override;
  void NavigationEntryCommitted(
      const content::LoadCommittedDetails& load_details) override;

  // dom_distiller::DistillabilityObserver overrides:
  void OnResult(const dom_distiller::DistillabilityResult& result) override;

  bool speedreader_active_ = false;

  WEB_CONTENTS_USER_DATA_KEY_DECL();
};

}  // namespace speedreader

#endif  // BRAVE_BROWSER_SPEEDREADER_SPEEDREADER_TAB_HELPER_H_
