#include "dHondt_method.hpp"

#include <algorithm>

Candidates DHondtMethod::operator()(const Constituencies& constituencies) const
{
    auto parties = _getPartiesOverThreshold(constituencies);

    Candidates candidates;

    for (const auto constituency : constituencies)
    {
        candidates.add(_getElectedCandidates(constituency, parties));
    }

    return candidates;
}

PolitycalParties DHondtMethod::_getPartiesOverThreshold(const Constituencies& constituencies) const
{
    PolitycalParties parties;

    auto total_number_of_votes = _calculateNumberOfVotes(constituencies);

    for (const auto& party : _getAllParties(constituencies))
    {
        if (total_number_of_votes * threshold_.value < _calculateNumberOfVotes(constituencies, party))
            parties.add(party);
    }

    return parties;
}

PolitycalParties DHondtMethod::_getAllParties(const Constituencies& constituencies) const
{
    PolitycalParties parties;

    for (const auto constituency : constituencies)
    {
        parties.add(constituency.parties());
    }

    return parties;
}

unsigned int DHondtMethod::_calculateNumberOfVotes(const Constituencies& constituencies) const
{
    unsigned int number_of_votes = 0;

    for (auto const& constituency : constituencies)
    {
        number_of_votes += _calculateNumberOfVotes(constituency);
    }

    return number_of_votes;
}

unsigned int DHondtMethod::_calculateNumberOfVotes(const Constituency& constituency) const
{
    return _calculateNumberOfVotes(constituency.candidates());
}

unsigned int DHondtMethod::_calculateNumberOfVotes(const Constituencies& constituencies, const PolitycalParty& party) const
{
    unsigned int number_of_votes = 0;

    for (auto const& constituency : constituencies)
    {
        number_of_votes += _calculateNumberOfVotes(constituency, party);
    }

    return number_of_votes;
}

unsigned int DHondtMethod::_calculateNumberOfVotes(const Constituency& constituency, const PolitycalParty& party) const
{
    return _calculateNumberOfVotes(constituency.candidates(party));
}

unsigned int DHondtMethod::_calculateNumberOfVotes(const Candidates& candidates) const
{
    unsigned number_of_votes = 0;

    for (auto const& candidate : candidates)
    {
        number_of_votes += candidate.votes;
    }

    return number_of_votes;
}

Candidates DHondtMethod::_getElectedCandidates(const Constituency& constituency, const PolitycalParties& parties) const
{
    Candidates candidates;

    auto metric_candidates = _getCandidatesMetrics(constituency, parties);

    _sortByMetric(metric_candidates);

    return _selectElectedCandidates(metric_candidates, constituency.numberOfElects().value);
}

DHondtMethod::MetricCandidates DHondtMethod::_getCandidatesMetrics(const Constituency& constituency, const PolitycalParties& parties) const
{
    MetricCandidates candidates_metrics;

    for (const auto & party : parties)
    {
        auto candidates = _getCandidatesMetrics(constituency, party);

        candidates_metrics.insert(candidates_metrics.end(), candidates.begin(), candidates.end());
    }

    return candidates_metrics;
}

DHondtMethod::MetricCandidates DHondtMethod::_getCandidatesMetrics(const Constituency& constituency, const PolitycalParty& party) const
{
    MetricCandidates candidates_metrics;

    auto number_of_votes = _calculateNumberOfVotes(constituency, party);

    auto candidates = constituency.candidates(party).sortByVotes();

    int i = 1;

    for (const auto& candidate : candidates)
    {
        candidates_metrics.push_back({ candidate, static_cast<double>(number_of_votes) / i++ });
    }

    return candidates_metrics;
}

void DHondtMethod::_sortByMetric(MetricCandidates& candidates_metrics) const
{
    auto cmp = [](const auto& lhs, const auto& rhs) { return lhs.metric < rhs.metric; };

    std::sort(candidates_metrics.begin(), candidates_metrics.end(), cmp);
}

Candidates DHondtMethod::_selectElectedCandidates(MetricCandidates& metric_candidates, unsigned int number_of_elects) const
{
    Candidates candidates;

    while (number_of_elects--)
    {
        candidates.add(metric_candidates.back().candidate);
        metric_candidates.pop_back();
    }

    return candidates;
}
