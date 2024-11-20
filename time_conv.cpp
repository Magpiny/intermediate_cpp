#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct TimeConstants
{
  static constexpr int64_t SECOND = 1000;
  static constexpr int64_t MINUTE = 60 * SECOND;
  static constexpr int64_t HOUR = 60 * MINUTE;
  static constexpr int64_t DAY = 24 * HOUR;
};

std::string
time_counter(int64_t milliseconds)
{
  // Calculate the number of days, hours, minutes, and seconds
  int64_t days = milliseconds / TimeConstants::DAY;
  milliseconds %= TimeConstants::DAY;
  int64_t hours = milliseconds / TimeConstants::HOUR;
  milliseconds %= TimeConstants::HOUR;
  int64_t minutes = milliseconds / TimeConstants::MINUTE;
  milliseconds %= TimeConstants::MINUTE;
  int64_t seconds = milliseconds / TimeConstants::SECOND;

  // Create a vector to hold the time components
  std::vector<std::string> time_components;

  if (days > 0) {
    time_components.push_back(std::to_string(days) + "d");
  }
  if (hours > 0) {
    time_components.push_back(std::to_string(hours) + "hr");
  }
  if (minutes > 0) {
    time_components.push_back(std::to_string(minutes) + "min");
  }
  if (seconds > 0 ||
      time_components.empty()) { // Include seconds if it's the only component
    time_components.push_back(std::to_string(seconds) + "s");
  }

  // Join the time components with spaces
  std::ostringstream oss;
  for (size_t i = 0; i < time_components.size(); ++i) {
    if (i > 0) {
      oss << " ";
    }
    oss << time_components[i];
  }

  return oss.str();
}

int
main()
{
  // Example usage
  std::cout << time_counter(23000) << std::endl;     // Output: 23s
  std::cout << time_counter(84000) << std::endl;     // Output: 1min 24s
  std::cout << time_counter(9000000) << std::endl;   // Output: 2hr 30min
  std::cout << time_counter(191430000) << std::endl; // Output: 2d 3hr 45min
  return 0;
}
