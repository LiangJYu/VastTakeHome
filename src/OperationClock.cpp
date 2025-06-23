/**
 * @file OperationClock.cpp
 * @brief Implementation of the OperationClock class.
 */

#include <format>
#include <iostream>
#include "Constants.h"
#include "OperationClock.h"

/**
 * @brief Constructs OperationClock with default timing parameters.
 * @details Initializes using constants from Constants:
 *   - current_time = 0
 *   - end_time = Constants::default_stop_time
 *   - t_increment = Constants::default_increment_time
 *
 * @throws std::invalid_argument if t_increment > end_time
 */
OperationClock::OperationClock()
    : current_time {0}
    , end_time {Constants::default_stop_time }
    , t_increment { Constants::default_increment_time} {}

void OperationClock::add_time(unsigned int t_to_add)
{
    // Ensure that add t_increment won't exceed end_time.
    if (current_time + t_to_add > end_time) {
        current_time = end_time;
    } else {
        current_time += t_to_add;
    }
}

/**
 * @brief Prefix increment operator.
 * @details:
 *   - Increases current_time by t_increment
 *
 * @return Reference to modified object
 */
OperationClock& OperationClock::operator++()
{
    this->add_time(t_increment);

    return *this;
}

/**
 * @brief Postfix increment operator.
 * @details:
 *   - Creates temporary copy of current state
 *   - Applies prefix increment to current object
 *   - Returns original state
 *
 * @return Copy of OperationClock before increment
 */
OperationClock OperationClock::operator++(int)
{
    OperationClock temp = *this;

    // Use prefix increment
    ++(*this);

    return temp;
}

/**
 * @brief Checks if clock is within operational period.
 * @details Compares current_time against end_time.
 *
 * @return true if operational period not expired
 */
bool OperationClock::not_expired() const
{
    return current_time < end_time;
}
