#ifndef ELECTORAL_SYSTEM_BUILDER_HPP
#define ELECTORAL_SYSTEM_BUILDER_HPP

#include <initializer_list>
#include <vector>
#include <tuple>
#include <set>

#include "electoral_system.hpp"

class PartiesPercentOfVotes
{
    using ElementType = std::tuple < PolitycalParty, PercentOfVotes>;

    struct ElementTypeCompare
    {
        bool operator()(const ElementType& lhs, const ElementType& rhs)
        {
            return PartyCmp()(std::get<PolitycalParty>(lhs), std::get<PolitycalParty>(rhs));
        }
    };

    using ContainerType = std::set<ElementType, ElementTypeCompare >;

public:
    PartiesPercentOfVotes(std::initializer_list<ElementType> init_list)
        : percent_of_votes_(init_list) {}

    auto begin() const { return percent_of_votes_.begin(); }
    auto end() const { return percent_of_votes_.end(); }

private:
    ContainerType percent_of_votes_;
};

class ConstituenciesParameters
{
    using ElementType = std::tuple<NumberOfElects, NumberOfVoters>;
    using ContainerType = std::vector<ElementType>;

public:
    ConstituenciesParameters(std::initializer_list<ElementType> init_list)
        : number_of_votes_(init_list) {}

    auto begin() const { return number_of_votes_.begin(); }
    auto end() const { return number_of_votes_.end(); }

private:
    ContainerType number_of_votes_;
};

class ElectoralSystemBuilder
{
public:
    ElectoralSystemBuilder() = default;

    ElectoralSystemBuilder(unsigned int value)
        : mean_number_of_candidates_per_constituency_(value) {};

    ElectoralSystem build(
        ConstituenciesParameters votes_per_constituency,
        PartiesPercentOfVotes percent_votes_per_party,
        VoterTurnout voter_turnout) const;

private:
    unsigned int mean_number_of_candidates_per_constituency_ = 10;

    Constituency _getConstituency(NumberOfElects, NumberOfVoters, PartiesPercentOfVotes, VoterTurnout) const;
    int _calcVotesCastForParty(NumberOfVoters, VoterTurnout, PercentOfVotes) const;
    ElectionList _getElectrionList(PolitycalParty party, int votes_cast_for_party) const;
    Candidates _getCandidates(const std::string& name) const;
    unsigned int _getNumberOfCandidates() const;
    unsigned int _getNumberOfCandidateVotes() const;
};

#endif // ELECTORAL_SYSTEM_BUILDER_HPP
