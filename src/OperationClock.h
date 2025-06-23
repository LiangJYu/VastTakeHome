/**
 * @file OperationClock.h
 * @brief Declaration of the OperationClock class and time constants.
 */

/**
 * @class OperationClock
 * @brief Tracks operational time with increment and boundary checking.
 *
 * Simulates a clock that increments at a specified rate until reaching a
 * predefined end time. Useful for simulations and time-bound operations.
 */
class OperationClock {
  // Maximum operational time in seconds
  unsigned int end_time;
  // Current elapsed time in seconds
  unsigned int current_time;
  // Time increment per step in seconds
  unsigned int t_increment;

public:
  /**
   * @brief Default constructor.
   * @details Initializes:
   *   - current_time = 0
   *   - end_time = Constants::default_stop_time
   *   - t_increment = Constants::default_increment_time
   *
   * @exception std::invalid_argument If t_increment exceeds end_time
   */
  OperationClock();

  unsigned int get_end_time() const { return end_time; };

  unsigned int get_current_time() const { return current_time; };

  unsigned int get_t_increment() const { return t_increment; };

  void add_time(unsigned int t_to_add);

  /**
   * @brief Prefix increment operator.
   * @return Reference to modified OperationClock object
   */
  OperationClock &operator++();

  /**
   * @brief Postfix increment operator.
   * @return Copy of OperationClock before increment
   */
  OperationClock operator++(int);

  /**
   * @brief Check if clock is within operational period.
   * @return true if current_time <= end_time, false otherwise
   */
  bool not_expired() const;
};
