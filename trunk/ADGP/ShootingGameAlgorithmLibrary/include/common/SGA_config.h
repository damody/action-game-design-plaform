#pragma once
#define SGA_MAX_THREADS 8
#define SGA_USE_MUTITHREAD 1

#if (SGA_USE_MUTITHREAD > 0)
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/thread/mutex.hpp>
typedef boost::mutex MUTEX;
typedef MUTEX::scoped_lock LOCK;
#endif
