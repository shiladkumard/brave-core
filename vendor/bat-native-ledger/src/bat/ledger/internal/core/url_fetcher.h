/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_LEDGER_CORE_URL_FETCHER_H_
#define BAT_LEDGER_CORE_URL_FETCHER_H_

#include "bat/ledger/internal/core/async_result.h"
#include "bat/ledger/internal/core/bat_ledger_context.h"
#include "bat/ledger/public/interfaces/ledger.mojom.h"

namespace ledger {

class URLFetcher : public BATLedgerContext::Component {
 public:
  static const BATLedgerContext::ComponentKey kComponentKey;

  struct FetchOptions {
    bool log_response_body = false;
    bool disable_logging = false;
  };

  using FetchResult = AsyncResult<mojom::UrlResponsePtr>;
  FetchResult Fetch(mojom::UrlRequestPtr request);
  FetchResult Fetch(mojom::UrlRequestPtr request, FetchOptions options);

 private:
  friend class BATLedgerContext;

  explicit URLFetcher(BATLedgerContext* context);

  virtual FetchResult FetchImpl(mojom::UrlRequestPtr request,
                                FetchOptions options);

  void LogURLRequest(const mojom::UrlRequest& request, FetchOptions options);
  void LogURLResponse(const mojom::UrlResponse& response, FetchOptions options);
  void LogURLResponseDetails(const mojom::UrlResponse& response,
                             FetchOptions options);
};

}  // namespace ledger

#endif  // BAT_LEDGER_CORE_URL_FETCHER_H_
