/**
 * Copyright (c) 2018 Inria
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Daniel Carvalho
 */

#include "mem/cache/replacement_policies/energy_rp.hh"
#include "mem/cache/base.hh"

#include <cassert>
#include <memory>

#include "params/ENERGYRP.hh"

ENERGYRP::ENERGYRP(const Params *p)
    : BaseReplacementPolicy(p)
{
}

void
ENERGYRP::invalidate(const std::shared_ptr<ReplacementData>& replacement_data)
const
{
    // Reset last touch timestamp
    std::static_pointer_cast<ENERGYReplData>(
        replacement_data)->lastTouchTick = Tick(0);
}

void
ENERGYRP::touch(const std::shared_ptr<ReplacementData>& replacement_data) const
{
    // Update last touch timestamp
    std::static_pointer_cast<ENERGYReplData>(
        replacement_data)->lastTouchTick = curTick();
}

void
ENERGYRP::reset(const std::shared_ptr<ReplacementData>& replacement_data) const
{
    // Set last touch timestamp
    std::static_pointer_cast<ENERGYReplData>(
        replacement_data)->lastTouchTick = curTick();
}

ReplaceableEntry*
ENERGYRP::getVictim(const ReplacementCandidates& candidates) const
{
    assert(!candidates.empty());

    ReplaceableEntry* cleanVictim = nullptr;
    ReplaceableEntry* lruVictim = candidates[0];
    Tick oldestTick = std::static_pointer_cast<ENERGYReplData>(
                          lruVictim->replacementData)->lastTouchTick;

    for (const auto& candidate : candidates) {
        auto energyData = std::static_pointer_cast<ENERGYReplData>(
            candidate->replacementData);
        Tick tick = energyData->lastTouchTick;

        CacheBlk* blk = static_cast<CacheBlk*>(candidate);
        if (!blk->isDirty()) {
            // 找到最老的 clean block
            if (!cleanVictim || tick < std::static_pointer_cast<ENERGYReplData>(
                    cleanVictim->replacementData)->lastTouchTick) {
                cleanVictim = candidate;
            }
        }

        // 同時找最老的 block（備案）
        if (tick < oldestTick) {
            oldestTick = tick;
            lruVictim = candidate;
        }
    }

    // 優先 evict clean block
    return cleanVictim ? cleanVictim : lruVictim;
}




std::shared_ptr<ReplacementData>
ENERGYRP::instantiateEntry()
{
    return std::shared_ptr<ReplacementData>(new ENERGYReplData());
}

ENERGYRP*
ENERGYRPParams::create()
{
    return new ENERGYRP(this);
}
