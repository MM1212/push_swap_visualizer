#pragma once

#include <string>
#include <list>
#include <vector>
#include <memory>

struct Run {
  std::string numbers;
  std::list<std::string> commands;
  Run(const std::string &numbers, const std::list<std::string> &commands)
   : numbers(numbers), commands(commands) {};
};

class Bulk {
  public:
    Bulk();
    ~Bulk() = default;

    bool isEnabled() const { return this->m_enabled; };
    void recordRun(const std::string &numbers, const std::list<std::string> &commands);
    void toggle() { this->m_enabled = !this->m_enabled; };
    void clear();
    auto getAverage() const { return this->m_average; };
    auto getMin() const { return this->m_min; };
    auto getMax() const { return this->m_max; };
    auto& getRuns() const { return this->m_runs; };
    void onImGuiRender();
    void start();
    bool isRunning() const { return this->m_count > 0; };
    void decrement() { this->m_count--; };

  private:
    bool m_enabled;
    int m_size;
    uint32_t m_count;
    uint32_t m_average;
    uint32_t m_min;
    uint32_t m_max;
    std::vector<std::unique_ptr<Run>> m_runs;
    void computeStats();
};