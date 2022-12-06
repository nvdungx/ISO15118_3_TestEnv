#include "port.hpp"
#include <queue>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/fmt.h>
#include <stdexcept>
#include <boost/random.hpp>


#define SLOGW(msg) spdlog::warn("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGI(msg) spdlog::info("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGE(msg) spdlog::error("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGD(msg) spdlog::debug("{0} {1}: {2}", __FILE__, __LINE__, msg)

namespace TestLib
{
Port::Port()
{
  
}

Port::Port(PortType ptype)
{
  // generate hash ID base on name or random
  _id = 0;
  // port name - set by owner component
  _name = "";
  _pType = ptype;
  _pAddr = 0;
}
Port::~Port() {}

const std::shared_ptr<Component>& Port::get_parent_comp(void)
{

}

void Port::set_parent_comp(const std::shared_ptr<Component> &parentComp)
{

}

void Port::clear()
{

}

void Port::start()
{

}
void Port::stop()
{

}
void Port::halt()
{

}
void Port::checkstate()
{

}

void map(const std::shared_ptr<Port> &compPort, const std::shared_ptr<Port> &tsiPort)
{
// if ("legal connection")
// then "store link to other port"
//   ( if ("link not yet established")
//     then "establish this link" else null )

// if ("illegal connection") then "store link to other port" error
}

void unmap(const std::shared_ptr<Port> &compPort, const std::shared_ptr<Port> &tsiPort)
{
// if ("link established") then "remove this link" else null
}

void connect(const std::shared_ptr<Port> &compPort, const std::shared_ptr<Port> &targetPort)
{
// if ("legal connection")
// then ( if ("link not yet established")
//        then "establish this link" else null )

// if ("illegal connection") then error
}

void disconnect(const std::shared_ptr<Port> &compPort, const std::shared_ptr<Port> &targetPort)
{
// if ("link established") then "remove this link" else null
}

void all_component_kill()
{

}


} // namespace TestLib
