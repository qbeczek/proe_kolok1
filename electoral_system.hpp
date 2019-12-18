#ifndef ELECTORAL_SYSTEM_HPP
#define ELECTORAL_SYSTEM_HPP

#include "candidate.hpp"
#include "politycal_party.hpp"
#include "constituency.hpp"

class ElectoralSystem
{
public:
    void add(const Constituency&);

    template<typename ElectionMethod>
    Candidates electedCandidates(const ElectionMethod&) const;
    Candidates allCandidates() const;

private:
    Constituencies constituencies_;
};

template<typename ElectionMethod>
inline Candidates ElectoralSystem::electedCandidates(const ElectionMethod& election_method) const
{
    return election_method(constituencies_);
}

#endif // ELECTORAL_SYSTEM_HPP


