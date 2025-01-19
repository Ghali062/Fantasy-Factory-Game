#include "worker.hh"

bool Worker::IsWorking() const { return _job.has_value(); }
void Worker::assignJob(Jobs newJobs) { _job.emplace(newJobs); }
void Worker::stopJob() { _job.reset(); }
