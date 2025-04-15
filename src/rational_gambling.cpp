#include <iostream>
#include <random>

namespace parameters {
    constexpr int ROUNDS = 10'000;
    constexpr double WIN_PROBABILITY = 0.55;
    constexpr double PAYOUT_RATIO = 1.0;
    constexpr double STARTING_BANKROLL = 1.0;
    constexpr double BET_PERCENT = 0.1;
}

bool flip_coin(double probability_of_winning) {
    std::random_device random;
    std::mt19937 generator(random());
    std::bernoulli_distribution distribution(probability_of_winning);
    bool result = distribution(generator);
    return result;
}

int main() {
    double bankroll = parameters::STARTING_BANKROLL;
    for (int j = 0; j < parameters::ROUNDS; j++) {
        double bet_size = bankroll * parameters::BET_PERCENT;
        bool result = flip_coin(parameters::WIN_PROBABILITY);
        if (result) {
            bankroll += (parameters::PAYOUT_RATIO * bet_size);
        } else {
            bankroll -= bet_size;
        }
    }
    std::cout << "Ending bankroll: " << bankroll << std::endl;
}
