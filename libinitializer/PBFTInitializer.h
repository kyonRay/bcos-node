/**
 *  Copyright (C) 2021 FISCO BCOS.
 *  SPDX-License-Identifier: Apache-2.0
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 * @brief initializer for the PBFT module
 * @file PBFTInitializer.h
 * @author: yujiechen
 * @date 2021-06-10
 */
#pragma once
#include "libinitializer/Common.h"
#include "libinitializer/NetworkInitializer.h"
#include "libinitializer/ProtocolInitializer.h"
#include <bcos-framework/libsealer/SealerFactory.h>
#include <bcos-pbft/pbft/PBFTFactory.h>
#include <bcos-sync/BlockSyncFactory.h>
#include <bcos-txpool/TxPoolFactory.h>

namespace bcos
{
namespace initializer
{
class PBFTInitializer
{
public:
    using Ptr = std::shared_ptr<PBFTInitializer>;
    PBFTInitializer() = default;
    virtual ~PBFTInitializer() { stop(); }

    virtual void init(NodeConfig::Ptr _nodeConfig, ProtocolInitializer::Ptr _protocolInitializer,
        NetworkInitializer::Ptr _networkInitializer, bcos::ledger::LedgerInterface::Ptr _ledger,
        bcos::dispatcher::DispatcherInterface::Ptr _dispatcher,
        bcos::storage::StorageInterface::Ptr _storage);

    virtual void start();
    virtual void stop();

    // for mini-consensus
    bcos::txpool::TxPoolInterface::Ptr txpool() { return m_txpool; }

protected:
    virtual void createTxPool(NodeConfig::Ptr _nodeConfig,
        ProtocolInitializer::Ptr _protocolInitializer, NetworkInitializer::Ptr _networkInitializer,
        bcos::ledger::LedgerInterface::Ptr _ledger);

    virtual void createSealer(
        NodeConfig::Ptr _nodeConfig, ProtocolInitializer::Ptr _protocolInitializer);

    virtual void createPBFT(NodeConfig::Ptr _nodeConfig,
        ProtocolInitializer::Ptr _protocolInitializer, NetworkInitializer::Ptr _networkInitializer,
        bcos::storage::StorageInterface::Ptr _storage, bcos::ledger::LedgerInterface::Ptr _ledger,
        bcos::dispatcher::DispatcherInterface::Ptr _dispatcher);

    virtual void createSync(NodeConfig::Ptr _nodeConfig,
        ProtocolInitializer::Ptr _protocolInitializer, NetworkInitializer::Ptr _networkInitializer,
        bcos::ledger::LedgerInterface::Ptr _ledger,
        bcos::dispatcher::DispatcherInterface::Ptr _dispatcher);

private:
    bcos::txpool::TxPool::Ptr m_txpool;
    bcos::sealer::Sealer::Ptr m_sealer;
    bcos::consensus::PBFTImpl::Ptr m_pbft;
    bcos::sync::BlockSync::Ptr m_blockSync;
};
}  // namespace initializer
}  // namespace bcos