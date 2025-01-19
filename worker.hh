#pragma once

/**
 * Represents one Worker
 */
#include "job.hh"
#include <optional>

class Worker

{
public:
  Worker() : _job() {}
  bool IsWorking() const;
  std::optional<Job> currentJob() const { return _job; }
  void assignJob(Jobs newJob);
  void stopJob();
  const static int salary = 10;

protected:
  /// None if workless
  std::optional<Job> _job;
};
