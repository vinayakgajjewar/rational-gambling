#include <iostream>
#include <random>

constexpr int ROUNDS = 10'000;
constexpr double WIN_PROBABILITY = 0.55;
constexpr double PAYOUT_RATIO = 1.0;
constexpr double STARTING_BANKROLL = 1.0;
constexpr double BET_PERCENT = 0.1;

bool flip_coin(double probability_of_winning) {
    std::random_device random;
    std::mt19937 generator(random());
    std::bernoulli_distribution distribution(probability_of_winning);
    bool result = distribution(generator);
    return result;
}

bool bankroll_condition_met(double bankroll) {
    bool return_value;
    if (bankroll >= 2 * STARTING_BANKROLL) {
        return_value = true;
    } else {
        return_value = false;
    }
    return return_value;
}

int main() {
    double bankroll = STARTING_BANKROLL;
    for (int j = 0; j < ROUNDS; j++) {
        double bet_size = bankroll * BET_PERCENT;
        bool result = flip_coin(WIN_PROBABILITY);
        if (result) {
            bankroll += (PAYOUT_RATIO * bet_size);
        } else {
            bankroll -= bet_size;
        }
        if (bankroll_condition_met(bankroll)) {
            std::cout << "Starting amount doubled after " << (j + 1) << " rounds" << std::endl;
            break;
        }
    }
    std::cout << "Ending bankroll: " << bankroll << std::endl;
}
