#include <iostream>
#include <random>

constexpr int ITERATIONS = 1e6;
constexpr int ROUNDS = 10;
constexpr double WIN_PROBABILITY = 0.5;
constexpr double PAYOUT_RATIO = 1.5;
constexpr double STARTING_BANKROLL = 1.0;
constexpr double BET_PERCENT = 0.67;

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

bool simulate_rounds() {
    bool bankroll_doubled = false;
    double bankroll = STARTING_BANKROLL;
    int current_round = 1;
    while (!bankroll_doubled && current_round <= ROUNDS) {
        double bet_size = bankroll * BET_PERCENT;
        bool result = flip_coin(WIN_PROBABILITY);
        if (result) {
            bankroll += (PAYOUT_RATIO * bet_size);
        } else {
            bankroll -= bet_size;
        }
        if (bankroll_condition_met(bankroll)) {
            bankroll_doubled = true;
        }
        current_round++;
    }
    return bankroll_doubled;
}

int main() {
    int successes = 0;
    for (int i = 0; i < ITERATIONS; i++) {
        bool success = simulate_rounds();
        if (success) {
            successes++;
        }
    }
    double success_probability = static_cast<double>(successes) / static_cast<double>(ITERATIONS);
    std::cout << "Probability of success: " << success_probability << std::endl;
}
