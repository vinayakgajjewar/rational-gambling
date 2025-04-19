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

double simulate_single_round(double current_bankroll, double bet_percent) {
    double bet_size = current_bankroll * bet_percent;
    bool result = flip_coin(WIN_PROBABILITY);
    if (result) {
        current_bankroll += (PAYOUT_RATIO * bet_size);
    } else {
        current_bankroll -= bet_size;
    }
    return current_bankroll;
}

bool simulate_rounds(double bet_percent) {
    bool bankroll_doubled = false;
    double bankroll = STARTING_BANKROLL;
    int current_round = 1;
    while (!bankroll_doubled && current_round <= ROUNDS) {
        bankroll = simulate_single_round(bankroll, bet_percent);
        if (bankroll_condition_met(bankroll)) {
            bankroll_doubled = true;
        }
        current_round++;
    }
    return bankroll_doubled;
}

double get_success_probability(double bet_percent) {
    int successes = 0;
    for (int i = 0; i < ITERATIONS; i++) {
        bool success = simulate_rounds(bet_percent);
        if (success) {
            successes++;
        }
    }
    double success_probability = static_cast<double>(successes) / static_cast<double>(ITERATIONS);
    return success_probability;
}

int main() {
    std::vector<double> bet_percents = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
    double best_bet_percent;
    double best_success_probability;
    for (double bet_percent: bet_percents) {
        std::cout << "Testing " << bet_percent << " bet percent" << std::endl;
        double success_probability = get_success_probability(bet_percent);
        if (success_probability >= best_success_probability) {
            best_bet_percent = bet_percent;
            best_success_probability = success_probability;
        }
    }
    std::cout << "Best bet percent is " << best_bet_percent << " with a " << best_success_probability
              << " success probability" << std::endl;
}
