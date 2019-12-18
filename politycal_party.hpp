#ifndef POLITYCAL_PARTY_HPP
#define POLITYCAL_PARTY_HPP

#include <string>
#include <vector>

#include "candidate.hpp"

class PolitycalParty
{
public:
    PolitycalParty(std::string name)
        : name_(name)
    {}

    auto name() const { return name_; }

private:
    std::string name_;
};

struct PartyCmp
{
    bool operator()(const PolitycalParty& lhs, const PolitycalParty& rhs) const { return lhs.name() < rhs.name(); }
};

class PolitycalParties
{
public:
    auto begin() const { return parties_.begin(); }
    auto end() const { return parties_.end(); }

    void add(const PolitycalParties& parties) { parties_.insert(parties_.end(), parties.begin(), parties.end()); unique(); }
    void add(const PolitycalParty& party) { parties_.push_back(party); unique(); }

private:
    void unique();

    std::vector<PolitycalParty> parties_;
};

class ElectionList
{
public:
    ElectionList(const PolitycalParty& party)
        : party_(party)
    {}

    auto party() const { return party_; }
    auto candidates() const { return candidates_; }

    void add(const Candidate& candidate) { candidates_.add(candidate); }
private:
    PolitycalParty party_;
    Candidates candidates_;
};

#endif // POLITYCAL_PARTY_HPP


