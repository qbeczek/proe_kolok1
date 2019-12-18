#include "politycal_party.hpp"

#include <algorithm>

void PolitycalParties::unique()
{
    std::sort(parties_.begin(), parties_.end(), PartyCmp());
    auto it = std::unique(parties_.begin(), parties_.end(), [](const auto& lhs, const auto& rhs) { return lhs.name() == rhs.name(); });
    parties_.erase(it, parties_.end());
}
