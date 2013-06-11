#include <oogl/glIncludes.h>
#include <oogl/timer.h>

namespace oogl {
oogl::timer::timer(const std::string& name) :
	utils::timer(name) {
}

void oogl::timer::start() {
	glFinish();
	utils::timer::start();
}

void oogl::timer::stop() {
	glFinish();
	utils::timer::stop();
}
}
