#ifndef CONSTITUENCY_HPP
#define CONSTITUENCY_HPP

#include <vector>
#include <map>

#include "candidate.hpp"
#include "politycal_party.hpp"

class Constituency
{
public:
    Constituency(NumberOfElects number_of_elects)
        : number_of_elects_(number_of_elects)
    {
    }

    void add(const ElectionList& list)
    {
        election_lists_.insert(std::make_pair(list.party(), list));
    }

    Candidates candidates() const;
    Candidates candidates(const PolitycalParty&) const;

    NumberOfElects numberOfElects() const { return number_of_elects_; }

    PolitycalParties parties() const ;

private:
    std::map < PolitycalParty, ElectionList, PartyCmp> election_lists_;
    NumberOfElects number_of_elects_;
};

class Constituencies
{
public:
    auto begin() const { return constituencies_.begin(); }
    auto end() const { return constituencies_.end(); }

    void add(const Constituency& constituency) { constituencies_.push_back(constituency); }

private:
    std::vector< Constituency> constituencies_;
};

#endif // CONSTITUENCY_HPP


