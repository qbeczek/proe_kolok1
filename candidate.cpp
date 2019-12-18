#include "candidate.hpp"

#include <algorithm>

Candidates Candidates::sortByNames()
{
    std::sort(candidates_.begin(), candidates_.end(), [](const Candidate& lhs, const Candidate& rhs) {return lhs.name < rhs.name; });
    return *this;
}

Candidates Candidates::sortByVotes()
{
    std::sort(candidates_.begin(), candidates_.end(), [](const Candidate& lhs, const Candidate& rhs) {return lhs.votes > rhs.votes; });
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Candidate& candidate)
{
    os << candidate.name << " " << candidate.votes;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Candidates& candidates)
{
    unsigned int i = 1;
    for (const auto& candidate : candidates)
    {
        os << i++ << ": " << candidate << std::endl;
    }
    return os;
}