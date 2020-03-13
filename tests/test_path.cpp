#include "test_path.h"
#include <unistd.h>
#include <sstream>
#include <fstream>

namespace TestPathNs
{

std::string get_path(const std::string& s)
{
    size_t i = s.rfind('/');

    return (i != std::string::npos) ? s.substr(0, i) : "";
}

std::string make_path(const std::string& fname)
{
    std::string path;

    if (std::string::npos == fname.find('/'))
    {
        std::ostringstream cmdline;
        cmdline << "/proc/" << getpid() << "/cmdline";
        std::ifstream ifs(cmdline.str().c_str());

        ifs >> path;

        path = get_path(path);

        path.append("/");
    }

    path.append(fname);

    return path;
}

}
