#include "constituency.hpp"

Candidates Constituency::candidates() const
{
    Candidates result;

    for (const auto list : election_lists_)
        result.add(list.second.candidates());

    return result;
}

Candidates Constituency::candidates(const PolitycalParty & party) const
{
    auto it = election_lists_.find(party);

    if (it != election_lists_.end())
        return it->second.candidates();

    return Candidates();
}

PolitycalParties Constituency::parties() const
{
    PolitycalParties parties;

    for (const auto& list : election_lists_)
        parties.add(list.first);

    return parties;
}
