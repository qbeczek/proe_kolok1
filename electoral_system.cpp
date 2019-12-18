#include "electoral_system.hpp"

void ElectoralSystem::add(const Constituency& constituency)
{
    constituencies_.add(constituency);
}

Candidates ElectoralSystem::allCandidates() const
{
    Candidates result;

    for (const auto constituency : constituencies_)
        result.add(constituency.candidates());

    return result;
}
