/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/rpill/common/rpill.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "base/barrier_closure.h"
#include "base/callback.h"
#include "base/callback_helpers.h"
#include "base/strings/string_util.h"
#include "base/system/sys_info.h"
#include "base/threading/scoped_blocking_call.h"

namespace brave_rpill {

namespace {

struct DeviceNameInfo {
  std::string manufacturer_name;
  std::string model_name;
};

std::string BuildDeviceId(DeviceNameInfo* info) {
  return base::ToLowerASCII(info->manufacturer_name + info->model_name);
}

bool IsUncertainFuture(DeviceNameInfo* info) {
  const std::string device_id = BuildDeviceId(info);

  const std::vector<std::string> keywords = {"amazon", "virtualbox", "vmware",
                                             "xen"};

  for (const auto& keyword : keywords) {
    if (device_id.find(keyword) != std::string::npos) {
      return true;
    }
  }

  return false;
}

void OnDeviceNameInfoReady(IsUncertainFutureCallback callback,
                           std::unique_ptr<DeviceNameInfo> info) {
  const bool is_uncertain_future = IsUncertainFuture(info.get());
  std::move(callback).Run(is_uncertain_future);
}

void OnHardwareInfoReady(DeviceNameInfo* device_name_info_ptr,
                         base::ScopedClosureRunner done_closure,
                         base::SysInfo::HardwareInfo hardware_info) {
  device_name_info_ptr->manufacturer_name =
      std::move(hardware_info.manufacturer);

  device_name_info_ptr->model_name = std::move(hardware_info.model);
}

}  // namespace

void DetectUncertainFuture(IsUncertainFutureCallback callback) {
  auto device_name_info = std::make_unique<DeviceNameInfo>();
  DeviceNameInfo* device_name_info_ptr = device_name_info.get();

  auto done_closure = base::BarrierClosure(
      /*num_closures=*/1,
      base::BindOnce(&OnDeviceNameInfoReady, std::move(callback),
                     std::move(device_name_info)));

  base::SysInfo::GetHardwareInfo(
      base::BindOnce(&OnHardwareInfoReady, device_name_info_ptr,
                     base::ScopedClosureRunner(done_closure)));
}

}  // namespace brave_rpill
