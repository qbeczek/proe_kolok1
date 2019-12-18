#include "electoral_system_builder.hpp"

#include <numeric>
#include <random>

ElectoralSystem ElectoralSystemBuilder::build(
    ConstituenciesParameters votes_per_constituency,
    PartiesPercentOfVotes percent_votes_per_party,
    VoterTurnout voter_turnout) const
{
    ElectoralSystem electoral_system;

    for (const auto & constituency_votes : votes_per_constituency)
    {
        electoral_system.add(_getConstituency(
            std::get<NumberOfElects>(constituency_votes),
            std::get<NumberOfVoters>(constituency_votes),
            percent_votes_per_party,
            voter_turnout));
    }

    return electoral_system;
}

Constituency ElectoralSystemBuilder::_getConstituency(
    NumberOfElects elects,
    NumberOfVoters voters,
    PartiesPercentOfVotes votes_per_party,
    VoterTurnout voter_turnout) const
{
    Constituency constituency(elects);

    for (const auto& votes_for_party : votes_per_party)
    {
        constituency.add(_getElectrionList(
            std::get<PolitycalParty>(votes_for_party),
            _calcVotesCastForParty(voters, voter_turnout, std::get<PercentOfVotes>(votes_for_party))));
    }
    return constituency;
}

int ElectoralSystemBuilder::_calcVotesCastForParty(NumberOfVoters voters, VoterTurnout voter_turnout, PercentOfVotes percent_of_votes) const
{
    return static_cast<int>(std::round(voters.value * voter_turnout.value * percent_of_votes.value));
}

ElectionList ElectoralSystemBuilder::_getElectrionList(PolitycalParty party, int votes_cast) const
{
    ElectionList election_list(party);

    auto candidates = _getCandidates(party.name());

    auto op = [](const unsigned int& lhs, const Candidate& rhs) {return lhs + rhs.votes; };
    auto total_numbet_of_votes = std::accumulate(candidates.begin(), candidates.end(), 0, op);

    for (const auto& candidate : candidates)
    {
        auto normalized_votes = static_cast<double>(candidate.votes) / static_cast<double>(total_numbet_of_votes) * static_cast<double>(votes_cast);
        election_list.add(Candidate{ candidate.name, static_cast<unsigned int>(normalized_votes) });
    }

    return election_list;
}

Candidates ElectoralSystemBuilder::_getCandidates(const std::string& name) const
{
    Candidates candidates;

    auto number_of_candidates = _getNumberOfCandidates();

    for (unsigned int i = 0; i < number_of_candidates; ++i)
    {
        candidates.add(Candidate{ name + ": " + std::to_string(i + 1), _getNumberOfCandidateVotes() });
    }

    return candidates;
}

unsigned int ElectoralSystemBuilder::_getNumberOfCandidates() const
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    auto mean = static_cast<double>(mean_number_of_candidates_per_constituency_);

    std::normal_distribution<> dis{ mean,mean / 5 };

    auto number_of_candidates = static_cast<int>(std::round(dis(gen)));

    return number_of_candidates ? number_of_candidates : 0;
}

unsigned int ElectoralSystemBuilder::_getNumberOfCandidateVotes() const
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1000.0);

    return static_cast<int>(std::round(dis(gen)));
}

