#ifndef CANDIDATE_HPP
#define CANDIDATE_HPP

#include <string>
#include <vector>

#include "helpers.hpp"

struct Candidate
{
    std::string name;
    unsigned int votes;
};

class Candidates
{
public:
    auto begin() const { return candidates_.begin(); }
    auto end() const { return candidates_.end(); }

    void add(const Candidates& candidates) { candidates_.insert(candidates_.end(), candidates.candidates_.begin(), candidates.candidates_.end()); }
    void add(const Candidate& candidate) { candidates_.push_back(candidate); }

    Candidates sortByNames();

    Candidates sortByVotes();

private:
    std::vector<Candidate> candidates_;
};

std::ostream& operator<<(std::ostream& os, const Candidate& candidate);
std::ostream& operator<<(std::ostream& os, const Candidates& candidates);

#endif // CANDIDATE_HPP


