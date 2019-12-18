#ifndef HELPERS_HPP
#define HELPERS_HPP

struct PercentOfVotes
{
    PercentOfVotes(double value) : value(value)
    {
        if (value < 0 || value > 1)
            throw std::exception("wrong argument value");
    }

    const double value;
};

struct VoterTurnout
{
    VoterTurnout(double value) : value(value)
    {
        if (value < 0 || value > 1)
            throw std::exception("wrong argument value");
    }

    const double value;
};

struct NumberOfVoters
{
    const unsigned int value;
};

struct NumberOfElects
{
    const unsigned int value;
};

#endif // HELPERS_HPP


