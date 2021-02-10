// Copyright (c) 2020 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.*/

import * as React from 'react'

import {
  SettingsRow,
  SettingsText,
  StyledTopSitesCustomizationSettings,
  StyledTopSitesCustomizationSettingsOption,
  StyledTopSitesCustomizationImage,
  StyledTopSitesCustomizationOptionTitle,
  StyledTopSitesCustomizationOptionDesc
} from '../../../components/default'
import { Toggle } from '../../../components/toggle'

import { getLocale } from '../../../../common/locale'

import favoritesSelected from './assets/favorites-selected.png'
import favoritesUnselected from './assets/favorites-unselected.png'
import frecencySelected from './assets/frecency-selected.png'
import frecencyUnselected from './assets/frecency-unselected.png'

interface Props {
  toggleShowTopSites: () => void
  showTopSites: boolean
  customLinksEnabled: boolean
  setMostVisitedSettings: (show: boolean, customize: boolean) => void
}

class TopSitesSettings extends React.PureComponent<Props, {}> {
  onClickFavorites = () => {
    this.props.setMostVisitedSettings(true, true)
  }

  onClickFrecency = () => {
    this.props.setMostVisitedSettings(true, false)
  }

  render () {
    const {
      toggleShowTopSites,
      showTopSites,
      customLinksEnabled
    } = this.props
    return (
      <div>
        <SettingsRow>
          <SettingsText>{getLocale('showTopSites')}</SettingsText>
          <Toggle
            onChange={toggleShowTopSites}
            checked={showTopSites}
            size='large'
          />
        </SettingsRow>
        <StyledTopSitesCustomizationSettings>
          <StyledTopSitesCustomizationSettingsOption>
            <StyledTopSitesCustomizationImage
              src={showTopSites ? customLinksEnabled ? favoritesSelected : favoritesUnselected
                                : favoritesUnselected}
              onClick={this.onClickFavorites}
            />
            <StyledTopSitesCustomizationOptionTitle>
              {getLocale('showFavoritesLabel')}
            </StyledTopSitesCustomizationOptionTitle>
            <StyledTopSitesCustomizationOptionDesc>
              {getLocale('showFavoritesDesc')}
            </StyledTopSitesCustomizationOptionDesc>
          </StyledTopSitesCustomizationSettingsOption>
          <StyledTopSitesCustomizationSettingsOption>
            <StyledTopSitesCustomizationImage
              src={showTopSites ? customLinksEnabled ? frecencyUnselected : frecencySelected
                                : frecencyUnselected}
              onClick={this.onClickFrecency}
            />
            <StyledTopSitesCustomizationOptionTitle>
              {getLocale('showFrecencyLabel')}
            </StyledTopSitesCustomizationOptionTitle>
            <StyledTopSitesCustomizationOptionDesc>
              {getLocale('showFrecencyDesc')}
            </StyledTopSitesCustomizationOptionDesc>
          </StyledTopSitesCustomizationSettingsOption>
        </StyledTopSitesCustomizationSettings>
      </div>
    )
  }
}

export default TopSitesSettings
