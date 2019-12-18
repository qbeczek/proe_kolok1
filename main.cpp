#include <iostream> 

#include "electoral_system.hpp"
#include "electoral_system_builder.hpp"
#include "dHondt_method.hpp"

int main(void)
{
    PartiesPercentOfVotes parties = {
        {PolitycalParty("A"), PercentOfVotes{0.01} },
        {PolitycalParty("B"), PercentOfVotes{0.6} },
        {PolitycalParty("C"), PercentOfVotes{0.39}} };

    ConstituenciesParameters constituencies = {
        {NumberOfElects{4}, NumberOfVoters{800} },
        {NumberOfElects{3}, NumberOfVoters{650} },
        {NumberOfElects{5}, NumberOfVoters{1050} }
    };

    auto mean_number_of_candidates_per_list = 10;
    ElectoralSystemBuilder builder(mean_number_of_candidates_per_list);
    auto electoral_system = builder.build(constituencies, parties, VoterTurnout(0.65));

    auto threshold = 0.05;
    auto election_method = DHondtMethod(threshold);

    auto electedCandidates = electoral_system.electedCandidates(election_method);

    std::cout << electedCandidates;

    std::cout << std::endl;
    std::getchar();
    return 0;
}
