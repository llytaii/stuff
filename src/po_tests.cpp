#include <iostream>

#include <boost/program_options.hpp>


namespace po = boost::program_options;

int main(int _argc, char* _argv[])
{
    po::options_description desc{"allowed options"};
    desc.add_options()
        ("help", "produce help message")        
        ("compression", po::value<int>(), "set compression level");

    po::variables_map vm;
    po::store(po::parse_command_line(_argc, _argv, desc), vm);
    po::notify(vm);

    if(vm.count("help"))
    {
        std::cout << desc << std::endl;
        return 1;
    }

    if(vm.count("compression"))
    {
        std::cout << "compression level was set to: "
                << vm["compression"].as<int>() << std::endl;
    }
    else
    {
        std::cout << "compression level was not set\n";
    }

    return 0;
}