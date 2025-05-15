#include "NavigationSubsystem.hpp"
#include "CcsdsPrimaryHeader.hpp"
#include "CcsdsSecondaryHeader.hpp"
#include "CcsdsPacket.hpp"

#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

NavigationSubsystem::NavigationSubsystem(std::atomic<bool>& runningFlag)
    : running(runningFlag) {}

void NavigationSubsystem::run()
{
    auto prihdr = CcsdsPrimaryHeader::createTelemetryPacket(42);
    while (running.load())
    {
        auto sechdr = CcsdsSecondaryHeader::now();
        prihdr.incrementSequenceCount();
        std::vector<uint8_t> data = {0xDE, 0xAD, 0xBE, 0xEF};

        CcsdsPacket packet(prihdr, sechdr, std::move(data));
        auto serialized = packet.serialize(); // fully compliant CCSDS packet

        std::cout << "[NavigationSubsystem::run] Pkt: " << std::endl;
        for (auto byte : serialized)
        {
            std::cout << std::hex << std::setw(2) << std::setfill('0')
            << static_cast<int>(byte) << " ";
        }
        std::cout << std::dec << std::endl;



        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "[NavigationSubsystem::run] " << "stopping cleanly." << std::endl;
}

/*
*   INFO:   Since I'm picking back up w/ Cpp I'm going to document stuff along 
*           the way as I relearn things.
*
*   What is the "::" notation for?
*
*       It tells C++ where to find the function or type. Kind of all like
*       saying what "folder" or "owner" it belongs to. "::" more specially is
*       the scope resolution operator.
*
*   Where did "this_thread" come from?
*
*       It came from the "std" library as we can tell through the scope 
*       resolution operator. It represents the current thread you are running
*       in. 
*
*       So "std::this_thread" is a namespace in <thread>. It provides utilities
*       for the current thread, like sleeping.
*/
