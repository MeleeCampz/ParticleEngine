#ifndef GLTIMER_H_
#define GLTIMER_H_

#include <string>
#include <utils/timerU.h>

namespace oogl {

class timer: utils::timer {
public:
	timer(const std::string& name);
protected:
	virtual void start();
	virtual void stop();
};

}

#endif
