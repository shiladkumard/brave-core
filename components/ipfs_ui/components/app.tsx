/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as React from 'react'
import { bindActionCreators, Dispatch } from 'redux'
import { connect } from 'react-redux'

// Components
import { AddressesConfig } from './addressesConfig'
import { ConnectedPeers } from './connectedPeers'
import { DaemonStatus } from './daemonStatus'
import { NodeInfo } from './nodeInfo'
import { RepoStats } from './repoStats'
import { UninstalledView } from './uninstalledView'
import { LearnMoreLink, GrayStyle } from '../style'
import { getLocale } from '../../common/locale'

// Utils
import * as ipfsActions from '../actions/ipfs_actions'

interface Props {
  actions: any
  ipfsData: IPFS.State
}

export class IPFSPage extends React.Component<Props, {}> {
  constructor (props: Props) {
    super(props)
  }

  get actions () {
    return this.props.actions
  }

  launchDaemon = () => {
    this.actions.launchDaemon()
  }

  shutdownDaemon = () => {
    this.actions.shutdownDaemon()
  }

  restartDaemon = () => {
    this.actions.restartDaemon()
  }

  installDaemon = () => {
    this.actions.installDaemon()
  }

  openNodeWebUI = () => {
    this.actions.openNodeWebUI()
  }

  openPeersWebUI = () => {
    this.actions.openPeersWebUI()
  }

  refreshActions = () => {
    this.actions.getConnectedPeers()
    this.actions.getAddressesConfig()
    this.actions.getRepoStats()
    this.actions.getNodeInfo()
  }

  componentDidUpdate (prevProps: Props) {
    if (prevProps.ipfsData.daemonStatus.launched !== this.props.ipfsData.daemonStatus.launched) {
      setTimeout(this.refreshActions, 2000)
    }
  }

  render () {
    return (
      <div id='ipfsPage'>
        {!this.props.ipfsData.daemonStatus.installed && (
        <UninstalledView daemonStatus={this.props.ipfsData.daemonStatus} onInstall={this.installDaemon}/>
        )}
        {this.props.ipfsData.daemonStatus.installed && (
        <DaemonStatus daemonStatus={this.props.ipfsData.daemonStatus} addressesConfig={this.props.ipfsData.addressesConfig} onLaunch={this.launchDaemon} onShutdown={this.shutdownDaemon} onRestart={this.restartDaemon} onOpenNodeWebUI={this.openNodeWebUI} />
        )}

        <div
          style={(!this.props.ipfsData.daemonStatus.installed ||
          this.props.ipfsData.daemonStatus.restarting ||
          !this.props.ipfsData.daemonStatus.launched) ? GrayStyle : {}}
        >
          <ConnectedPeers addressesConfig={this.props.ipfsData.addressesConfig} peerCount={this.props.ipfsData.connectedPeers.peerCount} onOpenPeersWebUI={this.openPeersWebUI} />
          <AddressesConfig addressesConfig={this.props.ipfsData.addressesConfig} />
          <RepoStats repoStats={this.props.ipfsData.repoStats} />
          <NodeInfo nodeInfo={this.props.ipfsData.nodeInfo} />
        </div>
        <a style={LearnMoreLink} href='https://support.brave.com/hc/en-us/sections/360010974932-InterPlanetary-File-System-IPFS-' target='_blank'>
          {getLocale('learn_more')}
        </a>
      </div>
    )
  }
}

export const mapStateToProps = (state: IPFS.ApplicationState) => ({
  ipfsData: state.ipfsData
})

export const mapDispatchToProps = (dispatch: Dispatch) => ({
  actions: bindActionCreators(ipfsActions, dispatch)
})

export default connect(
  mapStateToProps,
  mapDispatchToProps
)(IPFSPage)
