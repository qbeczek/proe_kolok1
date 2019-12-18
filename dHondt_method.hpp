#ifndef DHONDT_METHOD_HPP
#define DHONDT_METHOD_HPP

#include "electoral_system.hpp"

class DHondtMethod
{
    struct MetricCandidate
    {
        Candidate candidate;
        double metric;
    };

    using MetricCandidates = std::vector<MetricCandidate>;


public:
    DHondtMethod(PercentOfVotes threshold) : threshold_(threshold) {}

    Candidates operator()(const Constituencies& constituencies) const;

private:
    PolitycalParties _getPartiesOverThreshold(const Constituencies & constituencies) const;

    PolitycalParties _getAllParties(const Constituencies & constituencies) const;

    unsigned int _calculateNumberOfVotes(const Constituencies & constituencies) const;

    unsigned int _calculateNumberOfVotes(const Constituency & constituency) const;

    unsigned int _calculateNumberOfVotes(const Constituencies & constituencies, const PolitycalParty & party) const;

    unsigned int _calculateNumberOfVotes(const Constituency & constituency, const PolitycalParty & party) const;

    unsigned int _calculateNumberOfVotes(const Candidates & candidates) const;

    Candidates _getElectedCandidates(const Constituency & constituency, const PolitycalParties & parties) const;

    DHondtMethod::MetricCandidates _getCandidatesMetrics(const Constituency & constituency, const PolitycalParties & parties) const;

    DHondtMethod::MetricCandidates _getCandidatesMetrics(const Constituency & constituency, const PolitycalParty & party) const;

    void _sortByMetric(MetricCandidates & candidates_metrics) const;

    Candidates _selectElectedCandidates(MetricCandidates & metric_candidates, unsigned int number_of_elects) const;

    PercentOfVotes threshold_;
};


#endif // DHONDT_METHOD_HPP
